#include "Result.h"

void handleError(JSContext *cx, const char *message, JSErrorReport *report)
{
    Result::GetErrorReporter(cx)->HandleError(cx, message, report);
}

Result::Result(const char *value, JSErrorReport *report)
{
    this->SetReport(report);
    this->SetValue(value);
}

static function<void(JSContext*, const char*, JSErrorReport*)> Result::GetErrorReporter(JSContext *cx)
{
    return Result::errorHandleMap[cx];
}

static void Result::SetErrorReporter(JSContext *cx, function<void(JSContext*, const char*, JSErrorReport*)> errorHandle)
{
    Result::errorHandleMap[cx] = errorHandle;
}

JSErrorReporter Result::BeErrorReporter(JSContext *cx)
{
    Result::SetErrorReporter(cx, bind(&Result::HandleError, result, _1, _2, _3));

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
