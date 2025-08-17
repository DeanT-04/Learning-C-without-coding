# Lesson 05: Preprocessor Directives

## Overview

This lesson covers the C preprocessor, a powerful tool that processes your source code before compilation. The preprocessor handles directives that begin with `#` and can perform text substitution, conditional compilation, file inclusion, and macro expansion.

## Key Concepts

### What is the Preprocessor?

The preprocessor is a separate program that runs before the compiler. It:
- Processes directives that start with `#`
- Performs text substitution and macro expansion
- Handles conditional compilation
- Includes header files
- Removes comments

### Preprocessing Phases

1. **Trigraph replacement** (rarely used)
2. **Line splicing** (backslash-newline removal)
3. **Tokenization** and **comment removal**
4. **Preprocessor directive execution**
5. **Character set mapping**

## Basic Directives

### #include

Includes the contents of another file:

```c
#include <stdio.h>      // System header (angle brackets)
#include "myheader.h"   // User header (quotes)
```

**Difference:**
- `< >`: Searches system directories
- `" "`: Searches current directory first, then system directories

### #define

Creates macros (text replacements):

```c
#define PI 3.14159
#define MAX_SIZE 100
#define PROGRAM_NAME "My Program"
```

## Function-like Macros

Macros can accept parameters:

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))
#define ABS(x) ((x) < 0 ? -(x) : (x))
```

**Important:** Always use parentheses around parameters and the entire expression to avoid precedence issues.

### Multi-line Macros

Use backslash (`\`) for line continuation:

```c
#define PRINT_VARIABLE(var) \
    do { \
        printf("Variable: %s = %d\n", #var, var); \
    } while(0)
```

## Macro Operators

### Stringification Operator (#)

Converts macro parameter to string literal:

```c
#define STRINGIFY(x) #x
#define PRINT_VAR(var) printf(#var " = %d\n", var)

int count = 42;
PRINT_VAR(count);  // Prints: count = 42
```

### Token Pasting Operator (##)

Concatenates tokens:

```c
#define DECLARE_VAR(type, name) type var_##name
#define GET_VAR(name) var_##name

DECLARE_VAR(int, counter);  // Creates: int var_counter;
GET_VAR(counter) = 10;      // Accesses: var_counter = 10;
```

### Variable Arguments (__VA_ARGS__)

Macros can accept variable number of arguments:

```c
#define DEBUG_PRINTF(format, ...) \
    printf("[DEBUG] " format "\n", ##__VA_ARGS__)

DEBUG_PRINTF("Value: %d", 42);
DEBUG_PRINTF("Multiple: %d, %s", 100, "test");
```

## Conditional Compilation

### #if, #elif, #else, #endif

```c
#define VERSION 2

#if VERSION == 1
    printf("Version 1 code\n");
#elif VERSION == 2
    printf("Version 2 code\n");
#else
    printf("Unknown version\n");
#endif
```

### #ifdef, #ifndef

```c
#ifdef DEBUG
    printf("Debug mode enabled\n");
#endif

#ifndef RELEASE
    printf("Not in release mode\n");
#endif
```

### #undef

Removes a macro definition:

```c
#define TEMP 100
#undef TEMP
// TEMP is no longer defined
```

## Header Guards

Prevent multiple inclusions of the same header:

```c
#ifndef MYHEADER_H
#define MYHEADER_H

// Header content here

#endif // MYHEADER_H
```

**Alternative (C23):**
```c
#pragma once  // Compiler-specific, but widely supported
```

## Predefined Macros

The compiler provides several predefined macros:

```c
__FILE__        // Current source file name
__LINE__        // Current line number
__DATE__        // Compilation date
__TIME__        // Compilation time
__FUNCTION__    // Current function name (C99)
__STDC__        // 1 if standard C compliant
__STDC_VERSION__ // C standard version
```

### Platform Detection

```c
#ifdef _WIN32
    // Windows code
#elif defined(__linux__)
    // Linux code
#elif defined(__APPLE__)
    // macOS code
#endif
```

## Best Practices

### Macro Naming

Use UPPERCASE for macros to distinguish from variables:

```c
#define MAX_BUFFER_SIZE 1024  // Good
#define max_buffer_size 1024  // Confusing
```

### Parentheses in Macros

Always use parentheses to avoid precedence issues:

```c
#define SQUARE(x) ((x) * (x))     // Good
#define SQUARE(x) x * x           // Dangerous

// Problem with second version:
SQUARE(2 + 3)  // Expands to: 2 + 3 * 2 + 3 = 11 (not 25!)
```

### Multi-statement Macros

Use do-while(0) idiom for multi-statement macros:

```c
#define SWAP(a, b) \
    do { \
        int temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while(0)
```

### Avoid Side Effects

Be careful with macros that evaluate parameters multiple times:

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int x = 5;
int result = MAX(++x, 10);  // x is incremented twice!
```

## Common Pitfalls

### Macro Side Effects

```c
#define SQUARE(x) ((x) * (x))
int i = 5;
int result = SQUARE(++i);  // i is incremented twice!
```

### Missing Parentheses

```c
#define MULTIPLY(a, b) a * b
int result = MULTIPLY(2 + 3, 4);  // Expands to: 2 + 3 * 4 = 14 (not 20)
```

### Semicolon Issues

```c
#define PRINT_MSG(msg) printf("%s\n", msg);

if (condition)
    PRINT_MSG("Hello");  // Semicolon creates empty statement
else
    PRINT_MSG("World");  // This else has no matching if!
```

### Macro Redefinition

```c
#define SIZE 100
#define SIZE 200  // Warning: macro redefinition
```

## Advanced Techniques

### Conditional Debug Macros

```c
#ifdef DEBUG
    #define DBG_PRINT(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
    #define DBG_PRINT(fmt, ...) // Empty when not debugging
#endif
```

### Feature Flags

```c
#define FEATURE_LOGGING 1
#define FEATURE_ENCRYPTION 0

#if FEATURE_LOGGING
    void log_message(const char* msg);
#endif

#if FEATURE_ENCRYPTION
    void encrypt_data(char* data);
#endif
```

### Version Control

```c
#define VERSION_MAJOR 2
#define VERSION_MINOR 1
#define VERSION_PATCH 0

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define VERSION_STRING TOSTRING(VERSION_MAJOR) "." \
                      TOSTRING(VERSION_MINOR) "." \
                      TOSTRING(VERSION_PATCH)
```

## Debugging Preprocessor

### View Preprocessor Output

```bash
gcc -E main.c -o main.i  # Output preprocessed code to main.i
```

### Preprocessor-only Compilation

```bash
gcc -E main.c  # Print preprocessed code to stdout
```

## Code Examples Explained

The program demonstrates:

1. **Basic Macros**: Simple text replacement
2. **Function-like Macros**: Parameterized macros
3. **Mathematical Macros**: Useful mathematical operations
4. **Bit Manipulation**: Macros for bit operations
5. **Stringification**: Converting parameters to strings
6. **Token Pasting**: Concatenating tokens
7. **Conditional Compilation**: Platform and feature-specific code
8. **Predefined Macros**: Compiler-provided information
9. **Variable Arguments**: Macros with flexible parameters
10. **Header Guards**: Preventing multiple inclusions

## Compilation and Execution

Use the provided Makefile:

```bash
make          # Compile the program
make run      # Compile and execute
make clean    # Remove compiled files
make debug    # Compile with debug symbols
make preprocess # View preprocessor output
```

## Practice Exercises

1. Create a header file with mathematical constants and functions
2. Write macros for common array operations (find max, min, sum)
3. Implement a simple logging system using conditional compilation
4. Create platform-specific code using preprocessor directives
5. Write a macro that generates getter/setter functions
6. Implement a simple assertion macro for debugging

## Next Steps

After mastering preprocessor directives, you'll be ready for:
- Basic file I/O (Lesson 06)
- Multi-file projects and modular programming
- Advanced macro techniques
- Build systems and configuration management

Remember: The preprocessor is a powerful tool, but use it wisely. Overuse of complex macros can make code hard to read and debug. Always prioritize code clarity and maintainability!