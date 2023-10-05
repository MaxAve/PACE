SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OUT = PACE
all: $(OUT)
$(OUT): $(SRCS)
	g++ $(SRCS) -o $(OUT)
clean:
	rm -f $(OUT)
.PHONY: all clean