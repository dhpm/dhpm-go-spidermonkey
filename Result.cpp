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

Result::Result(const char *value)
{
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

ErrorReport* Result::GetReport()
{
    return this->report;
}

bool Result::HasReport()
{
    return this->report;
}

void Result::SetReport(ErrorReport *report)
{
    this->report = report;
}

void Result::HandleError(JSContext *cx, const char *message, JSErrorReport *report)
{
    this->SetReport(new ErrorReport(cx, message, report));
}
