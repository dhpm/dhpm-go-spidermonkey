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

    val, _ := Bar(cx, "gogo() + ' wrrrld'")

    assert.Equal(t, "hello wrrrld", val)
}

func TestException(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    val, _ := Bar(cx, "throw new Error('test')")

    assert.Equal(t, "", val)
}

func TestSyntaxError(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    val, _ := Bar(cx, "8==;")

    assert.Equal(t, "", val)
}

func TestValidScript(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    val, _ := Bar(cx, "['abc', 'def'].join('-')")

    assert.Equal(t, "abc-def", val)
}
