# Makefile for Dynamic Memory Allocation Lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Target executable
TARGET = dynamic_memory
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

# Clean compiled files
clean:
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist *.o del *.o

# Check for memory leaks (if valgrind is available)
memcheck: $(TARGET)
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET); \
	else \
		echo "Valgrind not found. Running with address sanitizer instead."; \
		$(MAKE) run-debug; \
	fi

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

# Test with different input
test: $(TARGET)
	@echo Testing with different inputs...
	@echo 3 | $(TARGET).exe

# Profile memory usage (if available)
profile: debug
	@if command -v time >/dev/null 2>&1; then \
		echo "Memory usage profiling:"; \
		/usr/bin/time -v ./$(TARGET)_debug 2>&1 | grep -E "(Maximum resident|Page faults)"; \
	else \
		echo "time command not available for profiling."; \
	fi

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  run       - Build and run the program"
	@echo "  debug     - Build debug version with sanitizers"
	@echo "  run-debug - Build and run debug version"
	@echo "  clean     - Remove compiled files"
	@echo "  memcheck  - Run with valgrind or address sanitizer"
	@echo "  analyze   - Run static analysis (if cppcheck available)"
	@echo "  format    - Format source code (if clang-format available)"
	@echo "  test      - Run with predefined test input"
	@echo "  profile   - Profile memory usage"
	@echo "  help      - Show this help message"

# Declare phony targets
.PHONY: all run debug run-debug clean memcheck analyze format test profile help