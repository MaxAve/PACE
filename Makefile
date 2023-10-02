# This Makefile compiles all C source files and creates an executable
# in the same directory as this Makefile
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)
OUT = PACE
CC = gcc
CFLAGS = -I./include
all: $(OUT)
$(OUT): $(SRCS)
	$(CC) $(SRCS) -o $(OUT) $(CFLAGS)
clean:
	rm -f $(OUT)
.PHONY: all clean
