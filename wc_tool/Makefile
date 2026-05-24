CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = main.c counter.c
TARGET = build/ccwc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf build
