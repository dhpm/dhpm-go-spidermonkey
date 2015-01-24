package spidermonkey

import (
    "testing"

    "github.com/stretchr/testify/assert"
    // "github.com/stretchr/testify/suite"
)

func TestDefinedFunction(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    val, err := GetFoo(cx, "gogo() + ' wrrrld'")

    assert.Equal(t, "hello wrrrld", val)
    assert.Nil(t, err)
}

func TestException(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    val, err := GetFoo(cx, "throw new Error('test')")

    assert.Equal(t, "", val)
    assert.Nil(t, err)
}

func TestSyntaxError(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    val, err := GetFoo(cx, "8==;")

    assert.Equal(t, "", val)
    assert.Nil(t, err)
}

func TestValidScript(t *testing.T) {
    // defer JS_ShutDown()

    rt := JS_NewRuntime()
    defer JS_DestroyRuntime(rt)

    cx := JS_NewContext(rt)
    defer JS_DestroyContext(cx)

    val, err := GetFoo(cx, "['abc', 'def'].join('-')")

    assert.Equal(t, "abc-def", val)
    assert.Nil(t, err)
}
