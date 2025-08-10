CXX = g++
CXXFLAGS = -Wall -std=c++17
LIBS = -lncurses

all: ark_ncurses

ark_ncurses: main.cpp json.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o ark_ncurses $(LIBS)

clean:
	rm -f ark_ncurses
