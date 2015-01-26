package spidermonkey

func GetFoo(cx JSContext, script string) (value string, report JSErrorReport) {
    result := GetFooResult(cx, script)

    value = result.GetValue()

    if result.HasReport() {
        report = result.GetReport()
    }

    return
}
