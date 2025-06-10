# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -std=c99 -I./library

# Source files
SRC = main.c eval.c library/mpc.c
OBJ = $(SRC:.c=.o)

# Target binary
TARGET = paprlang

# Detect platform
ifeq ($(OS),Windows_NT)
    LDFLAGS = 
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDFLAGS = -ledit
    endif
    ifeq ($(UNAME_S),Darwin)
        LDFLAGS = -ledit
    endif
endif

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

