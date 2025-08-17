# Advanced Algorithms Lesson Makefile
# Demonstrates compilation with optimization flags and profiling support

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OPTFLAGS = -O2 -march=native
DEBUGFLAGS = -g -O0 -DDEBUG
PROFILEFLAGS = -pg -O2

# Target executable
TARGET = algorithms
SOURCE = main.c

# Default target
all: $(TARGET)

# Standard compilation
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Compiled $(TARGET) successfully!"

# Optimized build for performance testing
optimized: $(SOURCE)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(TARGET)_opt $(SOURCE)
	@echo "Compiled optimized version: $(TARGET)_opt"

# Debug build with debugging symbols
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET)_debug $(SOURCE)
	@echo "Compiled debug version: $(TARGET)_debug"

# Profile build for performance analysis
profile: $(SOURCE)
	$(CC) $(CFLAGS) $(PROFILEFLAGS) -o $(TARGET)_profile $(SOURCE)
	@echo "Compiled profile version: $(TARGET)_profile"
	@echo "Run './$(TARGET)_profile' then 'gprof $(TARGET)_profile gmon.out' to analyze"

# Run the standard program
run: $(TARGET)
	@echo "Running Advanced Algorithms demonstration..."
	@echo "=========================================="
	./$(TARGET)

# Run optimized version
run-opt: optimized
	@echo "Running optimized version..."
	@echo "============================"
	./$(TARGET)_opt

# Run debug version with GDB
debug-run: debug
	@echo "Starting GDB session..."
	gdb ./$(TARGET)_debug

# Performance comparison between standard and optimized
benchmark: $(TARGET) optimized
	@echo "Performance Benchmark"
	@echo "===================="
	@echo "Standard build:"
	time ./$(TARGET) > /dev/null
	@echo ""
	@echo "Optimized build:"
	time ./$(TARGET)_opt > /dev/null

# Memory check with Valgrind (if available)
memcheck: debug
	@echo "Running memory check..."
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)_debug; \
	else \
		echo "Valgrind not found. Install valgrind for memory checking."; \
	fi

# Static analysis with cppcheck (if available)
analyze: $(SOURCE)
	@echo "Running static analysis..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c11 $(SOURCE); \
	else \
		echo "cppcheck not found. Install cppcheck for static analysis."; \
	fi

# Generate assembly output to study optimization
assembly: $(SOURCE)
	$(CC) $(CFLAGS) $(OPTFLAGS) -S -o $(TARGET).s $(SOURCE)
	@echo "Generated assembly file: $(TARGET).s"

# Clean all generated files
clean:
	@echo "Cleaning up..."
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_opt.exe del $(TARGET)_opt.exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist $(TARGET)_profile.exe del $(TARGET)_profile.exe
	@if exist $(TARGET).s del $(TARGET).s
	@if exist gmon.out del gmon.out
	@echo "Clean complete!"

# Show compiler and system information
info:
	@echo "Compiler Information:"
	@echo "===================="
	@$(CC) --version
	@echo ""
	@echo "System Information:"
	@echo "=================="
	@uname -a
	@echo ""
	@echo "Available Memory:"
	@echo "================"
	@if command -v free >/dev/null 2>&1; then \
		free -h; \
	else \
		echo "Memory info not available on this system"; \
	fi

# Help target
help:
	@echo "Available targets:"
	@echo "=================="
	@echo "  all        - Build standard version (default)"
	@echo "  optimized  - Build with optimization flags"
	@echo "  debug      - Build with debug symbols"
	@echo "  profile    - Build with profiling support"
	@echo "  run        - Run the standard program"
	@echo "  run-opt    - Run the optimized version"
	@echo "  debug-run  - Run with GDB debugger"
	@echo "  benchmark  - Compare standard vs optimized performance"
	@echo "  memcheck   - Run memory leak detection (requires Valgrind)"
	@echo "  analyze    - Run static code analysis (requires cppcheck)"
	@echo "  assembly   - Generate assembly output"
	@echo "  clean      - Remove all generated files"
	@echo "  info       - Show compiler and system information"
	@echo "  help       - Show this help message"

# Declare phony targets
.PHONY: all optimized debug profile run run-opt debug-run benchmark memcheck analyze assembly clean info help