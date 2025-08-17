# Makefile for Hello World lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUG_FLAGS = -g -DDEBUG
TARGET = hello_world
SOURCE = main.c

# Default target - compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Compile and run the program
run: $(TARGET)
	./$(TARGET)

# Compile with debug symbols
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug $(SOURCE)

# Clean compiled files
clean:
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist *.o del *.o

# Help target
help:
	@echo "Available targets:"
	@echo "  make          - Compile the program"
	@echo "  make run      - Compile and run the program"
	@echo "  make debug    - Compile with debug symbols"
	@echo "  make clean    - Remove compiled files"
	@echo "  make help     - Show this help message"

.PHONY: run debug clean help