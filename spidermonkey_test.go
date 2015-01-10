package spidermonkey

import (
    "github.com/stretchr/testify/assert"
    "testing"
)

func TestFoo(t *testing.T) {
    assert.Equal(t, "hello world", Foo("['hello', 'world'].join(' ')"))
}

func TestHello(t *testing.T) {
    assert.Equal(t, ":)", Hello())
}
