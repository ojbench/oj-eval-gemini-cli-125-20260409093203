CXX = g++
CXXFLAGS = -O2 -std=c++14 -Wall

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o code

clean:
	rm -f code
