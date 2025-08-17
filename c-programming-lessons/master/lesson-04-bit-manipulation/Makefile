# Bit Manipulation Lesson Makefile
# Demonstrates compilation with bit manipulation optimizations

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUGFLAGS = -g -O0 -DDEBUG
OPTFLAGS = -O2 -march=native -mtune=native
FASTFLAGS = -O3 -march=native -mtune=native -funroll-loops
PROFILEFLAGS = -pg -O2

# Target executable
TARGET = bit_manipulation
SOURCE = main.c

# Default target
all: $(TARGET)

# Standard compilation
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Compiled $(TARGET) successfully!"

# Debug build
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET)_debug $(SOURCE)
	@echo "Compiled debug version: $(TARGET)_debug"

# Optimized build
optimized: $(SOURCE)
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(TARGET)_opt $(SOURCE)
	@echo "Compiled optimized version: $(TARGET)_opt"

# Fast build with aggressive optimization
fast: $(SOURCE)
	$(CC) $(CFLAGS) $(FASTFLAGS) -o $(TARGET)_fast $(SOURCE)
	@echo "Compiled fast version: $(TARGET)_fast"

# Profile build
profile: $(SOURCE)
	$(CC) $(CFLAGS) $(PROFILEFLAGS) -o $(TARGET)_profile $(SOURCE)
	@echo "Compiled profile version: $(TARGET)_profile"

# Build all versions
all-versions: $(TARGET) debug optimized fast profile
	@echo "Built all versions"

# Run standard version
run: $(TARGET)
	@echo "Running Bit Manipulation demonstration..."
	@echo "========================================="
	./$(TARGET)

# Run optimized version
run-opt: optimized
	@echo "Running optimized version..."
	@echo "============================"
	./$(TARGET)_opt

# Run debug version
debug-run: debug
	@echo "Starting GDB session..."
	gdb ./$(TARGET)_debug

# Performance benchmark
benchmark: all-versions
	@echo "Bit Manipulation Performance Benchmark"
	@echo "======================================"
	@echo ""
	@echo "Debug version (-O0):"
	@echo "-------------------"
	@time ./$(TARGET)_debug > /dev/null 2>&1 || echo "Debug test completed"
	@echo ""
	@echo "Standard version:"
	@echo "----------------"
	@time ./$(TARGET) > /dev/null 2>&1 || echo "Standard test completed"
	@echo ""
	@echo "Optimized version (-O2):"
	@echo "-----------------------"
	@time ./$(TARGET)_opt > /dev/null 2>&1 || echo "Optimized test completed"
	@echo ""
	@echo "Fast version (-O3):"
	@echo "------------------"
	@time ./$(TARGET)_fast > /dev/null 2>&1 || echo "Fast test completed"

# Show binary sizes
sizes: all-versions
	@echo "Binary Size Comparison"
	@echo "====================="
	@ls -la $(TARGET)* | awk 'NR>1 {printf "%-20s %8s bytes\n", $$9, $$5}'

# Assembly output for bit manipulation analysis
assembly: $(SOURCE)
	$(CC) $(CFLAGS) $(OPTFLAGS) -S -fverbose-asm -o $(TARGET).s $(SOURCE)
	@echo "Generated assembly file: $(TARGET).s"
	@echo "Look for bit manipulation optimizations in the assembly code"

# Show compiler optimization report
opt-report: $(SOURCE)
	@echo "Compiler optimization report for bit operations..."
	$(CC) $(CFLAGS) $(OPTFLAGS) -fopt-info-vec -fopt-info-loop -fopt-info-inline -c $(SOURCE) -o /dev/null

# Test bit manipulation functions
test-functions: optimized
	@echo "Testing bit manipulation functions..."
	@echo "===================================="
	@echo "Running function tests:"
	./$(TARGET)_opt | grep -E "(set bits|power of two|First set bit|Reversed bits)"

# Memory usage analysis
memcheck: debug
	@echo "Memory usage analysis..."
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Running Valgrind memory check:"; \
		valgrind --tool=memcheck --leak-check=full ./$(TARGET)_debug > /dev/null; \
	else \
		echo "Valgrind not found. Install valgrind for memory analysis."; \
		./$(TARGET)_debug > /dev/null; \
	fi

# Profile with gprof
gprof-profile: profile
	@echo "Profiling bit manipulation performance..."
	./$(TARGET)_profile > /dev/null
	@if [ -f gmon.out ]; then \
		gprof $(TARGET)_profile gmon.out > profile_report.txt; \
		echo "Profile report generated: profile_report.txt"; \
		echo "Top functions by time:"; \
		head -20 profile_report.txt | grep -E "(time|seconds|calls)"; \
	else \
		echo "No profiling data generated"; \
	fi

# Bit manipulation tips and tricks
tips:
	@echo "Bit Manipulation Tips and Tricks"
	@echo "================================"
	@echo ""
	@echo "Common Patterns:"
	@echo "  Set bit n:     x |= (1 << n)"
	@echo "  Clear bit n:   x &= ~(1 << n)"
	@echo "  Toggle bit n:  x ^= (1 << n)"
	@echo "  Check bit n:   (x >> n) & 1"
	@echo ""
	@echo "Performance Tips:"
	@echo "  - Use shifts instead of multiply/divide by powers of 2"
	@echo "  - Use x & (x-1) to check if x is power of 2"
	@echo "  - Use x & -x to isolate rightmost set bit"
	@echo "  - Use x ^ (x >> 1) for binary to Gray code conversion"
	@echo ""
	@echo "Common Mistakes:"
	@echo "  - Shifting by >= width of type (undefined behavior)"
	@echo "  - Sign extension with right shift of negative numbers"
	@echo "  - Forgetting operator precedence (use parentheses)"
	@echo "  - Bit field portability issues across compilers"
	@echo ""
	@echo "Optimization Flags:"
	@echo "  -O2: Good balance of optimization and compile time"
	@echo "  -O3: More aggressive, may increase code size"
	@echo "  -march=native: Use target CPU's instruction set"
	@echo "  -funroll-loops: Unroll loops for better performance"

# Show system information relevant to bit manipulation
sysinfo:
	@echo "System Information for Bit Manipulation"
	@echo "======================================="
	@echo "Compiler: $(CC)"
	@$(CC) --version | head -1
	@echo ""
	@echo "Word sizes:"
	@echo "  char:      $(shell echo 'int main(){printf(\"%zu\", sizeof(char)); return 0;}' | $(CC) -x c - -o /tmp/test && /tmp/test && rm -f /tmp/test) bytes"
	@echo "  short:     $(shell echo 'int main(){printf(\"%zu\", sizeof(short)); return 0;}' | $(CC) -x c - -o /tmp/test && /tmp/test && rm -f /tmp/test) bytes"
	@echo "  int:       $(shell echo 'int main(){printf(\"%zu\", sizeof(int)); return 0;}' | $(CC) -x c - -o /tmp/test && /tmp/test && rm -f /tmp/test) bytes"
	@echo "  long:      $(shell echo 'int main(){printf(\"%zu\", sizeof(long)); return 0;}' | $(CC) -x c - -o /tmp/test && /tmp/test && rm -f /tmp/test) bytes"
	@echo "  long long: $(shell echo 'int main(){printf(\"%zu\", sizeof(long long)); return 0;}' | $(CC) -x c - -o /tmp/test && /tmp/test && rm -f /tmp/test) bytes"
	@echo "  pointer:   $(shell echo 'int main(){printf(\"%zu\", sizeof(void*)); return 0;}' | $(CC) -x c - -o /tmp/test && /tmp/test && rm -f /tmp/test) bytes"
	@echo ""
	@echo "Endianness test:"
	@echo 'int main(){int x=1; printf("%s\\n", *(char*)&x ? "Little Endian" : "Big Endian"); return 0;}' | $(CC) -x c - -o /tmp/endian && /tmp/endian && rm -f /tmp/endian
	@echo ""
	@echo "Built-in functions available:"
	@echo -n "  __builtin_popcount: "
	@echo 'int main(){return __builtin_popcount(15);}' | $(CC) -x c - -o /tmp/test 2>/dev/null && echo "Yes" && rm -f /tmp/test || echo "No"
	@echo -n "  __builtin_clz: "
	@echo 'int main(){return __builtin_clz(1);}' | $(CC) -x c - -o /tmp/test 2>/dev/null && echo "Yes" && rm -f /tmp/test || echo "No"

# Interactive bit manipulation calculator
calculator:
	@echo "Simple Bit Manipulation Calculator"
	@echo "=================================="
	@echo "Enter two numbers and see bitwise operations:"
	@read -p "First number (decimal): " a; \
	read -p "Second number (decimal): " b; \
	echo "Results:"; \
	echo "  $$a AND $$b = $$((a & b))"; \
	echo "  $$a OR $$b = $$((a | b))"; \
	echo "  $$a XOR $$b = $$((a ^ b))"; \
	echo "  NOT $$a = $$((~a))"; \
	echo "  $$a << 1 = $$((a << 1))"; \
	echo "  $$a >> 1 = $$((a >> 1))"

# Clean all generated files
clean:
	@echo "Cleaning up..."
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist $(TARGET)_opt.exe del $(TARGET)_opt.exe
	@if exist $(TARGET)_fast.exe del $(TARGET)_fast.exe
	@if exist $(TARGET)_profile.exe del $(TARGET)_profile.exe
	@if exist $(TARGET).s del $(TARGET).s
	@if exist gmon.out del gmon.out
	@if exist profile_report.txt del profile_report.txt
	@echo "Clean complete!"

# Help target
help:
	@echo "Available targets:"
	@echo "=================="
	@echo "  all           - Build standard version (default)"
	@echo "  debug         - Build with debug symbols"
	@echo "  optimized     - Build with optimization (-O2)"
	@echo "  fast          - Build with aggressive optimization (-O3)"
	@echo "  profile       - Build with profiling support"
	@echo "  all-versions  - Build all optimization versions"
	@echo "  run           - Run the standard program"
	@echo "  run-opt       - Run the optimized version"
	@echo "  debug-run     - Run with GDB debugger"
	@echo "  benchmark     - Compare performance of all versions"
	@echo "  sizes         - Show binary size comparison"
	@echo "  assembly      - Generate assembly output"
	@echo "  opt-report    - Show compiler optimization report"
	@echo "  test-functions- Test specific bit manipulation functions"
	@echo "  memcheck      - Run memory analysis (requires Valgrind)"
	@echo "  gprof-profile - Profile with gprof"
	@echo "  tips          - Show bit manipulation tips and tricks"
	@echo "  sysinfo       - Show system information"
	@echo "  calculator    - Interactive bit manipulation calculator"
	@echo "  clean         - Remove all generated files"
	@echo "  help          - Show this help message"

# Declare phony targets
.PHONY: all debug optimized fast profile all-versions run run-opt debug-run benchmark sizes assembly opt-report test-functions memcheck gprof-profile tips sysinfo calculator clean help