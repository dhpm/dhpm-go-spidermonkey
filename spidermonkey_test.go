package spidermonkey

import (
    "testing"

    "github.com/stretchr/testify/assert"
)

func TestDefinedFunction(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    assert.Equal(t, "hello wrrrld", Foo(cx, "gogo() + ' wrrrld'"))
}

func TestException(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    assert.Equal(t, "", Foo(cx, "throw new Error('test');"))
}

func TestSyntaxError(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    assert.Equal(t, "", Foo(cx, "8==;"))
}

func TestValidScript(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    assert.Equal(t, "hello world", Foo(cx, "['hello', 'world'].join(' ')"))
}
