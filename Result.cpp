#include "Result.h"

map<JSContext*, Result*> Result::errorHandleMap;

void handleError(JSContext *cx, const char *message, JSErrorReport *report)
{
    Result::GetErrorReporter(cx)->HandleError(cx, message, report);
}

Result* Result::GetErrorReporter(JSContext *cx)
{
    return Result::errorHandleMap.find(cx)->second;
}

void Result::SetErrorReporter(JSContext *cx, Result *result)
{
    Result::errorHandleMap.insert(pair<JSContext*, Result*>(cx, result));
}

Result::Result(const char *value, JSErrorReport *report)
{
    this->SetReport(report);
    this->SetValue(value);
}

JSErrorReporter Result::BeErrorReporter(JSContext *cx)
{
    Result::SetErrorReporter(cx, this);

    return JS_SetErrorReporter(cx, handleError);
}

const char* Result::GetValue()
{
    return this->value;
}

void Result::SetValue(const char* value)
{
    this->value = value;
}

JSErrorReport* Result::GetReport()
{
    return this->report;
}

bool Result::HasReport()
{
    return this->report;
}

void Result::SetReport(JSErrorReport *report)
{
    this->report = report;
}

void Result::HandleError(JSContext *cx, const char *message, JSErrorReport *report)
{
    JSString *jsStackTrace = nullptr;
    jsval v;

    fprintf(stderr, "File: %s Line: %u Message: %s\n", report->filename ? report->filename : "[no filename]", (unsigned int) report->lineno, message);

    if (JSREPORT_IS_EXCEPTION(report->flags) && JS_GetPendingException(cx, &v)) {
        JS_ClearPendingException(cx);

        JS_GetProperty(cx, JSVAL_TO_OBJECT(v), "stack", &v);
        jsStackTrace = JS_ValueToString(cx, v);
    }
    if (jsStackTrace) {
        fprintf(stderr, "Stack: %s\n", JS_EncodeString(cx, jsStackTrace));
    }
}
