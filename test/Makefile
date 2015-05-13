CXX = clang++-3.6
CXXFLAGS = -g -Wall -std=c++11
INC=-I..
LIBS =

bin/% : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(LIBS) $< -o $@

all: $(patsubst %.cpp, bin/%, $(wildcard *.cpp))

clean:
	rm -f bin/*
