# Makefile for Control Structures Lesson
# Lesson 4: if/else and switch statements

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEBUG_FLAGS = -g -DDEBUG
TARGET = control_structures
SOURCE = main.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(SOURCE)

# Compile and run
run: $(TARGET)
	$(TARGET).exe

# Compile with debug symbols
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug.exe $(SOURCE)

# Run debug version
run-debug: debug
	$(TARGET)_debug.exe

# Clean compiled files
clean:
	del /Q $(TARGET).exe $(TARGET)_debug.exe *.o 2>nul || echo Clean completed

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Compile the program (default)"
	@echo "  run       - Compile and run the program"
	@echo "  debug     - Compile with debug symbols"
	@echo "  run-debug - Compile and run debug version"
	@echo "  clean     - Remove compiled files"
	@echo "  help      - Show this help message"

# Declare phony targets
.PHONY: all run debug run-debug clean help