#include "spidermonkey.h"

static JSClass global_class = {
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

const char* foo(const char *script) {
    JSRuntime *rt = JS_NewRuntime(8L * 1024 * 1024, JS_USE_HELPER_THREADS);
    if (!rt)
        return ":(";

    JSContext *cx = JS_NewContext(rt, 8192);
    if (!cx)
        return ":(";

    JS::RootedObject global(cx, JS_NewGlobalObject(cx, &global_class, nullptr));
    if (!global)
        return ":(";

    JS::RootedValue rval(cx);

    {
      JSAutoCompartment ac(cx, global);
      JS_InitStandardClasses(cx, global);

      const char *filename = "noname";
      int lineno = 1;
      bool ok = JS_EvaluateScript(cx, global, script, strlen(script), filename, lineno, rval.address());
      if (!ok)
        return ":(";
    }

    JSString *str = rval.toString();

    const char *ret = JS_EncodeString(cx, str);

    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();

    return ret;
}
