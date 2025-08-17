# Lesson 06: Basic Functions

## Overview

Functions are fundamental building blocks in C programming that allow you to organize code into reusable, modular units. This lesson demonstrates function declarations, definitions, parameter passing, return values, and different types of functions including recursive functions.

## Key Concepts

### Function Structure

A C function consists of:
- **Function Declaration (Prototype)**: Tells the compiler about the function's name, return type, and parameters
- **Function Definition**: Contains the actual implementation of the function
- **Function Call**: Invokes the function to execute its code

```c
// Declaration (prototype)
int add(int a, int b);

// Definition
int add(int a, int b) {
    return a + b;
}

// Call
int result = add(5, 3);
```

### Function Syntax

```c
return_type function_name(parameter_type parameter_name, ...) {
    // Function body
    return value; // if return_type is not void
}
```

## Code Examples Explained

### 1. Simple Function (No Parameters, No Return Value)

```c
void greet(void) {
    printf("Hello from the greet() function!\n");
}
```

- `void` return type means the function doesn't return a value
- `void` in parameters means the function takes no parameters
- Used for performing actions without returning data

### 2. Function with Parameters and Return Value

```c
int add(int a, int b) {
    return a + b;
}
```

- Takes two `int` parameters
- Returns an `int` value
- Parameters are passed by value (copies are made)

### 3. Function with Multiple Parameters

```c
float calculate_average(float num1, float num2, float num3) {
    return (num1 + num2 + num3) / 3.0;
}
```

- Demonstrates functions can take multiple parameters
- Shows floating-point arithmetic
- Returns calculated result

### 4. Function with Array Parameter

```c
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}
```

- Arrays are passed by reference (address of first element)
- Size parameter needed because arrays don't carry size information
- Function can modify the original array

### 5. Recursive Function

```c
int factorial(int n) {
    if (n <= 1) {
        return 1;  // Base case
    }
    return n * factorial(n - 1);  // Recursive call
}
```

- Function calls itself with modified parameters
- Must have a base case to prevent infinite recursion
- Useful for mathematical calculations and tree-like data structures

### 6. Function with Pointer Parameters

```c
void swap_values(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

- Uses pointers to modify original variables
- Demonstrates pass by reference
- `*` operator dereferences pointers to access values

### 7. Boolean-like Function

```c
int is_even(int number) {
    return (number % 2 == 0);
}
```

- Returns 0 for false, non-zero for true
- C doesn't have built-in boolean type (until C99's `_Bool`)
- Common pattern for condition-checking functions

## Function Scope and Storage

### Local Variables
- Variables declared inside functions are local to that function
- They exist only during function execution
- Each function call gets its own copy

### Global Variables
- Variables declared outside all functions
- Accessible from any function in the program
- Should be used sparingly

### Static Variables
- Local variables that retain their value between function calls
- Initialized only once

```c
int counter() {
    static int count = 0;  // Initialized once
    count++;
    return count;
}
```

## Best Practices

1. **Use Descriptive Names**: Function names should clearly indicate their purpose
2. **Keep Functions Small**: Each function should do one thing well
3. **Use Function Prototypes**: Declare functions before using them
4. **Validate Parameters**: Check for valid input when necessary
5. **Document Complex Functions**: Add comments explaining the logic
6. **Avoid Global Variables**: Pass data through parameters instead
7. **Return Meaningful Values**: Use return values to indicate success/failure

## Common Pitfalls

1. **Missing Prototypes**: Can lead to compilation errors or warnings
2. **Parameter Mismatch**: Calling function with wrong number or type of arguments
3. **Infinite Recursion**: Forgetting base case in recursive functions
4. **Modifying Array Size**: Arrays passed to functions lose size information
5. **Returning Local Variable Address**: Local variables are destroyed when function ends

## Compilation and Execution

```bash
# Compile the program
make

# Run the program
make run

# Clean compiled files
make clean
```

## Expected Output

```
=== C Functions Demonstration ===

1. Simple function call:
Hello from the greet() function!

2. Function with parameters and return value:
add(15, 25) = 40

3. Function with multiple parameters:
Average of 85.5, 92.0, 78.5 = 85.33

4. Function with array parameter:
Array contents: 10 20 30 40 50 

5. Recursive function:
Factorial of 5 = 120

6. Function with pointer parameters:
Before swap: x = 10, y = 20
After swap: x = 20, y = 10

7. Function returning boolean-like value:
4 is even
7 is odd
12 is even
15 is odd
```

## Next Steps

- Learn about advanced function concepts (function pointers, variadic functions)
- Explore modular programming with multiple source files
- Study memory management in functions
- Practice writing your own utility functions

## Related Concepts

- Variable scope and lifetime
- Parameter passing mechanisms
- Recursion and iteration
- Modular programming
- Code organization and reusability