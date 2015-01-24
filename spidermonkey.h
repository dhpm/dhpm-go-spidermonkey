#ifndef DHPM_SPIDERMONKEY_H
#define DHPM_SPIDERMONKEY_H

#include <jsapi.h>

#include "Result.h"

extern JSContext* JS_NewContext(JSRuntime*);
extern JSRuntime* JS_NewRuntime(void);
extern Result* foo(JSContext*, const char*);
extern void JS_DestroyContext(JSContext *cx);
extern void JS_DestroyRuntime(JSRuntime *rt);
extern void JS_ShutDown(void);

#endif
