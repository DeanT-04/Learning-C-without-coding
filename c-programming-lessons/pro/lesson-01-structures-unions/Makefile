# Makefile for Structures and Unions Lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Target executable
TARGET = structures_unions
SOURCE = main.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -o $(TARGET).exe $(SOURCE)

# Compile and run
run: $(TARGET)
	$(TARGET).exe

# Debug build
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug.exe $(SOURCE)

# Run debug version
run-debug: debug
	$(TARGET)_debug.exe

# Clean compiled files
clean:
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist *.o del *.o

# Check for memory leaks (Windows - just run debug version)
memcheck: debug
	@echo "Memory checking tools not available on Windows. Running debug version."
	$(TARGET)_debug.exe

# Static analysis (if cppcheck is available)
analyze:
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c11 $(SOURCE); \
	else \
		echo "cppcheck not found. Skipping static analysis."; \
	fi

# Format code (if clang-format is available)
format:
	@if command -v clang-format >/dev/null 2>&1; then \
		clang-format -i $(SOURCE); \
		echo "Code formatted."; \
	else \
		echo "clang-format not found. Skipping code formatting."; \
	fi

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  run       - Build and run the program"
	@echo "  debug     - Build debug version"
	@echo "  run-debug - Build and run debug version"
	@echo "  clean     - Remove compiled files"
	@echo "  memcheck  - Run with valgrind (if available)"
	@echo "  analyze   - Run static analysis (if cppcheck available)"
	@echo "  format    - Format source code (if clang-format available)"
	@echo "  help      - Show this help message"

# Declare phony targets
.PHONY: all run debug run-debug clean memcheck analyze format help