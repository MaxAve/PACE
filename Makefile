# Esentially what this does is compile all .cpp files inside of the src folder
# Because of this, you do not have to update the Makefile as long as you don't need to add any
# compiler flags and whatnot
all: PACE
PACE: $(wildcard src/*.cpp)
	g++ -O3 $(wildcard src/*.cpp) -o bin/PACE
clean:
	rm -f PACE
.PHONY: all clean