CPP=g++
CPPFLAGS=-Wall -Wpedantic -DUSE_STREAM

.PHONY: all clean


all: sudoku-opt sudoku-dbg


sudoku-opt: sudoku-opt.o globals-opt.o sudoku4-opt.o sudoku9_util-opt.o sudoku9-opt.o generate.o
	$(CPP) $^ -o sudoku-opt

sudoku-opt.o: sudoku.cpp
	$(CPP) -std=c++11 -c sudoku.cpp -o sudoku-opt.o -O3 $(CPPFLAGS)


sudoku-dbg: sudoku-dbg.o globals-dbg.o sudoku4-dbg.o sudoku9_util-dbg.o sudoku9-dbg.o
	$(CPP) $^ -o sudoku-dbg

sudoku-dbg.o: sudoku.cpp
	$(CPP) -std=c++11 -c sudoku.cpp -o sudoku-dbg.o -g $(CPPFLAGS) -DDEBUG_BUILD



# 4x4 sudoku:
sudoku4-opt.o: sudoku4.cpp
	$(CPP) -std=c++11 -c sudoku4.cpp -o sudoku4-opt.o -O3 $(CPPFLAGS)

sudoku4-dbg.o: sudoku4.cpp
	$(CPP) -std=c++11 -c sudoku4.cpp -o sudoku4-dbg.o -g $(CPPFLAGS)


# 9x9 sudoku helpers:
sudoku9_util-opt.o: sudoku9_util.cpp
	$(CPP) -std=c++11 -c sudoku9_util.cpp -o sudoku9_util-opt.o -O3 $(CPPFLAGS)

sudoku9_util-dbg.o: sudoku9_util.cpp
	$(CPP) -std=c++11 -c sudoku9_util.cpp -o sudoku9_util-dbg.o -g $(CPPFLAGS)


sudoku9-opt.o: sudoku9.cpp
	$(CPP) -std=c++11 -c sudoku9.cpp -o sudoku9-opt.o -O3 $(CPPFLAGS)

sudoku9-dbg.o: sudoku9.cpp
	$(CPP) -std=c++11 -c sudoku9.cpp -o sudoku9-dbg.o -g $(CPPFLAGS)


# generation:
generate-opt.o: generate.cpp
	$(CPP) -std=c++11 -c generate.cpp -o generate-opt.o -O3 $(CPPFLAGS)

generate-dbg.o: generate.cpp
	$(CPP) -std=c++11 -c generate.cpp -o generate-dbg.o -g $(CPPFLAGS)

# globals:
globals-opt.o: globals.cpp
	$(CPP) -std=c++11 -c globals.cpp -o globals-opt.o -O3 $(CPPFLAGS)

globals-dbg.o: globals.cpp
	$(CPP) -std=c++11 -c globals.cpp -o globals-dbg.o -g $(CPPFLAGS)


# Clean:
clean:
	rm -f sudoku-dbg.o sudoku-dbg sudoku-opt sudoku-opt.o sudoku4-opt.o sudoku4-dbg.o global-opt.o global-dbg.o sudoku9_util-opt.o sudoku9_util-dbg.o sudoku9-opt.o sudoku9-dbg.o  globals-dbg.o globals-opt.o generate-opt.o generate-dbg.o
