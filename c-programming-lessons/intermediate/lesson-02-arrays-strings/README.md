# Lesson 02: Arrays and Strings

## Overview

This lesson covers arrays and strings in C, two fundamental data structures that work closely together. Arrays provide a way to store multiple values of the same type, while strings are specialized character arrays that represent text data.

## Key Concepts

### Arrays

An array is a collection of elements of the same data type stored in contiguous memory locations. Each element can be accessed using an index.

```c
int numbers[5] = {10, 20, 30, 40, 50};
```

### Array Declaration Syntax

```c
data_type array_name[size];
data_type array_name[size] = {value1, value2, ...};
data_type array_name[] = {value1, value2, ...};  // Size inferred
```

### Array Indexing

Arrays use zero-based indexing:
- First element: `array[0]`
- Last element: `array[size-1]`

```c
int arr[5] = {1, 2, 3, 4, 5};
printf("%d", arr[0]);  // Prints 1
printf("%d", arr[4]);  // Prints 5
```

## Multi-dimensional Arrays

Arrays can have multiple dimensions:

```c
int matrix[3][4];  // 3 rows, 4 columns
int cube[2][3][4]; // 3D array
```

### Initialization

```c
int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

## Arrays and Pointers

In C, array names are pointers to the first element:

```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;  // Equivalent to &arr[0]

// These are equivalent:
arr[i]
*(arr + i)
ptr[i]
*(ptr + i)
```

## Strings in C

Strings in C are arrays of characters terminated by a null character (`'\0'`).

### String Declaration

```c
char str1[20] = "Hello";        // Character array
char str2[] = "World";          // Size inferred
char *str3 = "C Programming";   // String literal (read-only)
```

### String vs Character Array

```c
char str1[] = {'H', 'e', 'l', 'l', 'o', '\0'};  // Manual null termination
char str2[] = "Hello";                           // Automatic null termination
```

## String Functions

C provides several standard library functions for string manipulation:

### String Length
```c
#include <string.h>
size_t len = strlen("Hello");  // Returns 5
```

### String Copy
```c
char dest[20];
strcpy(dest, "Hello");  // Copies "Hello" to dest
```

### String Concatenation
```c
char str[20] = "Hello ";
strcat(str, "World");  // str becomes "Hello World"
```

### String Comparison
```c
int result = strcmp("Apple", "Banana");
// Returns: negative if first < second
//          0 if equal
//          positive if first > second
```

### String Search
```c
char *pos = strchr("Hello", 'l');    // Find character
char *pos = strstr("Hello", "ll");   // Find substring
```

## Memory Considerations

### Array Size

```c
int arr[5];
size_t size = sizeof(arr) / sizeof(arr[0]);  // Gets number of elements
```

### String Buffer Safety

Always ensure sufficient buffer size:

```c
char buffer[100];
strncpy(buffer, source, sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination
```

## Common Operations

### Array Traversal

```c
int arr[5] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++) {
    printf("%d ", arr[i]);
}
```

### String Processing

```c
char str[] = "Hello";
for (int i = 0; str[i] != '\0'; i++) {
    printf("%c ", str[i]);
}
```

### Character Manipulation

```c
// Convert to uppercase
for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
        str[i] = str[i] - 'a' + 'A';
    }
}
```

## Input and Output

### Array Input
```c
int arr[5];
for (int i = 0; i < 5; i++) {
    scanf("%d", &arr[i]);
}
```

### String Input
```c
char str[100];
scanf("%99s", str);           // Single word (no spaces)
fgets(str, sizeof(str), stdin); // Entire line (with spaces)
```

## Best Practices

### Array Safety
1. Always check array bounds
2. Initialize arrays when declaring
3. Use `sizeof()` to get array size
4. Be careful with pointer arithmetic

### String Safety
1. Always null-terminate strings
2. Check buffer sizes to prevent overflow
3. Use safe functions like `strncpy()` and `snprintf()`
4. Validate input lengths

### Memory Management
1. Understand stack vs heap allocation
2. Be aware of array lifetime and scope
3. Don't return pointers to local arrays
4. Use dynamic allocation for large arrays

## Common Pitfalls

### Buffer Overflow
```c
char buffer[10];
strcpy(buffer, "This string is too long");  // DANGEROUS!
```

### Uninitialized Arrays
```c
int arr[5];  // Contains garbage values
// Always initialize: int arr[5] = {0};
```

### Array Decay
```c
void function(int arr[]) {
    // arr is actually a pointer here, not an array
    // sizeof(arr) won't give the array size
}
```

### String Termination
```c
char str[5] = {'H', 'e', 'l', 'l', 'o'};  // Missing '\0'!
printf("%s", str);  // Undefined behavior
```

## Code Examples Explained

The program demonstrates:

1. **Array Declaration**: Various ways to declare and initialize arrays
2. **Array Manipulation**: Accessing and modifying array elements
3. **Multi-dimensional Arrays**: Working with 2D arrays (matrices)
4. **Array-Pointer Relationship**: How arrays and pointers interact
5. **String Basics**: Character arrays as strings
6. **String Functions**: Using standard library string functions
7. **Character Manipulation**: Processing individual characters
8. **String I/O**: Reading strings from user input
9. **String Arrays**: Arrays of string pointers
10. **Advanced Operations**: Searching, trimming, and processing strings

## Compilation and Execution

Use the provided Makefile:

```bash
make          # Compile the program
make run      # Compile and execute
make clean    # Remove compiled files
make debug    # Compile with debug symbols
```

## Practice Exercises

1. Write a function to reverse an array in place
2. Implement a function to find the maximum value in an array
3. Create a program that counts word frequency in a string
4. Write a function to check if a string is a palindrome
5. Implement a simple string replacement function
6. Create a program that sorts an array of strings alphabetically

## Next Steps

After mastering arrays and strings, you'll be ready for:
- Advanced function parameters (Lesson 03)
- Dynamic memory allocation
- Data structures implementation
- File handling with arrays and strings

Remember: Arrays and strings are fundamental to C programming. Understanding their relationship with pointers and memory management is crucial for writing efficient and safe C code!