# Lesson 5: Loops in C Programming

## Overview

Loops are fundamental control structures that allow you to execute a block of code repeatedly. C provides three types of loops: `for`, `while`, and `do-while`. This lesson demonstrates all loop types, nested loops, and loop control statements.

## Learning Objectives

- Understand the three types of loops in C
- Learn when to use each loop type
- Master nested loops and their applications
- Use loop control statements (`break` and `continue`)
- Apply loops to solve practical programming problems

## Loop Types

### 1. For Loop

The `for` loop is ideal when you know the number of iterations in advance.

**Syntax:**
```c
for (initialization; condition; increment/decrement) {
    // Code to execute
}
```

**Example:**
```c
for (int i = 1; i <= 5; i++) {
    printf("Count: %d\n", i);
}
```

**Key Points:**
- Initialization runs once at the beginning
- Condition is checked before each iteration
- Increment/decrement runs after each iteration
- All three parts are optional but semicolons are required

### 2. While Loop

The `while` loop continues as long as the condition is true. Best for unknown number of iterations.

**Syntax:**
```c
while (condition) {
    // Code to execute
    // Don't forget to update the condition variable!
}
```

**Example:**
```c
int count = 1;
while (count <= 3) {
    printf("Count: %d\n", count);
    count++;  // Important: update the condition variable
}
```

**Key Points:**
- Condition is checked before each iteration
- May not execute at all if condition is initially false
- Remember to update variables that affect the condition

### 3. Do-While Loop

The `do-while` loop executes at least once, then continues while the condition is true.

**Syntax:**
```c
do {
    // Code to execute
} while (condition);
```

**Example:**
```c
int value = 0;
do {
    printf("Value: %d\n", value);
    value++;
} while (value < 3);
```

**Key Points:**
- Code block executes first, then condition is checked
- Guarantees at least one execution
- Useful for menu systems and input validation

## Nested Loops

Loops can be placed inside other loops to create nested structures.

**Example - Multiplication Table:**
```c
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        printf("%d x %d = %d\t", i, j, i * j);
    }
    printf("\n");
}
```

**Best Practices:**
- Use meaningful variable names (avoid i, j for complex nested loops)
- Be careful with performance - nested loops can be expensive
- Consider the total number of iterations (outer × inner)

## Loop Control Statements

### Break Statement

The `break` statement immediately exits the current loop.

```c
for (int i = 1; i <= 10; i++) {
    if (i == 6) {
        break;  // Exit loop when i equals 6
    }
    printf("i = %d\n", i);
}
```

### Continue Statement

The `continue` statement skips the rest of the current iteration and moves to the next.

```c
for (int i = 1; i <= 8; i++) {
    if (i % 2 == 0) {
        continue;  // Skip even numbers
    }
    printf("Odd number: %d\n", i);
}
```

**Important Notes:**
- In nested loops, `break` and `continue` only affect the innermost loop
- Use sparingly to maintain code readability

## Common Loop Patterns

### 1. Counting Loops
```c
// Count up
for (int i = 0; i < n; i++) { /* ... */ }

// Count down
for (int i = n-1; i >= 0; i--) { /* ... */ }
```

### 2. Accumulator Pattern
```c
int sum = 0;
for (int i = 1; i <= 10; i++) {
    sum += i;  // Accumulate values
}
```

### 3. Search Pattern
```c
int found = 0;
for (int i = 0; i < size && !found; i++) {
    if (array[i] == target) {
        found = 1;
    }
}
```

## Best Practices

1. **Choose the Right Loop Type:**
   - Use `for` when you know the number of iterations
   - Use `while` for condition-based loops
   - Use `do-while` when you need at least one execution

2. **Avoid Infinite Loops:**
   - Always ensure the loop condition can become false
   - Update variables that affect the condition inside the loop

3. **Initialize Variables:**
   - Initialize loop counters and condition variables properly
   - Be careful with variable scope in for loops

4. **Performance Considerations:**
   - Minimize work inside nested loops
   - Consider loop unrolling for performance-critical code
   - Cache frequently used values outside the loop

5. **Readability:**
   - Use meaningful variable names
   - Keep loop bodies concise
   - Comment complex loop logic

## Common Pitfalls

1. **Off-by-One Errors:**
   ```c
   // Wrong: misses last element
   for (int i = 0; i < 10; i++) { /* ... */ }  // 0 to 9
   
   // Correct: includes all elements
   for (int i = 0; i <= 9; i++) { /* ... */ }  // 0 to 9
   ```

2. **Infinite Loops:**
   ```c
   // Wrong: condition never changes
   int i = 0;
   while (i < 10) {
       printf("%d\n", i);
       // Missing: i++;
   }
   ```

3. **Modifying Loop Variables:**
   ```c
   // Dangerous: modifying loop variable inside loop
   for (int i = 0; i < 10; i++) {
       if (some_condition) {
           i += 2;  // Can cause unexpected behavior
       }
   }
   ```

## Compilation and Execution

To compile and run this lesson:

```bash
make          # Compile the program
make run      # Compile and run
make clean    # Remove compiled files
make debug    # Compile with debugging symbols
```

## Next Steps

After mastering loops, you'll be ready to learn about:
- Functions and parameter passing
- Arrays and their relationship with loops
- String manipulation using loops
- More complex algorithms that rely on iteration

## Practice Exercises

Try implementing these on your own:
1. Print the first 10 Fibonacci numbers
2. Create a simple calculator menu using do-while
3. Find the largest number in a series of inputs
4. Print a pyramid pattern using nested loops
5. Implement a simple guessing game with input validation