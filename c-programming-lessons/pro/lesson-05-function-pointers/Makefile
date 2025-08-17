# Makefile for Function Pointers Lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
DEBUG_FLAGS = -g -DDEBUG -fsanitize=address -fsanitize=undefined
RELEASE_FLAGS = -O2 -DNDEBUG

# Target executable
TARGET = function_pointers
SOURCE = main.c

# Windows executable extension
ifeq ($(OS),Windows_NT)
    EXT = .exe
    RM = del /Q
    RMDIR = rmdir /S /Q
else
    EXT = 
    RM = rm -f
    RMDIR = rm -rf
endif

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -o $(TARGET)$(EXT) $(SOURCE)

# Compile and run
run: $(TARGET)
	$(TARGET)$(EXT)

# Debug build with sanitizers
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug$(EXT) $(SOURCE)

# Run debug version
run-debug: debug
	$(TARGET)_debug$(EXT)

# Clean compiled files
clean:
ifeq ($(OS),Windows_NT)
	@if exist $(TARGET)$(EXT) del $(TARGET)$(EXT)
	@if exist $(TARGET)_debug$(EXT) del $(TARGET)_debug$(EXT)
	@if exist *.o del *.o
else
	$(RM) $(TARGET)$(EXT) $(TARGET)_debug$(EXT) *.o
endif

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

# Test function pointer concepts
test-concepts: $(TARGET)
	@echo "Testing function pointer concepts..."
	@echo "1. Testing basic function pointers"
	@echo "2. Testing function pointer arrays"
	@echo "3. Testing callback functions"
	@echo "4. Testing qsort integration"
	@echo "5. Testing event handling"
	@echo "6. Testing strategy pattern"
	@echo "7. Testing function pointers as parameters"
	@echo "8. Testing returning function pointers"
	@echo ""
	./$(TARGET)

# Performance comparison
perf-test: $(TARGET)
	@echo "Performance testing function pointers vs direct calls..."
	@time ./$(TARGET) 2>&1 | grep -E "(real|user|sys)" || ./$(TARGET)

# Demonstrate compiler optimizations
optimize-test:
	@echo "Comparing different optimization levels:"
	@echo "No optimization (-O0):"
	@$(CC) $(CFLAGS) -O0 -o $(TARGET)_O0 $(SOURCE)
	@time ./$(TARGET)_O0 >/dev/null 2>&1 || echo "O0 version completed"
	@echo "Standard optimization (-O2):"
	@$(CC) $(CFLAGS) -O2 -o $(TARGET)_O2 $(SOURCE)
	@time ./$(TARGET)_O2 >/dev/null 2>&1 || echo "O2 version completed"
	@echo "Maximum optimization (-O3):"
	@$(CC) $(CFLAGS) -O3 -o $(TARGET)_O3 $(SOURCE)
	@time ./$(TARGET)_O3 >/dev/null 2>&1 || echo "O3 version completed"
	@rm -f $(TARGET)_O0 $(TARGET)_O2 $(TARGET)_O3

# Generate assembly output for analysis
assembly: $(SOURCE)
	@echo "Generating assembly output..."
	$(CC) $(CFLAGS) -S -fverbose-asm -o $(TARGET).s $(SOURCE)
	@echo "Assembly saved to $(TARGET).s"

# Show function addresses
addresses: $(TARGET)
	@echo "Function addresses in the compiled program:"
	@objdump -t $(TARGET) | grep -E "(add|subtract|multiply|divide)" | head -10

# Interactive demo
demo: $(TARGET)
	@echo "=== Function Pointers Interactive Demo ==="
	@echo "This program demonstrates various function pointer concepts."
	@echo "Press Enter to start..."
	@read dummy
	./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all           - Build the program (default)"
	@echo "  run           - Build and run the program"
	@echo "  debug         - Build debug version with sanitizers"
	@echo "  run-debug     - Build and run debug version"
	@echo "  clean         - Remove compiled files"
	@echo "  memcheck      - Run with valgrind or address sanitizer"
	@echo "  analyze       - Run static analysis (if cppcheck available)"
	@echo "  format        - Format source code (if clang-format available)"
	@echo "  test-concepts - Test all function pointer concepts"
	@echo "  perf-test     - Performance test function pointers"
	@echo "  optimize-test - Compare optimization levels"
	@echo "  assembly      - Generate assembly output"
	@echo "  addresses     - Show function addresses"
	@echo "  demo          - Interactive demonstration"
	@echo "  help          - Show this help message"

# Declare phony targets
.PHONY: all run debug run-debug clean memcheck analyze format test-concepts perf-test optimize-test assembly addresses demo help