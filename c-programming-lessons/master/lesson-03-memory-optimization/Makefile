# Memory Optimization Lesson Makefile
# Demonstrates different optimization levels and performance measurement

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUGFLAGS = -g -O0 -DDEBUG
OPTFLAGS = -O2 -march=native -mtune=native
AGGRESSIVEFLAGS = -O3 -march=native -mtune=native -funroll-loops -ffast-math
SIZEFLAGS = -Os -march=native
PROFILEFLAGS = -pg -O2

# Target executable
TARGET = memory_optimization
SOURCE = main.c

# Default target
all: $(TARGET)

# Standard compilation
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(SOURCE)
	@echo "Compiled $(TARGET).exe successfully!"

# Debug build
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET)_debug.exe $(SOURCE)
	@echo "Compiled debug version: $(TARGET)_debug.exe"

# Optimized build
optimized: $(SOURCE)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(TARGET)_opt.exe $(SOURCE)
	@echo "Compiled optimized version: $(TARGET)_opt.exe"

# Aggressively optimized build
aggressive: $(SOURCE)
	$(CC) $(CFLAGS) $(AGGRESSIVEFLAGS) -o $(TARGET)_aggressive.exe $(SOURCE)
	@echo "Compiled aggressively optimized version: $(TARGET)_aggressive.exe"

# Size-optimized build
size: $(SOURCE)
	$(CC) $(CFLAGS) $(SIZEFLAGS) -o $(TARGET)_size.exe $(SOURCE)
	@echo "Compiled size-optimized version: $(TARGET)_size.exe"

# Profile build
profile: $(SOURCE)
	$(CC) $(CFLAGS) $(PROFILEFLAGS) -o $(TARGET)_profile.exe $(SOURCE)
	@echo "Compiled profile version: $(TARGET)_profile.exe"

# Build all versions
all-versions: $(TARGET) debug optimized aggressive size profile
	@echo "Built all optimization versions"

# Run standard version
run: $(TARGET)
	@echo "Running Memory Optimization demonstration..."
	@echo "============================================"
	$(TARGET).exe

# Run optimized version
run-opt: optimized
	@echo "Running optimized version..."
	@echo "============================"
	$(TARGET)_opt.exe

# Run debug version
debug-run: debug
	@echo "Starting GDB session..."
	gdb $(TARGET)_debug.exe

# Performance benchmark comparing different optimization levels
benchmark: all-versions
	@echo "Performance Benchmark"
	@echo "===================="
	@echo ""
	@echo "Testing different optimization levels..."
	@echo ""
	@echo "Debug version (-O0):"
	@echo "-------------------"
	@time ./$(TARGET)_debug > /dev/null 2>&1 || echo "Debug test completed"
	@echo ""
	@echo "Standard version (no optimization flags):"
	@echo "----------------------------------------"
	@time ./$(TARGET) > /dev/null 2>&1 || echo "Standard test completed"
	@echo ""
	@echo "Optimized version (-O2):"
	@echo "-----------------------"
	@time ./$(TARGET)_opt > /dev/null 2>&1 || echo "Optimized test completed"
	@echo ""
	@echo "Aggressive version (-O3):"
	@echo "------------------------"
	@time ./$(TARGET)_aggressive > /dev/null 2>&1 || echo "Aggressive test completed"
	@echo ""
	@echo "Size-optimized version (-Os):"
	@echo "----------------------------"
	@time ./$(TARGET)_size > /dev/null 2>&1 || echo "Size-optimized test completed"

# Show binary sizes
sizes: all-versions
	@echo "Binary Size Comparison"
	@echo "====================="
	@echo "Version                | Size (bytes)"
	@echo "----------------------|-------------"
	@ls -l $(TARGET)* | awk '{printf "%-20s | %s\n", $$9, $$5}'

# Memory usage analysis with Valgrind
memcheck: debug
	@echo "Memory usage analysis..."
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Running Valgrind memory check:"; \
		valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TARGET)_debug; \
		echo ""; \
		echo "Running Valgrind cache analysis:"; \
		valgrind --tool=cachegrind ./$(TARGET)_debug; \
	else \
		echo "Valgrind not found. Install valgrind for memory analysis."; \
		echo "Running debug version normally:"; \
		./$(TARGET)_debug; \
	fi

# Cache performance analysis
cache-analysis: optimized
	@echo "Cache performance analysis..."
	@if command -v perf >/dev/null 2>&1; then \
		echo "Running perf cache analysis:"; \
		perf stat -e cache-references,cache-misses,L1-dcache-loads,L1-dcache-load-misses ./$(TARGET)_opt; \
	elif command -v valgrind >/dev/null 2>&1; then \
		echo "Running Valgrind cache analysis:"; \
		valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out ./$(TARGET)_opt; \
		if command -v cg_annotate >/dev/null 2>&1; then \
			cg_annotate cachegrind.out; \
		fi; \
	else \
		echo "Performance analysis tools not available."; \
		echo "Install 'perf' or 'valgrind' for cache analysis."; \
		./$(TARGET)_opt; \
	fi

# Profile with gprof
gprof-profile: profile
	@echo "Profiling with gprof..."
	./$(TARGET)_profile > /dev/null
	@if [ -f gmon.out ]; then \
		gprof $(TARGET)_profile gmon.out > profile_report.txt; \
		echo "Profile report generated: profile_report.txt"; \
		echo "Top functions by time:"; \
		head -20 profile_report.txt; \
	else \
		echo "No profiling data generated"; \
	fi

# Assembly output for optimization analysis
assembly: $(SOURCE)
	$(CC) $(CFLAGS) $(OPTFLAGS) -S -fverbose-asm -o $(TARGET).s $(SOURCE)
	@echo "Generated assembly file: $(TARGET).s"
	@echo "Use 'less $(TARGET).s' to view the optimized assembly code"

# Compiler optimization report
opt-report: $(SOURCE)
	@echo "Compiler optimization report..."
	$(CC) $(CFLAGS) $(OPTFLAGS) -fopt-info-vec -fopt-info-loop -c $(SOURCE) -o /dev/null

# System information for optimization context
sysinfo:
	@echo "System Information for Optimization"
	@echo "==================================="
	@echo "Compiler: $(CC)"
	@$(CC) --version | head -1
	@echo ""
	@echo "CPU Information:"
	@if command -v lscpu >/dev/null 2>&1; then \
		lscpu | grep -E "(Model name|CPU MHz|Cache|Architecture)"; \
	elif [ -f /proc/cpuinfo ]; then \
		grep -E "(model name|cpu MHz|cache size)" /proc/cpuinfo | head -10; \
	else \
		echo "CPU info not available on this system"; \
	fi
	@echo ""
	@echo "Memory Information:"
	@if command -v free >/dev/null 2>&1; then \
		free -h; \
	else \
		echo "Memory info not available on this system"; \
	fi
	@echo ""
	@echo "Compiler Optimization Flags:"
	@echo "  Debug:      $(DEBUGFLAGS)"
	@echo "  Optimized:  $(OPTFLAGS)"
	@echo "  Aggressive: $(AGGRESSIVEFLAGS)"
	@echo "  Size:       $(SIZEFLAGS)"

# Performance tips
tips:
	@echo "Memory Optimization Tips"
	@echo "======================="
	@echo ""
	@echo "1. Structure Optimization:"
	@echo "   - Order members by size (largest first)"
	@echo "   - Group related data together"
	@echo "   - Use packed structures sparingly"
	@echo ""
	@echo "2. Cache Optimization:"
	@echo "   - Access memory sequentially when possible"
	@echo "   - Use cache-friendly data structures"
	@echo "   - Minimize cache line conflicts"
	@echo ""
	@echo "3. Memory Allocation:"
	@echo "   - Use stack allocation for small, short-lived data"
	@echo "   - Consider memory pools for frequent allocations"
	@echo "   - Align data to cache line boundaries for critical structures"
	@echo ""
	@echo "4. Compiler Optimization:"
	@echo "   - Use -O2 for most production code"
	@echo "   - Profile before using -O3"
	@echo "   - Consider -march=native for target-specific optimization"
	@echo ""
	@echo "5. Measurement:"
	@echo "   - Always profile before optimizing"
	@echo "   - Use consistent test conditions"
	@echo "   - Measure realistic workloads"

# Clean all generated files
clean:
	@echo "Cleaning up..."
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist $(TARGET)_opt.exe del $(TARGET)_opt.exe
	@if exist $(TARGET)_aggressive.exe del $(TARGET)_aggressive.exe
	@if exist $(TARGET)_size.exe del $(TARGET)_size.exe
	@if exist $(TARGET)_profile.exe del $(TARGET)_profile.exe
	@if exist $(TARGET).s del $(TARGET).s
	@if exist gmon.out del gmon.out
	@if exist profile_report.txt del profile_report.txt
	@if exist cachegrind.out* del cachegrind.out*
	@echo "Clean complete!"

# Help target
help:
	@echo "Available targets:"
	@echo "=================="
	@echo "  all           - Build standard version (default)"
	@echo "  debug         - Build with debug symbols (-O0)"
	@echo "  optimized     - Build with standard optimization (-O2)"
	@echo "  aggressive    - Build with aggressive optimization (-O3)"
	@echo "  size          - Build optimized for size (-Os)"
	@echo "  profile       - Build with profiling support"
	@echo "  all-versions  - Build all optimization versions"
	@echo "  run           - Run the standard program"
	@echo "  run-opt       - Run the optimized version"
	@echo "  debug-run     - Run with GDB debugger"
	@echo "  benchmark     - Compare all optimization levels"
	@echo "  sizes         - Show binary size comparison"
	@echo "  memcheck      - Run memory analysis (requires Valgrind)"
	@echo "  cache-analysis- Analyze cache performance"
	@echo "  gprof-profile - Profile with gprof"
	@echo "  assembly      - Generate assembly output"
	@echo "  opt-report    - Show compiler optimization report"
	@echo "  sysinfo       - Show system information"
	@echo "  tips          - Show optimization tips"
	@echo "  clean         - Remove all generated files"
	@echo "  help          - Show this help message"

# Declare phony targets
.PHONY: all debug optimized aggressive size profile all-versions run run-opt debug-run benchmark sizes memcheck cache-analysis gprof-profile assembly opt-report sysinfo tips clean help