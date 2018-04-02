CPP=g++
CPPFLAGS=-Wall -Wpedantic -DUSE_STREAM

.PHONY: all clean


all: buvos-opt buvos-dbg


buvos-opt: buvos-opt.o
	$(CPP) buvos-opt.o -o buvos-opt

buvos-opt.o: buvos.cpp
	$(CPP) -std=c++11 -c buvos.cpp -o buvos-opt.o -O3 $(CPPFLAGS)


buvos-dbg: buvos-dbg.o
	$(CPP) buvos-dbg.o -o buvos-dbg

buvos-dbg.o: buvos.cpp
	$(CPP) -std=c++11 -c buvos.cpp -o buvos-dbg.o -g $(CPPFLAGS)


clean:
	rm -f buvos-dbg.o buvos-dbg buvos-opt buvos-opt.o
