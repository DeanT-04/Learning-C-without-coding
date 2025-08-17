# Lesson 06: Basic File I/O

## Overview

This lesson covers file input/output operations in C, including reading from and writing to text and binary files. File I/O is essential for data persistence, configuration management, and data processing applications.

## Key Concepts

### File Streams

In C, files are accessed through file streams represented by `FILE*` pointers. The standard library provides three predefined streams:

- `stdin` - Standard input (keyboard)
- `stdout` - Standard output (screen)
- `stderr` - Standard error output (screen)

### File Operations

Basic file operations include:
1. **Opening** a file (`fopen`)
2. **Reading** from a file
3. **Writing** to a file
4. **Positioning** within a file
5. **Closing** a file (`fclose`)

## Opening Files

### fopen() Function

```c
FILE *fopen(const char *filename, const char *mode);
```

**Common file modes:**
- `"r"` - Read only (file must exist)
- `"w"` - Write only (creates new file or truncates existing)
- `"a"` - Append (creates new file or appends to existing)
- `"r+"` - Read and write (file must exist)
- `"w+"` - Read and write (creates new or truncates existing)
- `"a+"` - Read and append

**Binary modes:** Add `"b"` to any mode (e.g., `"rb"`, `"wb"`, `"ab"`)

### Example

```c
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    printf("Error opening file\n");
    return -1;
}
// Use file...
fclose(file);
```

## Reading from Files

### Character-by-Character Reading

```c
int fgetc(FILE *stream);

int ch;
while ((ch = fgetc(file)) != EOF) {
    printf("%c", ch);
}
```

### Line-by-Line Reading

```c
char *fgets(char *str, int size, FILE *stream);

char line[256];
while (fgets(line, sizeof(line), file) != NULL) {
    printf("%s", line);
}
```

### Formatted Reading

```c
int fscanf(FILE *stream, const char *format, ...);

int number;
float decimal;
char string[100];
fscanf(file, "%d %f %s", &number, &decimal, string);
```

## Writing to Files

### Character-by-Character Writing

```c
int fputc(int character, FILE *stream);

fputc('A', file);
fputc('\n', file);
```

### String Writing

```c
int fputs(const char *str, FILE *stream);

fputs("Hello, World!\n", file);
```

### Formatted Writing

```c
int fprintf(FILE *stream, const char *format, ...);

fprintf(file, "Number: %d, Float: %.2f\n", 42, 3.14);
```

## Binary File Operations

### Writing Binary Data

```c
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);

struct Data {
    int id;
    float value;
};

struct Data data = {1, 3.14};
fwrite(&data, sizeof(struct Data), 1, file);
```

### Reading Binary Data

```c
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);

struct Data data;
if (fread(&data, sizeof(struct Data), 1, file) == 1) {
    printf("ID: %d, Value: %.2f\n", data.id, data.value);
}
```

## File Positioning

### Getting Current Position

```c
long ftell(FILE *stream);

long position = ftell(file);
printf("Current position: %ld\n", position);
```

### Setting Position

```c
int fseek(FILE *stream, long offset, int whence);

// whence values:
// SEEK_SET - Beginning of file
// SEEK_CUR - Current position
// SEEK_END - End of file

fseek(file, 0, SEEK_SET);    // Go to beginning
fseek(file, 0, SEEK_END);    // Go to end
fseek(file, 10, SEEK_CUR);   // Move 10 bytes forward
```

### Rewinding

```c
void rewind(FILE *stream);

rewind(file);  // Equivalent to fseek(file, 0, SEEK_SET)
```

## Error Handling

### Checking for Errors

```c
int ferror(FILE *stream);
int feof(FILE *stream);

if (ferror(file)) {
    printf("File error occurred\n");
}

if (feof(file)) {
    printf("End of file reached\n");
}
```

### Using perror()

```c
FILE *file = fopen("nonexistent.txt", "r");
if (file == NULL) {
    perror("Error opening file");  // Prints system error message
}
```

### Proper Error Handling Pattern

```c
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    fprintf(stderr, "Error: Cannot open data.txt\n");
    return -1;
}

// Perform file operations...

if (ferror(file)) {
    fprintf(stderr, "Error: File operation failed\n");
    fclose(file);
    return -1;
}

if (fclose(file) != 0) {
    fprintf(stderr, "Error: Cannot close file\n");
    return -1;
}
```

## File Management

### Closing Files

```c
int fclose(FILE *stream);

if (fclose(file) != 0) {
    printf("Error closing file\n");
}
```

**Important:** Always close files when done to:
- Free system resources
- Ensure data is written to disk
- Prevent file corruption

### Removing Files

```c
int remove(const char *filename);

if (remove("temp.txt") == 0) {
    printf("File deleted successfully\n");
} else {
    printf("Error deleting file\n");
}
```

### Renaming Files

```c
int rename(const char *old_name, const char *new_name);

if (rename("old.txt", "new.txt") == 0) {
    printf("File renamed successfully\n");
} else {
    printf("Error renaming file\n");
}
```

## Best Practices

### Always Check Return Values

```c
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    // Handle error
    return -1;
}

if (fclose(file) != 0) {
    // Handle close error
}
```

### Use Appropriate Buffer Sizes

```c
char buffer[1024];  // Reasonable buffer size
while (fgets(buffer, sizeof(buffer), file) != NULL) {
    // Process line
}
```

### Handle Binary vs Text Mode

```c
// Text mode (default)
FILE *text_file = fopen("data.txt", "r");

// Binary mode (important for binary data)
FILE *binary_file = fopen("data.bin", "rb");
```

### Resource Management

```c
FILE *file = fopen("data.txt", "r");
if (file == NULL) return -1;

// Always close in all code paths
if (some_condition) {
    fclose(file);
    return -1;
}

// Normal processing...
fclose(file);
return 0;
```

## Common Pitfalls

### Not Checking fopen() Return Value

```c
FILE *file = fopen("data.txt", "r");
// DANGEROUS: What if file is NULL?
fgets(buffer, sizeof(buffer), file);  // Crash!
```

### Forgetting to Close Files

```c
void bad_function() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) return;
    
    // Process file...
    
    // FORGOT TO CLOSE FILE!
    // This leaks file handles
}
```

### Buffer Overflows

```c
char small_buffer[10];
// DANGEROUS: Line might be longer than buffer
fgets(small_buffer, 1000, file);  // Buffer overflow!

// CORRECT:
fgets(small_buffer, sizeof(small_buffer), file);
```

### Mixing Text and Binary Operations

```c
FILE *file = fopen("data.txt", "r");  // Text mode
fread(buffer, 1, 100, file);  // May not work as expected on Windows
```

### Not Handling EOF Correctly

```c
int ch;
while ((ch = fgetc(file)) != EOF) {  // Correct
    // Process character
}

// WRONG:
char ch;
while ((ch = fgetc(file)) != EOF) {  // ch should be int, not char
    // May not detect EOF correctly
}
```

## Performance Considerations

### Buffering

The standard library automatically buffers I/O operations. You can control buffering:

```c
// Set buffer size
setvbuf(file, NULL, _IOFBF, 8192);  // 8KB buffer

// Disable buffering
setvbuf(file, NULL, _IONBF, 0);

// Line buffering
setvbuf(file, NULL, _IOLBF, 0);
```

### Batch Operations

```c
// Efficient: Read/write in larger chunks
char buffer[4096];
while (fread(buffer, 1, sizeof(buffer), file) > 0) {
    // Process buffer
}

// Less efficient: Character by character
int ch;
while ((ch = fgetc(file)) != EOF) {
    // Process character
}
```

## Code Examples Explained

The program demonstrates:

1. **Basic File Operations**: Opening, checking, and closing files
2. **Text File Reading**: Character, line, and formatted reading
3. **Text File Writing**: Various writing methods
4. **File Append**: Adding data to existing files
5. **Binary Operations**: Reading and writing structured data
6. **File Positioning**: Seeking and positioning within files
7. **Error Handling**: Proper error checking and reporting

## Compilation and Execution

Use the provided Makefile:

```bash
make          # Compile the program
make run      # Compile and execute
make clean    # Remove compiled files
make debug    # Compile with debug symbols
```

## Practice Exercises

1. Write a program that counts words, lines, and characters in a text file
2. Create a simple database using binary files to store student records
3. Implement a file copy program that copies one file to another
4. Write a program that merges two sorted files into one sorted file
5. Create a log file system that appends timestamped messages
6. Implement a simple text editor that can read, modify, and save files

## Next Steps

After mastering basic file I/O, you'll be ready for:
- Advanced file handling (Pro level lessons)
- Directory operations
- File permissions and attributes
- Memory-mapped files
- Network I/O

Remember: File I/O is fundamental to most real-world applications. Always handle errors properly, manage resources carefully, and choose appropriate file modes for your use case!