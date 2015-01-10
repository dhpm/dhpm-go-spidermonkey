export CGO_ENABLED=0
export CGO_CPPFLAGS=-I/usr/include/mozjs-24

build test: spidermonkey.cpp spidermonkey.h spidermonkey.swigcxx

build:
	go build

test:
	go test --ldflags '-extldflags "-lmozjs-24"'
