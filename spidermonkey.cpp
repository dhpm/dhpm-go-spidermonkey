#include "spidermonkey.h"

static JSClass globalClass = {
    "global",
    JSCLASS_GLOBAL_FLAGS,
    // [SpiderMonkey 38] Following Stubs are removed. Remove those lines.
    JS_PropertyStub,
    JS_DeletePropertyStub,
    JS_PropertyStub,
    JS_StrictPropertyStub,
    JS_EnumerateStub,
    JS_ResolveStub,
    JS_ConvertStub
};

static JSBool myGoGo(JSContext *cx, unsigned argc, JS::Value *vp)
{
    const char *retString = "hello";
    JSString *jsString = JS_NewStringCopyN(cx, retString, strlen(retString));

    JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(jsString));

    return JS_TRUE;
}

JSContext* JS_NewContext(JSRuntime *rt)
{
    return JS_NewContext(rt, 8192);
}

JSRuntime* JS_NewRuntime()
{
    return JS_NewRuntime(8L * 1024 * 1024, JS_NO_HELPER_THREADS);
}

void reportError(JSContext *cx, const char *message, JSErrorReport *report)
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

Result* foo(JSContext *cx, const char *script)
{
    const char *filename;
    int lineno;
    JSScript *compiledScript;

    JS_SetErrorReporter(cx, reportError);

    JS::RootedObject global(cx, JS_NewGlobalObject(cx, &globalClass, nullptr));
    JS::RootedValue rval(cx);

    JSAutoCompartment ac(cx, global);

    JS_InitStandardClasses(cx, global);
    JS_DefineFunction(cx, global, "gogo", myGoGo, 0, 0);

    filename = "fooscript";
    lineno = 1;
    compiledScript = JS_CompileScript(cx, global, script, strlen(script), filename, lineno);

    if (!compiledScript) {
        // JS_ReportError(cx, "compile error :(");

        return new Result(nullptr, nullptr);
    }

    if (!JS_ExecuteScript(cx, global, compiledScript, rval.address())) {
        return new Result(nullptr, nullptr);
    }

    return new Result(JS_EncodeString(cx, rval.toString()), nullptr);
}
