# Advanced Debugging Techniques Lesson Makefile
# Demonstrates compilation with various debugging tools and flags

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUGFLAGS = -g -O0 -DDEBUG -fno-omit-frame-pointer
RELEASEFLAGS = -O2 -DNDEBUG
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer
UBSANFLAGS = -fsanitize=undefined
TSANFLAGS = -fsanitize=thread
PROFILEFLAGS = -pg -O2
COVERAGEFLAGS = --coverage -O0

# Target executable
TARGET = advanced_debugging
SOURCE = main.c

# Windows executable extension
ifeq ($(OS),Windows_NT)
    EXE_EXT = .exe
else
    EXE_EXT =
endif

# Default target
all: $(TARGET)

# Standard compilation
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET)$(EXE_EXT) $(SOURCE)
	@echo "Compiled $(TARGET)$(EXE_EXT) successfully!"

# Debug build with maximum debugging information
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET)_debug$(EXE_EXT) $(SOURCE)
	@echo "Compiled debug version: $(TARGET)_debug$(EXE_EXT)"

# Release build
release: $(SOURCE)
	$(CC) $(CFLAGS) $(RELEASEFLAGS) -o $(TARGET)_release $(SOURCE)
	@echo "Compiled release version: $(TARGET)_release"

# AddressSanitizer build
asan: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(ASANFLAGS) -o $(TARGET)_asan $(SOURCE)
	@echo "Compiled AddressSanitizer version: $(TARGET)_asan"

# UndefinedBehaviorSanitizer build
ubsan: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(UBSANFLAGS) -o $(TARGET)_ubsan $(SOURCE)
	@echo "Compiled UBSanitizer version: $(TARGET)_ubsan"

# ThreadSanitizer build
tsan: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(TSANFLAGS) -o $(TARGET)_tsan $(SOURCE)
	@echo "Compiled ThreadSanitizer version: $(TARGET)_tsan"

# Profile build
profile: $(SOURCE)
	$(CC) $(CFLAGS) $(PROFILEFLAGS) -o $(TARGET)_profile $(SOURCE)
	@echo "Compiled profile version: $(TARGET)_profile"

# Coverage build
coverage: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(COVERAGEFLAGS) -o $(TARGET)_coverage $(SOURCE)
	@echo "Compiled coverage version: $(TARGET)_coverage"

# Debug build with all sanitizers (where compatible)
debug-full: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(ASANFLAGS) $(UBSANFLAGS) -o $(TARGET)_full $(SOURCE)
	@echo "Compiled full debug version: $(TARGET)_full"

# Build all versions
all-versions: $(TARGET) debug release asan ubsan profile coverage
	@echo "Built all debugging versions"

# Run standard version
run: $(TARGET)
	@echo "Running Advanced Debugging demonstration..."
	@echo "==========================================="
	./$(TARGET)$(EXE_EXT)

# Run debug version
run-debug: debug
	@echo "Running debug version..."
	@echo "========================"
	./$(TARGET)_debug$(EXE_EXT)

# Run with AddressSanitizer
run-asan: asan
	@echo "Running with AddressSanitizer..."
	@echo "================================"
	@echo "AddressSanitizer will detect memory errors at runtime"
	./$(TARGET)_asan

# Run with UndefinedBehaviorSanitizer
run-ubsan: ubsan
	@echo "Running with UndefinedBehaviorSanitizer..."
	@echo "=========================================="
	@echo "UBSanitizer will detect undefined behavior at runtime"
	./$(TARGET)_ubsan

# Run with GDB
gdb-run: debug
	@echo "Starting GDB session..."
	@echo "======================="
	@echo "Useful GDB commands:"
	@echo "  break main     - Set breakpoint at main"
	@echo "  run            - Start program"
	@echo "  step           - Step into functions"
	@echo "  next           - Step over functions"
	@echo "  print var      - Print variable value"
	@echo "  bt             - Show backtrace"
	@echo "  quit           - Exit GDB"
	gdb ./$(TARGET)_debug

# Memory check with Valgrind
valgrind: debug
	@echo "Running Valgrind memory check..."
	@echo "================================"
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Checking for memory errors and leaks:"; \
		valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		         --track-origins=yes --verbose ./$(TARGET)_debug; \
	else \
		echo "Valgrind not found. Install valgrind for memory analysis."; \
		echo "On Ubuntu/Debian: sudo apt-get install valgrind"; \
		echo "On macOS: brew install valgrind"; \
		echo "Running debug version normally:"; \
		./$(TARGET)_debug; \
	fi

# Cache analysis with Valgrind
cachegrind: debug
	@echo "Running Valgrind cache analysis..."
	@echo "=================================="
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --tool=cachegrind ./$(TARGET)_debug; \
		if command -v cg_annotate >/dev/null 2>&1; then \
			echo "Generating cache analysis report:"; \
			cg_annotate cachegrind.out.*; \
		fi; \
	else \
		echo "Valgrind not available"; \
		./$(TARGET)_debug; \
	fi

# Heap profiling with Valgrind
massif: debug
	@echo "Running Valgrind heap profiler..."
	@echo "================================="
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --tool=massif ./$(TARGET)_debug; \
		if command -v ms_print >/dev/null 2>&1; then \
			echo "Generating heap usage report:"; \
			ms_print massif.out.*; \
		fi; \
	else \
		echo "Valgrind not available"; \
		./$(TARGET)_debug; \
	fi

# Static analysis with Clang
clang-analyze: $(SOURCE)
	@echo "Running Clang static analyzer..."
	@echo "================================"
	@if command -v clang >/dev/null 2>&1; then \
		clang --analyze $(CFLAGS) $(SOURCE); \
		echo "Check for generated .plist files for analysis results"; \
	else \
		echo "Clang not found. Install clang for static analysis."; \
	fi

# Static analysis with Cppcheck
cppcheck: $(SOURCE)
	@echo "Running Cppcheck static analysis..."
	@echo "==================================="
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c11 --verbose $(SOURCE); \
	else \
		echo "Cppcheck not found. Install cppcheck for static analysis."; \
		echo "On Ubuntu/Debian: sudo apt-get install cppcheck"; \
		echo "On macOS: brew install cppcheck"; \
	fi

# Profile with gprof
gprof-profile: profile
	@echo "Profiling with gprof..."
	@echo "======================="
	./$(TARGET)_profile > /dev/null
	@if [ -f gmon.out ]; then \
		gprof $(TARGET)_profile gmon.out > profile_report.txt; \
		echo "Profile report generated: profile_report.txt"; \
		echo "Top functions by time:"; \
		head -30 profile_report.txt; \
	else \
		echo "No profiling data generated"; \
	fi

# Code coverage analysis
coverage-run: coverage
	@echo "Running code coverage analysis..."
	@echo "================================="
	./$(TARGET)_coverage > /dev/null
	@if command -v gcov >/dev/null 2>&1; then \
		gcov $(SOURCE); \
		echo "Coverage report generated: $(SOURCE).gcov"; \
		echo "Coverage summary:"; \
		grep -E "(Lines executed|Branches executed)" *.gcov || echo "Coverage data processed"; \
	else \
		echo "gcov not found. Install gcc for coverage analysis."; \
	fi

# Generate HTML coverage report
coverage-html: coverage-run
	@echo "Generating HTML coverage report..."
	@echo "=================================="
	@if command -v lcov >/dev/null 2>&1 && command -v genhtml >/dev/null 2>&1; then \
		lcov --capture --directory . --output-file coverage.info; \
		genhtml coverage.info --output-directory coverage_html; \
		echo "HTML coverage report generated in coverage_html/"; \
	else \
		echo "lcov/genhtml not found. Install lcov for HTML reports."; \
		echo "On Ubuntu/Debian: sudo apt-get install lcov"; \
		echo "On macOS: brew install lcov"; \
	fi

# System call tracing
strace: debug
	@echo "Tracing system calls..."
	@echo "======================="
	@if command -v strace >/dev/null 2>&1; then \
		strace -c ./$(TARGET)_debug 2>&1 | head -20; \
	elif command -v dtruss >/dev/null 2>&1; then \
		sudo dtruss ./$(TARGET)_debug 2>&1 | head -20; \
	else \
		echo "System call tracing not available"; \
		./$(TARGET)_debug; \
	fi

# Library call tracing
ltrace: debug
	@echo "Tracing library calls..."
	@echo "========================"
	@if command -v ltrace >/dev/null 2>&1; then \
		ltrace ./$(TARGET)_debug 2>&1 | head -20; \
	else \
		echo "ltrace not found. Install ltrace for library call tracing."; \
		echo "On Ubuntu/Debian: sudo apt-get install ltrace"; \
		./$(TARGET)_debug; \
	fi

# Show debugging information
debug-info: debug
	@echo "Debugging Information"
	@echo "===================="
	@echo "Compiler: $(CC)"
	@$(CC) --version | head -1
	@echo ""
	@echo "Debug flags: $(DEBUGFLAGS)"
	@echo "Sanitizer flags available:"
	@echo "  AddressSanitizer: $(ASANFLAGS)"
	@echo "  UBSanitizer: $(UBSANFLAGS)"
	@echo "  ThreadSanitizer: $(TSANFLAGS)"
	@echo ""
	@echo "Binary information:"
	@file $(TARGET)_debug 2>/dev/null || echo "Debug binary not found"
	@echo ""
	@echo "Available debugging tools:"
	@echo -n "  GDB: "; command -v gdb >/dev/null && echo "Available" || echo "Not found"
	@echo -n "  Valgrind: "; command -v valgrind >/dev/null && echo "Available" || echo "Not found"
	@echo -n "  Clang analyzer: "; command -v clang >/dev/null && echo "Available" || echo "Not found"
	@echo -n "  Cppcheck: "; command -v cppcheck >/dev/null && echo "Available" || echo "Not found"

# Debugging tips
tips:
	@echo "Advanced Debugging Tips"
	@echo "======================"
	@echo ""
	@echo "Compilation Tips:"
	@echo "  -g              Add debug symbols"
	@echo "  -O0             Disable optimization for debugging"
	@echo "  -Wall -Wextra   Enable comprehensive warnings"
	@echo "  -fno-omit-frame-pointer  Keep frame pointers for better backtraces"
	@echo ""
	@echo "GDB Tips:"
	@echo "  break function  Set breakpoint at function"
	@echo "  watch variable  Break when variable changes"
	@echo "  bt full         Full backtrace with local variables"
	@echo "  info locals     Show all local variables"
	@echo "  print *ptr      Dereference and print pointer"
	@echo ""
	@echo "Valgrind Tips:"
	@echo "  --leak-check=full       Detailed leak detection"
	@echo "  --show-leak-kinds=all   Show all types of leaks"
	@echo "  --track-origins=yes     Track uninitialized values"
	@echo "  --tool=cachegrind       Cache performance analysis"
	@echo ""
	@echo "Sanitizer Tips:"
	@echo "  AddressSanitizer: Detects buffer overflows, use-after-free"
	@echo "  UBSanitizer: Detects undefined behavior"
	@echo "  ThreadSanitizer: Detects race conditions"
	@echo "  MemorySanitizer: Detects uninitialized memory reads"
	@echo ""
	@echo "Debugging Strategies:"
	@echo "  1. Reproduce the bug consistently"
	@echo "  2. Use binary search to isolate the problem"
	@echo "  3. Add logging and assertions"
	@echo "  4. Use appropriate tools for the bug type"
	@echo "  5. Fix root causes, not symptoms"

# Interactive debugging session
debug-session: debug
	@echo "Starting Interactive Debugging Session"
	@echo "====================================="
	@echo "This will start GDB with some useful breakpoints set"
	@echo "Press Ctrl+C to interrupt, 'quit' to exit GDB"
	gdb -ex "break main" -ex "break debug_malloc" -ex "break debug_free" -ex "run" ./$(TARGET)_debug

# Clean all generated files
clean:
	@echo "Cleaning up debugging files..."
	@if exist $(TARGET).exe del $(TARGET).exe
	@if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	@if exist $(TARGET)_release.exe del $(TARGET)_release.exe
	@if exist $(TARGET)_asan.exe del $(TARGET)_asan.exe
	@if exist $(TARGET)_ubsan.exe del $(TARGET)_ubsan.exe
	@if exist $(TARGET)_tsan.exe del $(TARGET)_tsan.exe
	@if exist $(TARGET)_profile.exe del $(TARGET)_profile.exe
	@if exist $(TARGET)_coverage.exe del $(TARGET)_coverage.exe
	@if exist $(TARGET)_full.exe del $(TARGET)_full.exe
	@if exist gmon.out del gmon.out
	@if exist profile_report.txt del profile_report.txt
	@if exist *.gcov del *.gcov
	@if exist *.gcda del *.gcda
	@if exist *.gcno del *.gcno
	@if exist coverage.info del coverage.info
	@if exist cachegrind.out.* del cachegrind.out.*
	@if exist massif.out.* del massif.out.*
	@if exist *.plist del *.plist
	@if exist coverage_html rmdir /s /q coverage_html
	@echo "Clean complete!"

# Help target
help:
	@echo "Available targets:"
	@echo "=================="
	@echo "  all           - Build standard version (default)"
	@echo "  debug         - Build with debug symbols and no optimization"
	@echo "  release       - Build optimized release version"
	@echo "  asan          - Build with AddressSanitizer"
	@echo "  ubsan         - Build with UndefinedBehaviorSanitizer"
	@echo "  tsan          - Build with ThreadSanitizer"
	@echo "  profile       - Build with profiling support"
	@echo "  coverage      - Build with code coverage support"
	@echo "  debug-full    - Build with multiple sanitizers"
	@echo "  all-versions  - Build all debugging versions"
	@echo ""
	@echo "Execution targets:"
	@echo "  run           - Run standard version"
	@echo "  run-debug     - Run debug version"
	@echo "  run-asan      - Run with AddressSanitizer"
	@echo "  run-ubsan     - Run with UndefinedBehaviorSanitizer"
	@echo "  gdb-run       - Run with GDB debugger"
	@echo ""
	@echo "Analysis targets:"
	@echo "  valgrind      - Run Valgrind memory check"
	@echo "  cachegrind    - Run Valgrind cache analysis"
	@echo "  massif        - Run Valgrind heap profiler"
	@echo "  clang-analyze - Run Clang static analyzer"
	@echo "  cppcheck      - Run Cppcheck static analysis"
	@echo "  gprof-profile - Profile with gprof"
	@echo "  coverage-run  - Run code coverage analysis"
	@echo "  coverage-html - Generate HTML coverage report"
	@echo "  strace        - Trace system calls"
	@echo "  ltrace        - Trace library calls"
	@echo ""
	@echo "Utility targets:"
	@echo "  debug-info    - Show debugging tool information"
	@echo "  tips          - Show debugging tips and tricks"
	@echo "  debug-session - Start interactive debugging session"
	@echo "  clean         - Remove all generated files"
	@echo "  help          - Show this help message"

# Declare phony targets
.PHONY: all debug release asan ubsan tsan profile coverage debug-full all-versions run run-debug run-asan run-ubsan gdb-run valgrind cachegrind massif clang-analyze cppcheck gprof-profile coverage-run coverage-html strace ltrace debug-info tips debug-session clean help