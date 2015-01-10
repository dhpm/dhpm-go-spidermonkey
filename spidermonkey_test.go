package spidermonkey

import (
    "github.com/stretchr/testify/assert"
    "testing"
)

func TestFoo(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    assert.Equal(t, "hello world", Foo(cx, "['hello', 'world'].join(' ')"))
}

func TestDefinedFunction(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    assert.Equal(t, "hello world", Foo(cx, "gogo(); 'hello'"))
}

func TestHello(t *testing.T) {
    assert.Equal(t, ":)", Hello())
}
