# Lesson 04: Scope and Storage Classes

## Overview

This lesson explores variable scope, storage classes, and variable lifetime in C. Understanding these concepts is crucial for writing efficient programs and avoiding common programming errors related to variable accessibility and memory management.

## Key Concepts

### Scope

Scope determines where in the program a variable can be accessed. C has several types of scope:

1. **Global Scope**: Variables accessible throughout the entire program
2. **Function Scope**: Variables accessible only within a specific function
3. **Block Scope**: Variables accessible only within a specific block `{}`
4. **File Scope**: Variables accessible only within the current source file

### Storage Classes

Storage classes define the lifetime, visibility, and memory location of variables:

1. **auto** (default for local variables)
2. **static** 
3. **extern**
4. **register**

## Global Variables

Global variables are declared outside all functions and have external linkage by default:

```c
int global_var = 100;        // External linkage
static int file_var = 200;   // Internal linkage (file scope only)
```

### External Linkage
- Accessible from other source files
- Can be declared as `extern` in other files
- Default for global variables

### Internal Linkage
- Accessible only within the current file
- Created using `static` keyword
- Cannot be accessed from other files

## Local Variables (Automatic Storage)

Local variables are created when entering their scope and destroyed when leaving:

```c
void function() {
    int local_var = 42;  // Automatic storage class
    // local_var exists only within this function
}
```

### Block Scope

Variables can be declared within any block:

```c
{
    int block_var = 10;  // Only exists within this block
    {
        int inner_var = 20;  // Nested block scope
    }
    // inner_var no longer accessible here
}
// block_var no longer accessible here
```

## Static Storage Class

### Static Local Variables

Static local variables retain their value between function calls:

```c
void counter() {
    static int count = 0;  // Initialized only once
    count++;
    printf("Count: %d\n", count);
}
```

**Characteristics:**
- Initialized only once (first time function is called)
- Retains value between function calls
- Has local scope but static storage duration
- Stored in data segment, not on stack

### Static Global Variables

Static global variables have internal linkage:

```c
static int file_only_var = 100;  // Only accessible in this file
```

## Register Storage Class

The `register` keyword suggests storing a variable in CPU registers:

```c
register int fast_var = 100;  // Hint to use CPU register
```

**Characteristics:**
- Hint to compiler (may be ignored)
- Cannot take address of register variables
- Typically used for frequently accessed variables
- Modern compilers often ignore this hint

## Extern Storage Class

The `extern` keyword declares a variable defined elsewhere:

```c
extern int global_var;  // Declaration (not definition)
```

**Use cases:**
- Accessing global variables from other files
- Forward declarations
- Sharing variables across multiple source files

## Variable Shadowing

When a local variable has the same name as a global variable, it "shadows" the global:

```c
int x = 10;  // Global variable

void function() {
    int x = 20;  // Shadows global x
    printf("%d", x);  // Prints 20, not 10
}
```

**Important:** Once shadowed, the global variable becomes inaccessible in that scope.

## Storage Duration Types

### Automatic Storage Duration
- Local variables, function parameters
- Created when entering scope, destroyed when leaving
- Stored on the stack

### Static Storage Duration
- Global variables, static variables
- Exist for the entire program execution
- Stored in data segment

### Dynamic Storage Duration
- Variables allocated with `malloc()`, `calloc()`
- Manually managed lifetime
- Stored on the heap

### Thread Storage Duration (C11)
- One instance per thread
- Uses `_Thread_local` keyword

## Linkage Types

### External Linkage
```c
int global_var;              // External linkage
extern int another_global;   // External linkage (declaration)
```

### Internal Linkage
```c
static int file_var;         // Internal linkage
static void file_function(); // Internal linkage
```

### No Linkage
```c
void function() {
    int local_var;           // No linkage
    static int static_local; // No linkage (but static duration)
}
```

## Best Practices

### Minimize Global Variables
- Use local variables when possible
- Pass data through function parameters
- Global variables make code harder to debug and maintain

### Use Static for File-Local Functions
```c
static void helper_function() {
    // Only accessible within this file
}
```

### Initialize Variables
```c
int count = 0;           // Good: explicitly initialized
static int total = 0;    // Good: static variables are zero-initialized by default
```

### Avoid Variable Shadowing
```c
int global_var = 10;

void function() {
    int global_var = 20;  // Avoid: confusing shadowing
    // Use different names instead
}
```

## Common Pitfalls

### Uninitialized Automatic Variables
```c
void function() {
    int x;  // Contains garbage value!
    printf("%d", x);  // Undefined behavior
}
```

### Returning Pointers to Local Variables
```c
int* bad_function() {
    int local = 42;
    return &local;  // DANGEROUS: local is destroyed when function returns
}
```

### Assuming Register Variables are Faster
```c
register int i;  // Compiler may ignore this hint
// Modern compilers are better at optimization than manual register hints
```

### Forgetting Static Initialization
```c
void function() {
    static int count;  // Automatically initialized to 0
    // But be explicit when possible:
    static int explicit_count = 0;
}
```

## Memory Layout

### Stack
- Automatic variables
- Function parameters
- Return addresses
- Grows and shrinks during execution

### Data Segment
- Global variables
- Static variables
- String literals
- Exists for entire program execution

### Heap
- Dynamically allocated memory
- Managed with malloc/free
- Can grow during execution

## Scope Resolution

When accessing variables, C follows this order:
1. Local scope (innermost block)
2. Outer local scopes
3. Function parameters
4. Global scope

```c
int x = 1;  // Global

void function(int x) {  // Parameter shadows global
    {
        int x = 3;  // Local shadows parameter and global
        printf("%d", x);  // Prints 3
    }
    printf("%d", x);  // Prints parameter value
}
```

## Code Examples Explained

The program demonstrates:

1. **Global Variables**: External and internal linkage
2. **Local Scope**: Automatic variables and their lifetime
3. **Static Local**: Variables that persist between function calls
4. **Register Storage**: Compiler hints for optimization
5. **Global Access**: How functions can access global variables
6. **Variable Shadowing**: How local variables hide global ones
7. **Block Scope**: Variables within nested blocks
8. **Function Parameters**: Scope in recursive functions
9. **Storage Duration**: Different types of variable lifetime
10. **Linkage Types**: How variables are shared between files

## Compilation and Execution

Use the provided Makefile:

```bash
make          # Compile the program
make run      # Compile and execute
make clean    # Remove compiled files
make debug    # Compile with debug symbols
```

## Practice Exercises

1. Create a program with multiple source files sharing global variables
2. Write a function that uses static variables to implement a simple counter
3. Demonstrate variable shadowing with nested blocks
4. Create a program showing the difference between automatic and static local variables
5. Write functions that show proper and improper use of variable scope
6. Implement a simple state machine using static variables

## Next Steps

After mastering scope and storage classes, you'll be ready for:
- Preprocessor directives (Lesson 05)
- Multi-file projects and header files
- Advanced memory management
- Modular programming techniques

Remember: Understanding scope and storage classes is fundamental to writing maintainable C code. Proper variable management prevents bugs and makes your programs more efficient and easier to understand!