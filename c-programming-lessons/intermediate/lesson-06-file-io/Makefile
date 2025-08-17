# Makefile for Basic File I/O Lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUG_FLAGS = -g -DDEBUG
TARGET = file_io_lesson
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

# Clean compiled files and generated files
clean:
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist $(TARGET) del $(TARGET)
	@if exist $(TARGET)_debug del $(TARGET)_debug
	@if exist sample.txt del sample.txt
	@if exist numbers.txt del numbers.txt
	@if exist output.txt del output.txt
	@if exist append_demo.txt del append_demo.txt
	@if exist students.dat del students.dat
	@echo "Cleaned compiled files and generated files"

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
	@echo "  clean       - Remove compiled and generated files"
	@echo "  test-compile - Check syntax without creating executable"
	@echo "  help        - Show this help message"

# Declare phony targets
.PHONY: all run debug clean test-compile help