# Source files
SRCS = src/main.c src/board.c

# Output binary
OUT = PACE

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I./include

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(SRCS) -o $(OUT) $(CFLAGS)

clean:
	rm -f $(OUT)

.PHONY: all clean