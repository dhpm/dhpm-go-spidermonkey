export CGO_ENABLED=0
export CGO_CPPFLAGS=-std=c++0x -I/usr/include/mozjs-24

test: spidermonkey.cpp spidermonkey.h spidermonkey.swigcxx
	go test --ldflags '-extldflags "-lmozjs-24"'
