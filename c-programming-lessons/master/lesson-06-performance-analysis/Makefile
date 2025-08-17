# Performance Analysis Lesson Makefile
# Demonstrates compilation with profiling and performance measurement tools

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUGFLAGS = -g -O0 -DDEBUG
OPTFLAGS = -O2 -march=native -mtune=native
FASTFLAGS = -O3 -march=native -mtune=native -funroll-loops
PROFILEFLAGS = -pg -O2
MATHLIB = -lm

# Platform-specific libraries
UNAME_S := $(shell uname -s 2>/dev/null || echo "Windows")
ifeq ($(OS),Windows_NT)
    SYSLIBS = 
else
    SYSLIBS = -lrt
endif

# Target executable
TARGET = performance_analysis
SOURCE = main.c

# Default target
all: $(TARGET)

# Standard compilation
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(MATHLIB) $(SYSLIBS)
	@echo "Compiled $(TARGET) successfully!"

# Debug build
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET)_debug $(SOURCE) $(MATHLIB) $(SYSLIBS)
	@echo "Compiled debug version: $(TARGET)_debug"

# Optimized build
optimized: $(SOURCE)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(TARGET)_opt $(SOURCE) $(MATHLIB) $(SYSLIBS)
	@echo "Compiled optimized version: $(TARGET)_opt"

# Fast build with aggressive optimization
fast: $(SOURCE)
	$(CC) $(CFLAGS) $(FASTFLAGS) -o $(TARGET)_fast $(SOURCE) $(MATHLIB) $(SYSLIBS)
	@echo "Compiled fast version: $(TARGET)_fast"

# Profile build with gprof
profile: $(SOURCE)
	$(CC) $(CFLAGS) $(PROFILEFLAGS) -o $(TARGET)_profile $(SOURCE) $(MATHLIB) $(SYSLIBS)
	@echo "Compiled profile version: $(TARGET)_profile"

# Build all versions
all-versions: $(TARGET) debug optimized fast profile
	@echo "Built all performance analysis versions"

# Run standard version
run: $(TARGET)
	@echo "Running Performance Analysis demonstration..."
	@echo "============================================="
	./$(TARGET)

# Run optimized version
run-opt: optimized
	@echo "Running optimized version..."
	@echo "============================"
	./$(TARGET)_opt

# Run debug version
debug-run: debug
	@echo "Running debug version..."
	@echo "========================"
	./$(TARGET)_debug

# Performance benchmark comparing all versions
benchmark: all-versions
	@echo "Performance Benchmark Comparison"
	@echo "================================"
	@echo ""
	@echo "Testing different optimization levels..."
	@echo ""
	@echo "Debug version (-O0):"
	@echo "-------------------"
	@time ./$(TARGET)_debug > /dev/null 2>&1 || echo "Debug benchmark completed"
	@echo ""
	@echo "Standard version:"
	@echo "----------------"
	@time ./$(TARGET) > /dev/null 2>&1 || echo "Standard benchmark completed"
	@echo ""
	@echo "Optimized version (-O2):"
	@echo "-----------------------"
	@time ./$(TARGET)_opt > /dev/null 2>&1 || echo "Optimized benchmark completed"
	@echo ""
	@echo "Fast version (-O3):"
	@echo "------------------"
	@time ./$(TARGET)_fast > /dev/null 2>&1 || echo "Fast benchmark completed"

# Profile with gprof
gprof-profile: profile
	@echo "Profiling with gprof..."
	@echo "======================="
	./$(TARGET)_profile > /dev/null
	@if [ -f gmon.out ]; then \
		gprof $(TARGET)_profile gmon.out > gprof_report.txt; \
		echo "gprof report generated: gprof_report.txt"; \
		echo ""; \
		echo "Top functions by time:"; \
		echo "====================="; \
		head -30 gprof_report.txt | grep -E "(time|seconds|calls)" || head -30 gprof_report.txt; \
	else \
		echo "No profiling data generated"; \
	fi

# Profile with perf (Linux only)
perf-profile: optimized
	@echo "Profiling with perf..."
	@echo "====================="
	@if command -v perf >/dev/null 2>&1; then \
		echo "Recording performance data..."; \
		perf record -g ./$(TARGET)_opt > /dev/null 2>&1; \
		echo "Generating performance report..."; \
		perf report --stdio > perf_report.txt 2>/dev/null; \
		echo "Performance report generated: perf_report.txt"; \
		echo ""; \
		echo "Top hotspots:"; \
		echo "============"; \
		head -20 perf_report.txt; \
	else \
		echo "perf not available on this system"; \
		echo "Install perf tools: sudo apt-get install linux-tools-generic"; \
	fi

# Hardware performance counters with perf
perf-stat: optimized
	@echo "Hardware Performance Counter Analysis"
	@echo "===================================="
	@if command -v perf >/dev/null 2>&1; then \
		echo "Running performance counter analysis..."; \
		perf stat -e instructions,cycles,cache-references,cache-misses,branch-instructions,branch-misses ./$(TARGET)_opt; \
	else \
		echo "perf not available - running standard version"; \
		./$(TARGET)_opt; \
	fi

# Memory performance analysis with Valgrind
memory-profile: debug
	@echo "Memory Performance Analysis"
	@echo "==========================="
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Running Valgrind memory profiler..."; \
		valgrind --tool=massif --massif-out-file=massif.out ./$(TARGET)_debug > /dev/null 2>&1; \
		if command -v ms_print >/dev/null 2>&1; then \
			echo "Generating memory usage report..."; \
			ms_print massif.out > memory_report.txt; \
			echo "Memory report generated: memory_report.txt"; \
			echo ""; \
			echo "Memory usage summary:"; \
			echo "===================="; \
			head -20 memory_report.txt; \
		fi; \
	else \
		echo "Valgrind not available"; \
		echo "Install: sudo apt-get install valgrind"; \
		./$(TARGET)_debug > /dev/null; \
	fi

# Cache performance analysis
cache-analysis: optimized
	@echo "Cache Performance Analysis"
	@echo "=========================="
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Running cache analysis..."; \
		valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out ./$(TARGET)_opt > /dev/null 2>&1; \
		if command -v cg_annotate >/dev/null 2>&1; then \
			echo "Generating cache analysis report..."; \
			cg_annotate cachegrind.out > cache_report.txt; \
			echo "Cache report generated: cache_report.txt"; \
			echo ""; \
			echo "Cache performance summary:"; \
			echo "========================="; \
			head -20 cache_report.txt; \
		fi; \
	elif command -v perf >/dev/null 2>&1; then \
		echo "Using perf for cache analysis..."; \
		perf stat -e L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-misses ./$(TARGET)_opt; \
	else \
		echo "Cache analysis tools not available"; \
		./$(TARGET)_opt; \
	fi

# Comprehensive performance report
performance-report: all-versions
	@echo "Comprehensive Performance Report" > performance_summary.txt
	@echo "================================" >> performance_summary.txt
	@echo "" >> performance_summary.txt
	@echo "System Information:" >> performance_summary.txt
	@echo "==================" >> performance_summary.txt
	@echo "Compiler: $(CC)" >> performance_summary.txt
	@$(CC) --version | head -1 >> performance_summary.txt 2>/dev/null || echo "Compiler version unavailable" >> performance_summary.txt
	@echo "Platform: $(UNAME_S)" >> performance_summary.txt
	@echo "Date: $$(date)" >> performance_summary.txt
	@echo "" >> performance_summary.txt
	@echo "Binary Sizes:" >> performance_summary.txt
	@echo "============" >> performance_summary.txt
	@ls -la $(TARGET)* | awk '{printf "%-20s %8s bytes\n", $$9, $$5}' >> performance_summary.txt 2>/dev/null || echo "Binary size info unavailable" >> performance_summary.txt
	@echo "" >> performance_summary.txt
	@echo "Performance report generated: performance_summary.txt"
	@echo "Run 'make gprof-profile' and 'make perf-profile' for detailed analysis"

# Flame graph generation (requires FlameGraph tools)
flamegraph: optimized
	@echo "Generating Flame Graph..."
	@echo "========================"
	@if command -v perf >/dev/null 2>&1; then \
		if command -v stackcollapse-perf.pl >/dev/null 2>&1 && command -v flamegraph.pl >/dev/null 2>&1; then \
			echo "Recording performance data for flame graph..."; \
			perf record -g ./$(TARGET)_opt > /dev/null 2>&1; \
			echo "Generating flame graph..."; \
			perf script | stackcollapse-perf.pl | flamegraph.pl > flamegraph.svg; \
			echo "Flame graph generated: flamegraph.svg"; \
			echo "Open flamegraph.svg in a web browser to view"; \
		else \
			echo "FlameGraph tools not found"; \
			echo "Install from: https://github.com/brendangregg/FlameGraph"; \
		fi; \
	else \
		echo "perf not available for flame graph generation"; \
	fi

# Show binary sizes
sizes: all-versions
	@echo "Binary Size Analysis"
	@echo "==================="
	@echo "Version                | Size (bytes) | Stripped Size"
	@echo "----------------------|--------------|---------------"
	@for binary in $(TARGET)*; do \
		if [ -f "$$binary" ]; then \
			size=$$(stat -f%z "$$binary" 2>/dev/null || stat -c%s "$$binary" 2>/dev/null || echo "N/A"); \
			printf "%-20s | %12s |" "$$binary" "$$size"; \
			if command -v strip >/dev/null 2>&1; then \
				cp "$$binary" "$$binary.tmp"; \
				strip "$$binary.tmp" 2>/dev/null; \
				stripped_size=$$(stat -f%z "$$binary.tmp" 2>/dev/null || stat -c%s "$$binary.tmp" 2>/dev/null || echo "N/A"); \
				printf " %13s\n" "$$stripped_size"; \
				rm -f "$$binary.tmp"; \
			else \
				printf " %13s\n" "N/A"; \
			fi; \
		fi; \
	done

# Assembly output for optimization analysis
assembly: $(SOURCE)
	$(CC) $(CFLAGS) $(OPTFLAGS) -S -fverbose-asm -o $(TARGET).s $(SOURCE)
	@echo "Generated assembly file: $(TARGET).s"
	@echo "Use 'less $(TARGET).s' to view optimized assembly code"

# Compiler optimization report
opt-report: $(SOURCE)
	@echo "Compiler Optimization Report"
	@echo "============================"
	@echo "Analyzing optimization opportunities..."
	$(CC) $(CFLAGS) $(OPTFLAGS) -fopt-info-vec -fopt-info-loop -fopt-info-inline -c $(SOURCE) -o /dev/null 2>&1 || echo "Optimization analysis completed"

# Performance tips and best practices
tips:
	@echo "Performance Analysis Tips and Best Practices"
	@echo "============================================"
	@echo ""
	@echo "Measurement Tips:"
	@echo "  - Run multiple iterations for statistical significance"
	@echo "  - Warm up caches before timing critical sections"
	@echo "  - Use appropriate timing resolution for your measurements"
	@echo "  - Control system load during benchmarking"
	@echo ""
	@echo "Profiling Tools:"
	@echo "  gprof:    Function-level profiling with call graphs"
	@echo "  perf:     Hardware performance counters and sampling"
	@echo "  Valgrind: Memory usage and cache behavior analysis"
	@echo "  VTune:    Intel's advanced profiling suite"
	@echo ""
	@echo "Optimization Strategy:"
	@echo "  1. Profile first - identify actual bottlenecks"
	@echo "  2. Algorithm optimization has biggest impact"
	@echo "  3. Data structure and memory layout optimization"
	@echo "  4. Compiler optimization flags (-O2, -O3, -march=native)"
	@echo "  5. Platform-specific optimizations"
	@echo ""
	@echo "Common Performance Issues:"
	@echo "  - Cache misses from poor memory access patterns"
	@echo "  - Inefficient algorithms (O(n²) instead of O(n log n))"
	@echo "  - Excessive memory allocation/deallocation"
	@echo "  - Branch mispredictions in tight loops"
	@echo "  - I/O bottlenecks and blocking operations"
	@echo ""
	@echo "Compiler Flags:"
	@echo "  -O0:           No optimization (debugging)"
	@echo "  -O1:           Basic optimizations"
	@echo "  -O2:           Standard optimizations (recommended)"
	@echo "  -O3:           Aggressive optimizations"
	@echo "  -march=native: Target current CPU architecture"
	@echo "  -pg:           Enable gprof profiling"

# System performance information
sysinfo:
	@echo "System Performance Information"
	@echo "=============================="
	@echo "Compiler: $(CC)"
	@$(CC) --version | head -1 2>/dev/null || echo "Compiler version unavailable"
	@echo "Platform: $(UNAME_S)"
	@echo ""
	@echo "CPU Information:"
	@if command -v lscpu >/dev/null 2>&1; then \
		lscpu | grep -E "(Model name|CPU MHz|Cache|Architecture)"; \
	elif [ -f /proc/cpuinfo ]; then \
		grep -E "(model name|cpu MHz|cache size)" /proc/cpuinfo | head -5; \
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
	@echo "Available Performance Tools:"
	@echo -n "  gprof: "; command -v gprof >/dev/null && echo "Available" || echo "Not found"
	@echo -n "  perf: "; command -v perf >/dev/null && echo "Available" || echo "Not found"
	@echo -n "  valgrind: "; command -v valgrind >/dev/null && echo "Available" || echo "Not found"
	@echo -n "  time: "; command -v time >/dev/null && echo "Available" || echo "Not found"

# Interactive performance analysis
interactive: optimized
	@echo "Interactive Performance Analysis"
	@echo "==============================="
	@echo "This will run the optimized version and show real-time performance"
	@echo "Press Ctrl+C to stop monitoring"
	@if command -v top >/dev/null 2>&1; then \
		echo "Starting performance monitoring..."; \
		(./$(TARGET)_opt > /dev/null &) && top -p $$!; \
	else \
		echo "Performance monitoring not available"; \
		./$(TARGET)_opt; \
	fi

# Clean all generated files
clean:
	@echo "Cleaning up performance analysis files..."
	@rm -f $(TARGET) $(TARGET)_debug $(TARGET)_opt $(TARGET)_fast $(TARGET)_profile
	@rm -f $(TARGET).s gmon.out gprof_report.txt perf_report.txt
	@rm -f memory_report.txt cache_report.txt performance_summary.txt
	@rm -f massif.out cachegrind.out perf.data* flamegraph.svg
	@rm -f performance_test.dat
	@echo "Clean complete!"

# Help target
help:
	@echo "Available targets:"
	@echo "=================="
	@echo "  all              - Build standard version (default)"
	@echo "  debug            - Build with debug symbols"
	@echo "  optimized        - Build with optimization (-O2)"
	@echo "  fast             - Build with aggressive optimization (-O3)"
	@echo "  profile          - Build with profiling support"
	@echo "  all-versions     - Build all optimization versions"
	@echo ""
	@echo "Execution targets:"
	@echo "  run              - Run standard version"
	@echo "  run-opt          - Run optimized version"
	@echo "  debug-run        - Run debug version"
	@echo "  benchmark        - Compare all versions"
	@echo ""
	@echo "Profiling targets:"
	@echo "  gprof-profile    - Profile with gprof"
	@echo "  perf-profile     - Profile with perf (Linux)"
	@echo "  perf-stat        - Hardware performance counters"
	@echo "  memory-profile   - Memory usage analysis"
	@echo "  cache-analysis   - Cache performance analysis"
	@echo "  flamegraph       - Generate flame graph visualization"
	@echo ""
	@echo "Analysis targets:"
	@echo "  performance-report - Generate comprehensive report"
	@echo "  sizes            - Show binary size comparison"
	@echo "  assembly         - Generate assembly output"
	@echo "  opt-report       - Show compiler optimization report"
	@echo ""
	@echo "Utility targets:"
	@echo "  tips             - Show performance tips"
	@echo "  sysinfo          - Show system information"
	@echo "  interactive      - Interactive performance monitoring"
	@echo "  clean            - Remove all generated files"
	@echo "  help             - Show this help message"

# Declare phony targets
.PHONY: all debug optimized fast profile all-versions run run-opt debug-run benchmark gprof-profile perf-profile perf-stat memory-profile cache-analysis performance-report flamegraph sizes assembly opt-report tips sysinfo interactive clean help