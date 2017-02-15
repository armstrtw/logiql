CXX = clang++
CXXFLAGS = -g -Wall -std=c++11
INC=-I.. -I/usr/include/catch
LIBS =

bin/% : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(LIBS) $< -o $@

all: $(patsubst %.cpp, bin/%, $(wildcard *.cpp))

clean:
	rm -f bin/*
