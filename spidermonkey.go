package spidermonkey

func Bar(cx JSContext, script string) (string, JSErrorReport) {
    ret := Foo(cx, script)

    return ret.GetValue(), ret.GetReport()
}
