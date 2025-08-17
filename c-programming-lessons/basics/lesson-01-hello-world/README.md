# Lesson 01: Hello World

## Overview

This lesson introduces the fundamental structure of a C program through the classic "Hello, World!" example. You'll learn about the basic components that make up every C program and understand the compilation and execution process.

## Learning Objectives

- Understand the basic structure of a C program
- Learn about the `#include` directive and standard library
- Understand the `main()` function and its role
- Learn how to compile and run C programs
- Understand the compilation process on Windows

## Code Explanation

### Program Structure

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

Let's break down each part:

#### 1. Header Include
```c
#include <stdio.h>
```
- The `#include` directive tells the preprocessor to include the contents of another file
- `stdio.h` is the standard input/output header file
- It contains declarations for functions like `printf()` that we use for output
- The angle brackets `< >` indicate this is a system header file

#### 2. Main Function
```c
int main() {
```
- Every C program must have exactly one `main()` function
- This is where program execution begins
- `int` indicates the function returns an integer value
- The parentheses `()` show this function takes no parameters

#### 3. Program Logic
```c
printf("Hello, World!\n");
```
- `printf()` is a function that prints formatted text to the console
- The text inside quotes is called a string literal
- `\n` is an escape sequence that represents a newline character
- The semicolon `;` marks the end of the statement

#### 4. Return Statement
```c
return 0;
```
- Returns an integer value to the operating system
- `0` typically indicates successful program execution
- Non-zero values usually indicate errors
- This is how the OS knows if your program ran successfully

## Compilation Process

### What Happens When You Compile

1. **Preprocessing**: The preprocessor handles directives like `#include`
2. **Compilation**: The compiler translates C code into assembly language
3. **Assembly**: The assembler converts assembly into machine code (object files)
4. **Linking**: The linker combines object files and libraries into an executable

### Using the Makefile

This lesson includes a Makefile that automates the compilation process:

```bash
# Compile the program
make

# Compile and run
make run

# Compile with debugging symbols
make debug

# Clean up compiled files
make clean

# Show available commands
make help
```

### Manual Compilation

You can also compile manually using:

```bash
gcc -Wall -Wextra -std=c11 -o hello_world main.c
```

**Compiler flags explained:**
- `-Wall`: Enable all common warnings
- `-Wextra`: Enable extra warnings
- `-std=c11`: Use the C11 standard
- `-o hello_world`: Specify output filename

## Running the Program

After compilation, run the program:

```bash
# On Windows
hello_world.exe

# On Unix-like systems
./hello_world
```

**Expected Output:**
```
Hello, World!
```

## Key Concepts

### C Program Structure
Every C program follows this basic structure:
1. Header includes (preprocessor directives)
2. Function declarations (if needed)
3. Main function definition
4. Other function definitions (if any)

### Best Practices Demonstrated
- **Clear formatting**: Proper indentation and spacing
- **Standard compliance**: Using C11 standard
- **Error checking**: Compiler warnings enabled
- **Documentation**: Comments explaining complex parts

### Common Mistakes to Avoid
- Forgetting to include necessary headers
- Missing semicolons after statements
- Forgetting the return statement in main
- Not handling compilation warnings

## Next Steps

Now that you understand the basic structure of a C program, you're ready to move on to:
- Variables and data types
- User input and output
- Basic arithmetic operations

## Troubleshooting

### Common Compilation Errors

**Error: 'printf' undeclared**
- Solution: Make sure you have `#include <stdio.h>` at the top

**Error: expected ';' before '}'**
- Solution: Check that all statements end with semicolons

**Error: undefined reference to 'main'**
- Solution: Ensure you have a `main()` function defined

### Platform-Specific Notes

**Windows:**
- Use MinGW, MSVC, or Clang compiler
- Executable will have `.exe` extension
- Use Command Prompt or PowerShell to run

**Compiler Installation:**
- Install MinGW-w64 or Visual Studio Build Tools
- Ensure compiler is in your PATH environment variable