# Makefile for Lesson 02: Variables and Data Types
# Demonstrates C data types, variable declaration, and initialization

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
DEBUG_FLAGS = -g -DDEBUG
TARGET = variables_types
SOURCE = main.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Compilation successful! Executable: $(TARGET)"

# Compile and run
run: $(TARGET)
	@echo "Running Variables and Data Types demonstration..."
	@echo "================================================"
	./$(TARGET)

# Debug build
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug $(SOURCE)
	@echo "Debug build created: $(TARGET)_debug"

# Clean compiled files
clean:
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist $(TARGET) del $(TARGET)
	@if exist $(TARGET)_debug del $(TARGET)_debug
	@echo "Cleaned compiled files"

# Show data type information
info:
	@echo "=== Data Types Information ==="
	@echo "This lesson covers:"
	@echo "- Integer types: char, short, int, long, long long"
	@echo "- Floating-point types: float, double, long double"
	@echo "- Boolean type: bool (C99)"
	@echo "- Variable declaration and initialization"
	@echo "- Type casting and conversion"
	@echo "- Constants and best practices"

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Compile the program (default)"
	@echo "  run     - Compile and run the program"
	@echo "  debug   - Compile with debug symbols"
	@echo "  clean   - Remove compiled files"
	@echo "  info    - Show lesson information"
	@echo "  help    - Show this help message"

# Declare phony targets
.PHONY: all run debug clean info help