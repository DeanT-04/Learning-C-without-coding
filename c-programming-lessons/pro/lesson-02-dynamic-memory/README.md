# Lesson 02: Dynamic Memory Allocation

## Overview

This lesson covers dynamic memory allocation in C, which allows programs to request memory at runtime. Unlike static allocation where memory size is determined at compile time, dynamic allocation provides flexibility to allocate exactly the amount of memory needed during program execution.

## Key Concepts

### Dynamic Memory Allocation
- **Purpose**: Allocate memory during program execution
- **Flexibility**: Size determined at runtime, not compile time
- **Location**: Memory allocated on the heap, not the stack
- **Responsibility**: Programmer must manually free allocated memory

### Memory Management Functions
- **malloc()**: Allocates uninitialized memory
- **calloc()**: Allocates zero-initialized memory
- **realloc()**: Resizes previously allocated memory
- **free()**: Releases allocated memory back to the system

## Code Examples Explained

### 1. malloc() - Memory Allocation

```c
int *ptr = malloc(5 * sizeof(int));
```

- Allocates memory for 5 integers
- Returns pointer to allocated memory or NULL if failed
- Memory contains garbage values (uninitialized)
- Must check for NULL before using

**Key Points:**
- Always multiply by `sizeof(type)` for correct byte count
- Memory is not initialized - contains random values
- Returns `void*` that can be assigned to any pointer type

### 2. calloc() - Cleared Memory Allocation

```c
int *ptr = calloc(5, sizeof(int));
```

- Allocates memory for 5 integers initialized to zero
- Takes two parameters: count and size of each element
- Equivalent to `malloc(count * size)` followed by `memset(ptr, 0, count * size)`
- Safer than malloc when you need zero-initialized memory

**Advantages:**
- Automatic zero initialization
- Overflow protection in size calculation
- Cleaner code for arrays

### 3. realloc() - Memory Reallocation

```c
ptr = realloc(ptr, new_size);
```

- Resizes previously allocated memory block
- Can expand or shrink the memory block
- May move the memory block to a new location
- Preserves existing data up to the minimum of old and new sizes

**Important Notes:**
- Original pointer may become invalid
- Always assign result back to pointer
- `realloc(ptr, 0)` is equivalent to `free(ptr)`
- `realloc(NULL, size)` is equivalent to `malloc(size)`

### 4. Dynamic Arrays

```c
double *array = malloc(size * sizeof(double));
```

- Create arrays with runtime-determined size
- Access elements using array notation: `array[i]`
- Useful for user input-driven array sizes
- More memory-efficient than large static arrays

### 5. Dynamic Structures

```c
struct Student *student = malloc(sizeof(struct Student));
student->name = malloc(50 * sizeof(char));
```

- Allocate memory for structures at runtime
- Can create arrays of structures dynamically
- Nested allocation for structure members (like strings)
- Enables flexible data structure sizes

### 6. Dynamic 2D Arrays

**Method 1: Array of Pointers**
```c
int **matrix = malloc(rows * sizeof(int*));
for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(cols * sizeof(int));
}
```

**Method 2: Single Allocation**
```c
int *matrix = malloc(rows * cols * sizeof(int));
// Access: matrix[i * cols + j]
```

- Method 1: More flexible, non-contiguous memory
- Method 2: Better cache performance, contiguous memory

## Memory Management Best Practices

### 1. Always Check Return Values
```c
ptr = malloc(size);
if (ptr == NULL) {
    // Handle allocation failure
    return -1;
}
```

### 2. Free Every Allocation
```c
free(ptr);
ptr = NULL;  // Prevent dangling pointer
```

### 3. Avoid Memory Leaks
- Match every `malloc/calloc/realloc` with exactly one `free`
- Free memory in reverse order of allocation for nested structures
- Set pointers to NULL after freeing

### 4. Prevent Double Free
```c
if (ptr != NULL) {
    free(ptr);
    ptr = NULL;
}
```

### 5. Handle Error Conditions
```c
char *buf1 = malloc(size1);
char *buf2 = malloc(size2);
if (buf1 == NULL || buf2 == NULL) {
    free(buf1);  // Safe even if NULL
    free(buf2);  // Safe even if NULL
    return ERROR;
}
```

## Common Pitfalls

1. **Memory Leaks**: Forgetting to call `free()` for allocated memory
2. **Dangling Pointers**: Using pointers after freeing the memory
3. **Double Free**: Calling `free()` twice on the same pointer
4. **Buffer Overruns**: Writing beyond allocated memory boundaries
5. **Null Pointer Dereference**: Using pointer without checking for NULL
6. **Use After Free**: Accessing memory after it has been freed

## Memory Debugging Tools

### Valgrind (Linux/Mac)
```bash
valgrind --leak-check=full ./program
```

### Static Analysis
```bash
cppcheck --enable=all source.c
```

### Compiler Warnings
```bash
gcc -Wall -Wextra -fsanitize=address program.c
```

## Compilation and Execution

```bash
make          # Compile the program
make run      # Compile and run
make clean    # Remove compiled files
make debug    # Compile with debugging symbols
make memcheck # Run with valgrind (if available)
```

## Expected Output

The program demonstrates:
- Basic malloc, calloc, and realloc operations
- Dynamic array creation and manipulation
- Dynamic structure allocation
- 2D array allocation methods
- Memory leak prevention techniques
- Safe memory management practices

## Performance Considerations

### Memory Allocation Overhead
- Each allocation has metadata overhead
- Frequent small allocations can be inefficient
- Consider memory pools for many small objects

### Cache Performance
- Contiguous memory allocation improves cache locality
- Single allocation method for 2D arrays is faster
- Structure of arrays vs array of structures trade-offs

### Fragmentation
- Frequent allocation/deallocation can fragment heap
- Use appropriate allocation strategies
- Consider memory alignment requirements

## Next Steps

After mastering dynamic memory allocation, you'll be ready to:
- Learn advanced file handling (Lesson 03)
- Implement complex data structures (Lesson 04)
- Work with function pointers and callbacks
- Build multi-file projects with modular design

## Key Takeaways

- Dynamic allocation provides runtime flexibility at the cost of manual management
- Always check return values and handle allocation failures
- Match every allocation with exactly one deallocation
- Use tools to detect memory leaks and errors
- Consider performance implications of allocation patterns
- Set pointers to NULL after freeing to prevent dangling pointer bugs