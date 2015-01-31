#include "ErrorReport.h"

ErrorReport::ErrorReport(JSContext *cx, const char *message, JSErrorReport *report)
{
    this->context = context;
    this->message = message;
    this->report = report;
}

const char* ErrorReport::GetStackTrace()
{
    jsval v;

    if (!this->IsException() || !JS_GetPendingException(this->context, &v)) {
        return "";
    }

    JSString *jsStackTrace;

    JS_ClearPendingException(this->context);
    JS_GetProperty(this->context, JSVAL_TO_OBJECT(v), "stack", &v);

    jsStackTrace = JS_ValueToString(this->context, v);

    return JS_EncodeString(this->context, jsStackTrace);
}

bool ErrorReport::IsException()
{
    return JSREPORT_IS_EXCEPTION(this->report->flags);
}
