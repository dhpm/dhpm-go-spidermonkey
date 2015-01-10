#ifndef GO_SPIDERMONKEY_H
#define GO_SPIDERMONKEY_H

#include <jsapi.h>

extern const char* foo(JSContext*, const char*);
extern JSContext* JS_NewContext(JSRuntime*);
extern JSRuntime* JS_NewRuntime(void);
extern void JS_DestroyContext(JSContext *cx);
extern void JS_DestroyRuntime(JSRuntime *rt);
extern void JS_ShutDown(void);

#endif
