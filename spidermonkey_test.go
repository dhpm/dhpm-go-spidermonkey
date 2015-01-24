package spidermonkey

import (
    "testing"

    "github.com/stretchr/testify/assert"
    "github.com/stretchr/testify/suite"
)

type GetFooTestSuite struct {
    suite.Suite
    Context JSContext
    Runtime JSRuntime
}

func (suite *GetFooTestSuite) SetupTest() {
    suite.Runtime = JS_NewRuntime()
    suite.Context = JS_NewContext(suite.Runtime)
}

func (suite *GetFooTestSuite) TearDownAllSuite() {
    JS_ShutDown()
}

func (suite *GetFooTestSuite) TearDownTest() {
    JS_DestroyContext(suite.Context)
    JS_DestroyRuntime(suite.Runtime)
}

func (suite *GetFooTestSuite) TestDefinedFunction() {
    val, err := GetFoo(suite.Context, "gogo() + ' wrrrld'")

    assert.Equal(suite.T(), "hello wrrrld", val)
    assert.Nil(suite.T(), err)
}

func (suite *GetFooTestSuite) TestException() {
    val, err := GetFoo(suite.Context, "throw new Error('test')")

    assert.Equal(suite.T(), "", val)
    assert.NotNil(suite.T(), err)
}

func (suite *GetFooTestSuite) TestSyntaxError() {
    val, err := GetFoo(suite.Context, "8==;")

    assert.Equal(suite.T(), "", val)
    assert.NotNil(suite.T(), err)
}

func (suite *GetFooTestSuite) TestValidScript() {
    val, err := GetFoo(suite.Context, "['abc', 'def'].join('-')")

    assert.Equal(suite.T(), "abc-def", val)
    assert.Nil(suite.T(), err)
}

func TestExampleTestSuite(t *testing.T) {
    suite.Run(t, new(GetFooTestSuite))
}
