CXX = clang++-3.6
CXXFLAGS = -g -Wall -std=c++11
INC=-I..
LIBS =

% : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $(LIBS) $< -o $@

zero.coupon.bond.test: zero.coupon.bond.test.cpp
fixed.coupon.bond.test: fixed.coupon.bond.test.cpp

clean:
	rm -f zero.coupon.bond.test fixed.coupon.bond.test