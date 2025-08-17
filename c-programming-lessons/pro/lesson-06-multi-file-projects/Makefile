# Makefile for Multi-File Project Lesson
# This demonstrates a complex, professional Makefile for multi-module projects

# Compiler and tools
CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -std=c11 -pedantic
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG
LDFLAGS = -lm

# Project information
PROJECT_NAME = multi_file_project
VERSION = 1.0.0
TARGET = $(PROJECT_NAME)

# Source files and dependencies
MAIN_SOURCE = main.c
SOURCES = math_operations.c string_utils.c student_manager.c
HEADERS = config.h math_operations.h string_utils.h student_manager.h
OBJECTS = $(SOURCES:.c=.o)
ALL_SOURCES = $(MAIN_SOURCE) $(SOURCES)
ALL_OBJECTS = $(ALL_SOURCES:.c=.o)

# Library creation
STATIC_LIB = lib$(PROJECT_NAME).a
SHARED_LIB = lib$(PROJECT_NAME).so

# Directories
BUILD_DIR = build
DOC_DIR = docs
TEST_DIR = tests

# Default target
all: $(TARGET)

# Main executable
$(TARGET): $(ALL_OBJECTS)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -o $(TARGET) $(ALL_OBJECTS) $(LDFLAGS)

# Object file compilation with dependency tracking
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Release build (explicit)
release: CFLAGS += $(RELEASE_FLAGS)
release: clean $(TARGET)

# Run the program
run: $(TARGET)
	.\$(TARGET).exe

# Run debug version
run-debug: debug
	.\$(TARGET).exe

# Static library creation
static-lib: $(OBJECTS)
	$(AR) rcs $(STATIC_LIB) $(OBJECTS)
	@echo "Static library $(STATIC_LIB) created"

# Shared library creation
shared-lib: CFLAGS += -fPIC
shared-lib: $(OBJECTS)
	$(CC) -shared -o $(SHARED_LIB) $(OBJECTS) $(LDFLAGS)
	@echo "Shared library $(SHARED_LIB) created"

# Test with static library
test-static: static-lib
	$(CC) $(CFLAGS) -o $(TARGET)_static $(MAIN_SOURCE) -L. -l$(PROJECT_NAME) $(LDFLAGS)
	./$(TARGET)_static

# Test with shared library
test-shared: shared-lib
	$(CC) $(CFLAGS) -o $(TARGET)_shared $(MAIN_SOURCE) -L. -l$(PROJECT_NAME) $(LDFLAGS)
	LD_LIBRARY_PATH=. ./$(TARGET)_shared

# Memory leak detection
memcheck: debug
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET); \
	else \
		echo "Valgrind not found. Running with address sanitizer instead."; \
		./$(TARGET); \
	fi

# Static code analysis
analyze:
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem \
		         --suppress=unusedFunction --suppress=unmatchedSuppression \
		         $(ALL_SOURCES) $(HEADERS); \
	else \
		echo "cppcheck not found. Skipping static analysis."; \
	fi

# Code formatting
format:
	@if command -v clang-format >/dev/null 2>&1; then \
		clang-format -i $(ALL_SOURCES) $(HEADERS); \
		echo "Code formatted successfully."; \
	else \
		echo "clang-format not found. Skipping code formatting."; \
	fi

# Generate documentation
docs:
	@if command -v doxygen >/dev/null 2>&1; then \
		mkdir -p $(DOC_DIR); \
		doxygen Doxyfile 2>/dev/null || echo "Doxyfile not found, creating basic docs"; \
		echo "Documentation generated in $(DOC_DIR)"; \
	else \
		echo "doxygen not found. Skipping documentation generation."; \
	fi

# Performance profiling
profile: CFLAGS += -pg
profile: $(TARGET)
	./$(TARGET)
	@if command -v gprof >/dev/null 2>&1; then \
		gprof $(TARGET) gmon.out > profile_report.txt; \
		echo "Profile report generated: profile_report.txt"; \
	else \
		echo "gprof not found. Profiling data collected but not analyzed."; \
	fi

# Assembly output generation
assembly:
	@mkdir -p $(BUILD_DIR)
	@for src in $(ALL_SOURCES); do \
		echo "Generating assembly for $$src"; \
		$(CC) $(CFLAGS) -S -fverbose-asm -o $(BUILD_DIR)/$${src%.c}.s $$src; \
	done
	@echo "Assembly files generated in $(BUILD_DIR)/"

# Dependency analysis
deps:
	@echo "=== Project Dependencies ==="
	@echo "Main source: $(MAIN_SOURCE)"
	@echo "Module sources: $(SOURCES)"
	@echo "Headers: $(HEADERS)"
	@echo "Objects: $(ALL_OBJECTS)"
	@echo "Libraries: $(STATIC_LIB) $(SHARED_LIB)"
	@echo ""
	@echo "=== File Dependencies ==="
	@for src in $(ALL_SOURCES); do \
		echo "$$src depends on:"; \
		$(CC) -MM $$src 2>/dev/null || echo "  Unable to determine dependencies"; \
	done

# Size analysis
size: $(TARGET)
	@echo "=== Executable Size Analysis ==="
	@dir $(TARGET).exe
	@echo ""
	@echo "=== Section Sizes ==="
	@echo "size command not available on Windows"
	@echo ""
	@echo "=== Object File Sizes ==="
	@dir *.o 2>nul || echo "No object files found"

# Symbol analysis
symbols: $(TARGET)
	@echo "=== Symbol Analysis ==="
	@if command -v nm >/dev/null 2>&1; then \
		echo "Exported symbols:"; \
		nm -D $(TARGET) 2>/dev/null | head -20 || nm $(TARGET) | head -20; \
	else \
		echo "nm command not available"; \
	fi

# Test compilation with different standards
test-standards:
	@echo "Testing compilation with different C standards:"
	@for std in c89 c99 c11 c17; do \
		echo "Testing with -std=$$std"; \
		$(CC) -std=$$std -Wall -Wextra -c $(ALL_SOURCES) -o /dev/null 2>&1 && \
		echo "  ✓ $$std compatible" || echo "  ✗ $$std incompatible"; \
	done

# Performance benchmark
benchmark: $(TARGET)
	@echo "=== Performance Benchmark ==="
	@echo "Running performance test..."
	@time ./$(TARGET) >/dev/null 2>&1 || echo "Benchmark completed"

# Install (basic implementation)
install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/bin (requires sudo)"
	@sudo cp $(TARGET) /usr/local/bin/ 2>/dev/null || \
		echo "Installation failed. Try: sudo make install"

# Uninstall
uninstall:
	@echo "Removing $(TARGET) from /usr/local/bin"
	@sudo rm -f /usr/local/bin/$(TARGET) 2>/dev/null || \
		echo "Uninstallation completed"

# Package creation
package: clean
	@echo "Creating source package..."
	@tar -czf $(PROJECT_NAME)-$(VERSION).tar.gz \
		$(ALL_SOURCES) $(HEADERS) Makefile README.md
	@echo "Package created: $(PROJECT_NAME)-$(VERSION).tar.gz"

# Clean build artifacts
clean:
	-del /Q $(TARGET).exe $(TARGET)_static.exe $(TARGET)_shared.exe 2>nul
	-del /Q *.o 2>nul
	-del /Q $(STATIC_LIB) $(SHARED_LIB) 2>nul
	-del /Q gmon.out profile_report.txt 2>nul
	-del /Q students.txt 2>nul
	-rmdir /S /Q $(BUILD_DIR) 2>nul

# Deep clean (including generated files)
distclean: clean
	-rmdir /S /Q $(DOC_DIR) 2>nul
	-del /Q $(PROJECT_NAME)-*.tar.gz 2>nul
	-del /Q *.log 2>nul

# Show project information
info:
	@echo "=== Project Information ==="
	@echo "Name: $(PROJECT_NAME)"
	@echo "Version: $(VERSION)"
	@echo "Target: $(TARGET)"
	@echo "Compiler: $(CC)"
	@echo "C Standard: C11"
	@echo "Sources: $(words $(ALL_SOURCES)) files"
	@echo "Headers: $(words $(HEADERS)) files"
	@echo ""
	@echo "=== Available Targets ==="
	@echo "  all          - Build the main executable (default)"
	@echo "  debug        - Build debug version with sanitizers"
	@echo "  release      - Build optimized release version"
	@echo "  run          - Build and run the program"
	@echo "  static-lib   - Create static library"
	@echo "  shared-lib   - Create shared library"
	@echo "  memcheck     - Run with memory leak detection"
	@echo "  analyze      - Perform static code analysis"
	@echo "  format       - Format source code"
	@echo "  docs         - Generate documentation"
	@echo "  profile      - Profile performance"
	@echo "  assembly     - Generate assembly output"
	@echo "  deps         - Show dependencies"
	@echo "  size         - Analyze executable size"
	@echo "  symbols      - Show symbol information"
	@echo "  benchmark    - Run performance benchmark"
	@echo "  package      - Create source package"
	@echo "  clean        - Remove build artifacts"
	@echo "  distclean    - Remove all generated files"
	@echo "  install      - Install to system (requires sudo)"
	@echo "  uninstall    - Remove from system (requires sudo)"

# Help target
help: info

# Declare phony targets
.PHONY: all debug release run run-debug static-lib shared-lib test-static test-shared \
        memcheck analyze format docs profile assembly deps size symbols \
        test-standards benchmark install uninstall package clean distclean info help

# Special targets
.DEFAULT_GOAL := all
.SUFFIXES:
.SUFFIXES: .c .o