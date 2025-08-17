# System Programming Lesson Makefile
# Demonstrates compilation with system-specific flags and feature detection

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUGFLAGS = -g -O0 -DDEBUG
LIBS = 

# Detect operating system
UNAME_S := $(shell uname -s 2>/dev/null || echo "Windows")

# Platform-specific settings
ifeq ($(UNAME_S),Linux)
    CFLAGS += -D_GNU_SOURCE
    LIBS += -lpthread
    PLATFORM = Linux
endif

ifeq ($(UNAME_S),Darwin)
    CFLAGS += -D_DARWIN_C_SOURCE
    PLATFORM = macOS
endif

ifneq (,$(findstring MINGW,$(UNAME_S)))
    CFLAGS += -D_WIN32
    PLATFORM = Windows (MinGW)
endif

ifneq (,$(findstring CYGWIN,$(UNAME_S)))
    CFLAGS += -D_WIN32
    PLATFORM = Windows (Cygwin)
endif

ifeq ($(OS),Windows_NT)
    CFLAGS += -D_WIN32
    PLATFORM = Windows
endif

# Target executable
TARGET = system_programming
SOURCE = main.c

# Default target
all: $(TARGET)
	@echo "Built for platform: $(PLATFORM)"

# Standard compilation
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)
	@echo "Compiled $(TARGET) successfully!"

# Debug build
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET)_debug $(SOURCE) $(LIBS)
	@echo "Compiled debug version: $(TARGET)_debug"

# Run the program
run: $(TARGET)
	@echo "Running System Programming demonstration..."
	@echo "=========================================="
	./$(TARGET)

# Run with sample arguments
run-args: $(TARGET)
	@echo "Running with command-line arguments..."
	@echo "====================================="
	./$(TARGET) arg1 arg2 "argument with spaces" --option=value

# Run debug version
debug-run: debug
	@echo "Starting GDB session..."
	gdb ./$(TARGET)_debug

# Test system calls (requires strace on Linux)
trace: $(TARGET)
	@echo "Tracing system calls..."
	@if command -v strace >/dev/null 2>&1; then \
		strace -c ./$(TARGET) 2>&1 | head -20; \
	elif command -v dtruss >/dev/null 2>&1; then \
		sudo dtruss ./$(TARGET) 2>&1 | head -20; \
	else \
		echo "System call tracing not available (strace/dtruss not found)"; \
		echo "Running program normally:"; \
		./$(TARGET); \
	fi

# Memory check with Valgrind
memcheck: debug
	@echo "Running memory check..."
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)_debug; \
	else \
		echo "Valgrind not found. Install valgrind for memory checking."; \
		echo "Running debug version normally:"; \
		./$(TARGET)_debug; \
	fi

# Check for required system features
check-features:
	@echo "System Feature Check"
	@echo "==================="
	@echo "Platform: $(PLATFORM)"
	@echo ""
	@echo "Checking for system features:"
	@echo -n "  fork(): "
	@if echo '#include <unistd.h>\nint main(){fork();return 0;}' | $(CC) -x c - -o /tmp/test_fork 2>/dev/null; then \
		echo "Available"; rm -f /tmp/test_fork; \
	else \
		echo "Not available"; \
	fi
	@echo -n "  signals: "
	@if echo '#include <signal.h>\nint main(){signal(SIGINT,SIG_DFL);return 0;}' | $(CC) -x c - -o /tmp/test_signal 2>/dev/null; then \
		echo "Available"; rm -f /tmp/test_signal; \
	else \
		echo "Not available"; \
	fi
	@echo -n "  POSIX file operations: "
	@if echo '#include <fcntl.h>\nint main(){open("test",O_RDONLY);return 0;}' | $(CC) -x c - -o /tmp/test_posix 2>/dev/null; then \
		echo "Available"; rm -f /tmp/test_posix; \
	else \
		echo "Not available"; \
	fi

# Show system information
sysinfo:
	@echo "System Information"
	@echo "=================="
	@echo "Compiler: $(CC)"
	@$(CC) --version | head -1
	@echo "Platform: $(PLATFORM)"
	@echo "Architecture: $(shell uname -m 2>/dev/null || echo "Unknown")"
	@echo "Kernel: $(shell uname -r 2>/dev/null || echo "Unknown")"
	@echo ""
	@echo "Process Information:"
	@echo "  Current PID: $$$$"
	@echo "  Current User: $(shell whoami 2>/dev/null || echo "Unknown")"
	@echo "  Current Directory: $(shell pwd)"
	@echo ""
	@echo "Environment Variables (sample):"
	@echo "  PATH: $(PATH)"
	@echo "  HOME: $(HOME)"
	@echo "  USER: $(USER)"

# Performance test
performance: $(TARGET)
	@echo "Performance Test"
	@echo "==============="
	@echo "Testing file operations performance..."
	@time ./$(TARGET) > /dev/null 2>&1 || echo "Performance test completed"

# Clean all generated files
clean:
	@echo "Cleaning up..."
ifeq ($(OS),Windows_NT)
	@if exist $(TARGET).exe del /Q $(TARGET).exe
	@if exist $(TARGET)_debug.exe del /Q $(TARGET)_debug.exe
	@if exist system_test.txt del /Q system_test.txt
	@if exist permission_test.txt del /Q permission_test.txt
	@if exist test_directory rmdir /S /Q test_directory
	@if exist core del /Q core
	@if exist gmon.out del /Q gmon.out
else
	@rm -f $(TARGET) $(TARGET)_debug
	@rm -f system_test.txt permission_test.txt
	@rm -rf test_directory
	@rm -f core gmon.out
endif
	@echo "Clean complete!"

# Install system dependencies (Linux only)
install-deps:
	@echo "Installing system programming tools..."
	@if command -v apt-get >/dev/null 2>&1; then \
		echo "Using apt-get (Debian/Ubuntu):"; \
		sudo apt-get update && sudo apt-get install -y build-essential gdb valgrind strace; \
	elif command -v yum >/dev/null 2>&1; then \
		echo "Using yum (Red Hat/CentOS):"; \
		sudo yum install -y gcc gdb valgrind strace; \
	elif command -v brew >/dev/null 2>&1; then \
		echo "Using Homebrew (macOS):"; \
		brew install gcc gdb; \
	else \
		echo "Package manager not found. Please install manually:"; \
		echo "  - GCC compiler"; \
		echo "  - GDB debugger"; \
		echo "  - Valgrind (memory checker)"; \
		echo "  - strace (system call tracer)"; \
	fi

# Help target
help:
	@echo "Available targets:"
	@echo "=================="
	@echo "  all          - Build standard version (default)"
	@echo "  debug        - Build with debug symbols"
	@echo "  run          - Run the program"
	@echo "  run-args     - Run with sample command-line arguments"
	@echo "  debug-run    - Run with GDB debugger"
	@echo "  trace        - Trace system calls (requires strace/dtruss)"
	@echo "  memcheck     - Run memory leak detection (requires Valgrind)"
	@echo "  check-features - Check for available system features"
	@echo "  sysinfo      - Show system and compiler information"
	@echo "  performance  - Run performance test"
	@echo "  install-deps - Install development tools (Linux/macOS)"
	@echo "  clean        - Remove all generated files"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Platform-specific notes:"
	@echo "  - Full functionality available on Linux/macOS"
	@echo "  - Limited functionality on Windows (use WSL for full experience)"
	@echo "  - Some features require administrator privileges"

# Declare phony targets
.PHONY: all debug run run-args debug-run trace memcheck check-features sysinfo performance clean install-deps help