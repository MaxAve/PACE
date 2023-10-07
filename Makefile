all: PACE
PACE: $(wildcard src/*.cpp)
	g++ $(wildcard src/*.cpp) -o PACE
clean:
	rm -f PACE
.PHONY: all clean