# Makefile for Pointers and Memory Lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUG_FLAGS = -g -DDEBUG
TARGET = pointers_lesson
SOURCE = main.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Compilation successful! Executable: $(TARGET)"

# Compile and run
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@echo "================================"
	./$(TARGET)
	@echo "================================"

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

# Test compilation without running
test-compile: $(SOURCE)
	$(CC) $(CFLAGS) -fsyntax-only $(SOURCE)
	@echo "Syntax check passed!"

# Show help
help:
	@echo "Available targets:"
	@echo "  all         - Compile the program (default)"
	@echo "  run         - Compile and run the program"
	@echo "  debug       - Compile with debug symbols"
	@echo "  clean       - Remove compiled files"
	@echo "  test-compile - Check syntax without creating executable"
	@echo "  help        - Show this help message"

# Declare phony targets
.PHONY: all run debug clean test-compile help