# Makefile for Preprocessor Directives Lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUG_FLAGS = -g -DDEBUG
TARGET = preprocessor_lesson
SOURCE = main.c
HEADERS = config.h math_utils.h

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Compilation successful! Executable: $(TARGET)"

# Compile and run
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@echo "================================"
	./$(TARGET)
	@echo "================================"

# Debug build
debug: $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug $(SOURCE)
	@echo "Debug build created: $(TARGET)_debug"

# Show preprocessor output
preprocess: $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -E $(SOURCE) -o $(TARGET).i
	@echo "Preprocessor output saved to $(TARGET).i"

# Clean compiled files
clean:
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist $(TARGET) del $(TARGET)
	@if exist $(TARGET)_debug del $(TARGET)_debug
	@if exist $(TARGET).i del $(TARGET).i
	@echo "Cleaned compiled files"

# Test compilation without running
test-compile: $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) -fsyntax-only $(SOURCE)
	@echo "Syntax check passed!"

# Show help
help:
	@echo "Available targets:"
	@echo "  all         - Compile the program (default)"
	@echo "  run         - Compile and run the program"
	@echo "  debug       - Compile with debug symbols"
	@echo "  preprocess  - Generate preprocessor output"
	@echo "  clean       - Remove compiled files"
	@echo "  test-compile - Check syntax without creating executable"
	@echo "  help        - Show this help message"

# Declare phony targets
.PHONY: all run debug preprocess clean test-compile help