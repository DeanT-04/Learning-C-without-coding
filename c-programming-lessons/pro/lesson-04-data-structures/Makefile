# Makefile for Data Structures Lesson
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Target executable
TARGET = data_structures
SOURCES = main.c linked_list.c stack.c queue.c
HEADERS = linked_list.h stack.h queue.h
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -o $(TARGET) $(OBJECTS)

# Compile individual object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) -c $< -o $@

# Compile and run
run: $(TARGET)
	./$(TARGET)

# Debug build with sanitizers
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)_debug

$(TARGET)_debug: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET)_debug $(SOURCES)

# Run debug version
run-debug: debug
	./$(TARGET)_debug

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
		cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem $(SOURCES); \
	else \
		echo "cppcheck not found. Skipping static analysis."; \
	fi

# Format code (if clang-format is available)
format:
	@if command -v clang-format >/dev/null 2>&1; then \
		clang-format -i $(SOURCES) $(HEADERS); \
		echo "Code formatted."; \
	else \
		echo "clang-format not found. Skipping code formatting."; \
	fi

# Test individual modules
test-linked-list: linked_list.o
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -DTEST_LINKED_LIST -o test_linked_list linked_list.c
	./test_linked_list

test-stack: stack.o
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -DTEST_STACK -o test_stack stack.c
	./test_stack

test-queue: queue.o
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -DTEST_QUEUE -o test_queue queue.c
	./test_queue

# Performance test
perf-test: $(TARGET)
	@echo "Performance testing data structures..."
	@time ./$(TARGET) 2>&1 | grep -E "(real|user|sys)" || ./$(TARGET)

# Generate documentation (if doxygen is available)
docs:
	@if command -v doxygen >/dev/null 2>&1; then \
		doxygen Doxyfile 2>/dev/null || echo "Doxyfile not found, skipping documentation generation"; \
	else \
		echo "doxygen not found. Skipping documentation generation."; \
	fi

# Show dependencies
deps:
	@echo "Source files: $(SOURCES)"
	@echo "Header files: $(HEADERS)"
	@echo "Object files: $(OBJECTS)"
	@echo "Target: $(TARGET)"

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
	@echo "  test-*        - Test individual modules"
	@echo "  perf-test     - Performance test data structures"
	@echo "  docs          - Generate documentation (if doxygen available)"
	@echo "  deps          - Show file dependencies"
	@echo "  help          - Show this help message"

# Declare phony targets
.PHONY: all run debug run-debug clean memcheck analyze format test-linked-list test-stack test-queue perf-test docs deps help