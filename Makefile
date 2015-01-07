clean:
	git clean -f

install: spidermonkey.6 spidermonkey_gc.6
	go tool pack grc spidermonkey.a spidermonkey.6 spidermonkey_gc.6
	go install

spidermonkey.6: spidermonkey.go
	go tool 6g spidermonkey.go

spidermonkey_gc.6: spidermonkey_gc.c
	go tool 6c -I /usr/lib/go/pkg/linux_amd64/ -D _64BIT spidermonkey_gc.c

spidermonkey_gc.c: spidermonkey.go

spidermonkey.go: spidermonkey.cpp spidermonkey.h spidermonkey.swig
	swig -go -intgosize 32 -c++ spidermonkey.swig
