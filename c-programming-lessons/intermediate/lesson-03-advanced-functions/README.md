# Lesson 03: Advanced Functions

## Overview

This lesson explores advanced function concepts in C, including parameter passing mechanisms, recursion, and function design patterns. Understanding these concepts is crucial for writing efficient, maintainable, and powerful C programs.

## Key Concepts

### Function Parameters

Functions can receive parameters in different ways, affecting how data is passed and modified.

### Pass by Value

When passing by value, a copy of the argument is made:

```c
void function(int x) {
    x = 100;  // Only modifies the local copy
}

int main() {
    int num = 50;
    function(num);
    // num is still 50
}
```

### Pass by Reference (using pointers)

When passing by reference, the function receives the address of the variable:

```c
void function(int *x) {
    *x = 100;  // Modifies the original variable
}

int main() {
    int num = 50;
    function(&num);
    // num is now 100
}
```

## Function Return Values

Functions can return values of any data type:

```c
int add(int a, int b) {
    return a + b;
}

double average(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}
```

## Recursion

Recursion is a programming technique where a function calls itself to solve a problem.

### Components of Recursion

1. **Base Case**: The condition that stops the recursion
2. **Recursive Case**: The function calling itself with modified parameters

```c
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}
```

### Recursion vs Iteration

Many problems can be solved both recursively and iteratively:

**Recursive Fibonacci:**
```c
int fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}
```

**Iterative Fibonacci:**
```c
int fibonacci_iterative(int n) {
    if (n <= 1) return n;
    int prev = 0, curr = 1, next;
    for (int i = 2; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```

## Functions with Arrays

Arrays are always passed by reference (as pointers) to functions:

```c
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

void modify_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Modifies original array
    }
}
```

### Array Size in Functions

Since arrays decay to pointers when passed to functions, you must pass the size separately:

```c
int find_max(int arr[], int size) {  // size parameter needed
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}
```

## Functions with Strings

Strings (character arrays) can be manipulated through functions:

```c
void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len/2; i++) {
        char temp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = temp;
    }
}
```

## Advanced Recursion Examples

### Tower of Hanoi

A classic recursive problem:

```c
void tower_of_hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    tower_of_hanoi(n-1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    tower_of_hanoi(n-1, aux, to, from);
}
```

### Binary Search

Recursive search algorithm:

```c
int binary_search(int arr[], int left, int right, int target) {
    if (left > right) return -1;  // Not found
    
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;  // Found
    
    if (target < arr[mid])
        return binary_search(arr, left, mid-1, target);
    else
        return binary_search(arr, mid+1, right, target);
}
```

## Function Design Principles

### Single Responsibility

Each function should have one clear purpose:

```c
// Good: Single responsibility
int calculate_sum(int arr[], int size);
void print_array(int arr[], int size);

// Avoid: Multiple responsibilities
void sum_and_print(int arr[], int size);  // Does too much
```

### Clear Parameter Names

Use descriptive parameter names:

```c
// Good
void swap_values(int *first, int *second);

// Less clear
void swap(int *a, int *b);
```

### Input Validation

Always validate function inputs:

```c
double calculate_average(int arr[], int size) {
    if (size <= 0 || arr == NULL) {
        return 0.0;  // Handle invalid input
    }
    // ... rest of function
}
```

## Memory Considerations

### Stack Overflow

Deep recursion can cause stack overflow:

```c
// Dangerous: No proper base case
int bad_recursion(int n) {
    return bad_recursion(n + 1);  // Infinite recursion!
}
```

### Tail Recursion

Some recursive functions can be optimized:

```c
// Tail recursive (can be optimized)
int factorial_tail(int n, int accumulator) {
    if (n <= 1) return accumulator;
    return factorial_tail(n - 1, n * accumulator);
}
```

## Best Practices

### Function Prototypes

Always declare function prototypes:

```c
// At top of file or in header
int factorial(int n);
void swap_values(int *a, int *b);

// Implementations later
int factorial(int n) {
    // implementation
}
```

### Error Handling

Handle edge cases and errors:

```c
int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;  // or some error code
    }
    return a / b;
}
```

### Documentation

Document complex functions:

```c
/**
 * Performs binary search on a sorted array
 * @param arr: sorted array to search
 * @param left: starting index
 * @param right: ending index
 * @param target: value to find
 * @return: index of target, or -1 if not found
 */
int binary_search(int arr[], int left, int right, int target);
```

## Common Pitfalls

### Modifying Read-Only Data

```c
void bad_function(char *str) {
    str[0] = 'X';  // Dangerous if str is a string literal
}

int main() {
    bad_function("Hello");  // May cause runtime error
}
```

### Infinite Recursion

```c
int bad_factorial(int n) {
    return n * bad_factorial(n - 1);  // Missing base case!
}
```

### Array Bounds

```c
void unsafe_function(int arr[], int size) {
    arr[size] = 0;  // Out of bounds access!
}
```

## Performance Considerations

### Recursion vs Iteration

- **Recursion**: More elegant, easier to understand
- **Iteration**: Usually more efficient, no stack overhead

### Function Call Overhead

Frequent function calls have overhead. For performance-critical code, consider:
- Inlining small functions
- Reducing function call depth
- Using iterative solutions for simple problems

## Code Examples Explained

The program demonstrates:

1. **Pass by Value vs Reference**: How parameter passing affects original variables
2. **Function Parameters**: Different ways to pass and receive data
3. **Recursive Functions**: Factorial and Fibonacci implementations
4. **Array Functions**: Working with arrays in functions
5. **String Functions**: Manipulating strings through functions
6. **Advanced Recursion**: Tower of Hanoi problem
7. **Recursive Algorithms**: Binary search implementation

## Compilation and Execution

Use the provided Makefile:

```bash
make          # Compile the program
make run      # Compile and execute
make clean    # Remove compiled files
make debug    # Compile with debug symbols
```

## Practice Exercises

1. Write a recursive function to calculate the power of a number
2. Implement a function that sorts an array using recursion (merge sort)
3. Create a function that checks if a string is a palindrome using recursion
4. Write a function that finds the greatest common divisor (GCD) recursively
5. Implement a recursive function to traverse a directory structure
6. Create a function that converts decimal to binary using recursion

## Next Steps

After mastering advanced functions, you'll be ready for:
- Scope and storage classes (Lesson 04)
- Function pointers
- Callback functions
- Modular programming with multiple files

Remember: Functions are the building blocks of C programs. Understanding parameter passing, recursion, and function design principles is essential for writing maintainable and efficient code!