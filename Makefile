all: spidermonkey.a

clean:
	git clean -f

spidermonkey.6: spidermonkey.go
	go tool 6g spidermonkey.go

spidermonkey.a: spidermonkey.6 spidermonkey_gc.6 spidermonkey_wrap.o
	go tool pack grc spidermonkey.a spidermonkey.6 spidermonkey_gc.6 spidermonkey_wrap.o

spidermonkey.go spidermonkey_gc.c spidermonkey_wrap.cxx: spidermonkey.cpp spidermonkey.h spidermonkey.swigcxx
	swig -go -intgosize 64 -c++ spidermonkey.swigcxx

spidermonkey.o: spidermonkey.cpp
	gcc -c spidermonkey.cpp -o spidermonkey.o

spidermonkey_gc.6: spidermonkey_gc.c
	go tool 6c -I /usr/lib/go/pkg/linux_amd64/ -D _64BIT spidermonkey_gc.c

spidermonkey_wrap.o: spidermonkey_wrap.cxx
	gcc -c spidermonkey_wrap.cxx -o spidermonkey_wrap.o
