# Lesson 02: Variables and Data Types

## Overview

This lesson covers the fundamental data types in C programming, including integer types, floating-point types, character types, and boolean types. You'll learn how to declare, initialize, and use variables effectively.

## Learning Objectives

- Understand all basic C data types and their characteristics
- Learn proper variable declaration and initialization techniques
- Understand data type sizes, ranges, and memory usage
- Practice type casting and conversion between data types
- Apply best practices for choosing appropriate data types

## Key Concepts

### 1. Integer Data Types

C provides several integer types with different sizes and ranges:

#### Character Types
- `char`: Smallest integer type, typically 1 byte
- `signed char`: Explicitly signed character (-128 to 127)
- `unsigned char`: Unsigned character (0 to 255)

#### Standard Integer Types
- `short int` (or `short`): Short integer, typically 2 bytes
- `int`: Standard integer, typically 4 bytes
- `long int` (or `long`): Long integer, typically 4 or 8 bytes
- `long long int`: Extended integer, typically 8 bytes

#### Unsigned Variants
- `unsigned short`, `unsigned int`, `unsigned long`, `unsigned long long`
- Unsigned types can only store non-negative values
- They have twice the positive range of their signed counterparts

### 2. Floating-Point Data Types

#### Precision Levels
- `float`: Single precision (typically 4 bytes, ~7 decimal digits)
- `double`: Double precision (typically 8 bytes, ~15 decimal digits)  
- `long double`: Extended precision (varies by system, ~19 decimal digits)

#### Important Notes
- Always use `f` suffix for float literals: `3.14f`
- Double is the default for decimal literals: `3.14`
- Use `L` suffix for long double literals: `3.14L`

### 3. Boolean Data Type

- `bool`: Introduced in C99 standard
- Requires `#include <stdbool.h>`
- Values: `true` and `false`
- Internally stored as integers (0 for false, non-zero for true)

### 4. Void Type

- `void`: Represents "no type" or "no value"
- Used for functions that don't return a value
- Used for generic pointers (`void*`)

## Variable Declaration and Initialization

### Declaration Syntax
```c
data_type variable_name;
```

### Initialization Methods
```c
int uninitialized;           // Contains garbage value
int zero_init = 0;          // Initialized to zero
int direct_init = 42;       // Direct initialization
int a = 1, b = 2, c = 3;    // Multiple variables
```

### Constants
```c
const int MAX_SIZE = 100;   // Cannot be modified after initialization
```

## Data Type Sizes and Ranges

The actual sizes of data types can vary between systems. Use these headers for portable code:
- `#include <limits.h>` - Integer type limits
- `#include <float.h>` - Floating-point type limits

### Common Sizes (typical 64-bit system)
- `char`: 1 byte (-128 to 127)
- `short`: 2 bytes (-32,768 to 32,767)
- `int`: 4 bytes (-2,147,483,648 to 2,147,483,647)
- `long`: 8 bytes (very large range)
- `float`: 4 bytes (~7 decimal digits precision)
- `double`: 8 bytes (~15 decimal digits precision)

## Type Casting

### Implicit Casting (Automatic)
```c
int i = 10;
float f = i;    // int automatically converted to float
```

### Explicit Casting (Manual)
```c
float f = 3.7f;
int i = (int)f;    // Explicitly cast float to int (truncates to 3)
```

## Best Practices

### Choosing Data Types
1. **Use `int` for most integer operations** - it's optimized for the target platform
2. **Use `double` for floating-point calculations** - better precision than float
3. **Use `char` only for characters** - not for small integers
4. **Use `unsigned` types when values are always non-negative**
5. **Use `const` for values that shouldn't change**

### Initialization
1. **Always initialize variables** - uninitialized variables contain garbage values
2. **Initialize at declaration when possible** - clearer and safer
3. **Use meaningful variable names** - `student_count` instead of `sc`

### Memory Considerations
1. **Choose appropriate sizes** - don't use `long long` when `int` suffices
2. **Be aware of platform differences** - sizes can vary between systems
3. **Use `sizeof()` operator** - to determine actual sizes at runtime

## Common Pitfalls

### 1. Integer Overflow
```c
int max_int = INT_MAX;
int overflow = max_int + 1;  // Undefined behavior!
```

### 2. Floating-Point Precision
```c
float f1 = 0.1f;
float f2 = 0.2f;
float sum = f1 + f2;  // May not exactly equal 0.3!
```

### 3. Uninitialized Variables
```c
int count;
printf("%d", count);  // Prints garbage value!
```

### 4. Character vs Integer Confusion
```c
char digit = 5;      // Stores ASCII character 5 (not printable)
char digit = '5';    // Stores character '5' (ASCII 53)
```

## Compilation and Execution

### Compile the program:
```bash
make
```

### Run the program:
```bash
make run
```

### Clean compiled files:
```bash
make clean
```

## Expected Output

The program will display:
- All data types with their values and sizes
- Ranges for integer types
- Precision information for floating-point types
- Examples of variable initialization
- Type casting demonstrations

## Next Steps

After mastering variables and data types, you'll be ready to learn about:
- Operators and expressions (Lesson 03)
- Input/output operations
- Mathematical calculations with different data types

## Key Takeaways

1. **C has rich type system** - choose the right type for your data
2. **Always initialize variables** - prevents unpredictable behavior
3. **Understand type sizes** - they affect memory usage and value ranges
4. **Use constants for fixed values** - improves code maintainability
5. **Be careful with type conversions** - data loss can occur