# Makefile for [LESSON_NAME]
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEBUG_FLAGS = -g -DDEBUG
TARGET = main
SOURCES = main.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Compile and run
run: $(TARGET)
	./$(TARGET)

# Compile with debug symbols
debug: $(SOURCES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET) $(SOURCES)

# Clean compiled files
clean:
	rm -f $(TARGET) $(TARGET).exe *.o

# Force rebuild
rebuild: clean all

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Compile the program (default)"
	@echo "  run     - Compile and run the program"
	@echo "  debug   - Compile with debug symbols"
	@echo "  clean   - Remove compiled files"
	@echo "  rebuild - Clean and rebuild"
	@echo "  help    - Show this help message"

.PHONY: all run debug clean rebuild help