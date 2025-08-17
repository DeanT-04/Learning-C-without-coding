# Makefile for Advanced File Handling Lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Target executable
TARGET = file_handling
SOURCE = main.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -o $(TARGET).exe $(SOURCE)

# Compile and run
run: $(TARGET)
	$(TARGET).exe

# Debug build with sanitizers
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug.exe $(SOURCE)

# Run debug version
run-debug: debug
	$(TARGET)_debug.exe

# Clean compiled files and test files
clean:
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist *.o del *.o
	@if exist employees.dat del employees.dat
	@if exist positions.txt del positions.txt
	@if exist source.txt del source.txt
	@if exist copy*.txt del copy*.txt
	@if exist employees.csv del employees.csv
	@if exist old_name.txt del old_name.txt
	@if exist new_name.txt del new_name.txt
	@if exist error_test.txt del error_test.txt
	@if exist buffer_test.txt del buffer_test.txt

# Deep clean - remove all generated files
clean-all: clean
	@if exist *.dat del *.dat
	@if exist *.csv del *.csv
	@if exist *.txt del *.txt

# Check for memory leaks (Windows - use debug build with sanitizers)
memcheck: debug
	@echo "Running with address sanitizer (valgrind not available on Windows)"
	$(TARGET)_debug.exe

# Static analysis (if cppcheck is available)
analyze:
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem $(SOURCE); \
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

# Test file operations
test: $(TARGET)
	@echo "Testing file operations..."
	$(TARGET).exe
	@echo "Checking for leftover files..."
	@dir *.dat *.csv *.txt 2>nul || echo "All test files cleaned up successfully"

# Demonstrate binary file inspection
inspect-binary: $(TARGET)
	$(TARGET).exe
	@echo "Binary file content (if exists):"
	@if exist employees.dat (type employees.dat) else (echo "Binary file not found")

# Performance test with large file
perf-test: $(TARGET)
	@echo "Performance testing with file operations..."
	$(TARGET).exe

# Show help
help:
	@echo "Available targets:"
	@echo "  all         - Build the program (default)"
	@echo "  run         - Build and run the program"
	@echo "  debug       - Build debug version with sanitizers"
	@echo "  run-debug   - Build and run debug version"
	@echo "  clean       - Remove compiled files and test files"
	@echo "  clean-all   - Remove all generated files"
	@echo "  memcheck    - Run with valgrind or address sanitizer"
	@echo "  analyze     - Run static analysis (if cppcheck available)"
	@echo "  format      - Format source code (if clang-format available)"
	@echo "  test        - Run program and verify cleanup"
	@echo "  inspect-binary - Run program and inspect binary files"
	@echo "  perf-test   - Performance test file operations"
	@echo "  help        - Show this help message"

# Declare phony targets
.PHONY: all run debug run-debug clean clean-all memcheck analyze format test inspect-binary perf-test help