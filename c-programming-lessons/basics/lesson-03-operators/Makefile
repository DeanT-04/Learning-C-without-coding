# Makefile for Lesson 03: Operators and Expressions

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEBUG_FLAGS = -g -DDEBUG
TARGET = operators
SOURCE = main.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Compile and run
run: $(TARGET)
	./$(TARGET)

# Compile with debug information
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug $(SOURCE)

# Clean compiled files
clean:
	if exist $(TARGET).exe del $(TARGET).exe
	if exist $(TARGET)_debug.exe del $(TARGET)_debug.exe
	if exist $(TARGET) del $(TARGET)
	if exist $(TARGET)_debug del $(TARGET)_debug
	if exist *.o del *.o

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Compile the program (default)"
	@echo "  run     - Compile and run the program"
	@echo "  debug   - Compile with debug information"
	@echo "  clean   - Remove compiled files"
	@echo "  help    - Show this help message"

# Declare phony targets
.PHONY: all run debug clean help