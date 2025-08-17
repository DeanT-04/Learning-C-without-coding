# Lesson 4: Control Structures (if/else, switch)

## Overview

Control structures are fundamental programming constructs that allow you to control the flow of program execution based on conditions. This lesson covers conditional statements (`if`, `else`, `else if`) and selection statements (`switch`) in C programming.

## Key Concepts

### 1. Conditional Statements

#### Basic if Statement
```c
if (condition) {
    // Code executed if condition is true
}
```
- The condition must evaluate to true (non-zero) or false (zero)
- Braces `{}` are optional for single statements but recommended for clarity
- Always use parentheses around the condition

#### if-else Statement
```c
if (condition) {
    // Code executed if condition is true
} else {
    // Code executed if condition is false
}
```
- Provides an alternative path when the condition is false
- Only one block will execute

#### if-else if-else Chain
```c
if (condition1) {
    // Code for condition1
} else if (condition2) {
    // Code for condition2
} else if (condition3) {
    // Code for condition3
} else {
    // Default code if no conditions are true
}
```
- Allows testing multiple conditions in sequence
- First true condition executes, others are skipped
- `else` clause is optional but recommended for completeness

### 2. Nested Conditions

You can place if statements inside other if statements:
```c
if (outer_condition) {
    if (inner_condition) {
        // Code executed when both conditions are true
    }
}
```
- Useful for complex decision-making logic
- Keep nesting levels reasonable for readability
- Consider using logical operators instead of deep nesting

### 3. Logical Operators in Conditions

- `&&` (AND): Both conditions must be true
- `||` (OR): At least one condition must be true  
- `!` (NOT): Inverts the condition
```c
if (age >= 18 && has_license && !is_suspended) {
    // Can drive legally
}
```

### 4. Switch Statement

The switch statement provides a clean way to handle multiple discrete values:
```c
switch (expression) {
    case value1:
        // Code for value1
        break;
    case value2:
        // Code for value2
        break;
    default:
        // Code when no cases match
        break;
}
```

#### Key Switch Rules:
- Expression must evaluate to an integer type (int, char, enum)
- Each case must be a constant value
- `break` statements prevent fall-through to next case
- `default` case handles unmatched values (optional but recommended)

#### Fall-through Behavior
```c
switch (month) {
    case 12:
    case 1:
    case 2:
        printf("Winter");
        break;
    // Multiple cases can share the same code block
}
```

### 5. Ternary Operator

A shorthand for simple if-else statements:
```c
result = (condition) ? value_if_true : value_if_false;
```
- Useful for simple assignments based on conditions
- Should not be overused for complex logic
- Improves code conciseness when used appropriately

## Best Practices

### Code Style
1. **Always use braces** for if statements, even for single lines
2. **Indent consistently** to show code structure clearly
3. **Use meaningful variable names** for conditions
4. **Keep conditions simple** and readable

### Logic Design
1. **Handle the most common case first** in if-else chains
2. **Use switch for multiple discrete values** instead of long if-else chains
3. **Always include a default case** in switch statements
4. **Avoid deep nesting** - consider early returns or logical operators

### Error Prevention
1. **Use parentheses** to clarify complex conditions
2. **Test boundary conditions** (edge cases)
3. **Consider all possible paths** through your logic
4. **Use consistent comparison operators** (avoid mixing `<` and `<=`)

## Common Pitfalls

### 1. Assignment vs. Comparison
```c
// Wrong - assignment instead of comparison
if (x = 5) { ... }

// Correct - comparison
if (x == 5) { ... }
```

### 2. Missing Break in Switch
```c
// Dangerous - will fall through to next case
switch (grade) {
    case 'A':
        printf("Excellent");
        // Missing break!
    case 'B':
        printf("Good"); // This will also execute for 'A'
        break;
}
```

### 3. Floating Point Comparisons
```c
// Problematic - floating point precision issues
if (price == 19.99) { ... }

// Better - use a small tolerance
if (fabs(price - 19.99) < 0.01) { ... }
```

### 4. Complex Conditions
```c
// Hard to read
if (age >= 18 && (income > 50000 || has_cosigner) && credit_score > 650 && !is_bankrupt) { ... }

// Better - break into logical chunks
int is_adult = (age >= 18);
int has_sufficient_income = (income > 50000 || has_cosigner);
int has_good_credit = (credit_score > 650 && !is_bankrupt);

if (is_adult && has_sufficient_income && has_good_credit) { ... }
```

## Compilation and Execution

Use the provided Makefile to compile and run:

```bash
make          # Compile the program
make run      # Compile and run
make clean    # Remove compiled files
make debug    # Compile with debug symbols
```

## Expected Output

The program demonstrates various control structures with clear examples and explanations of each concept in action.

## Next Steps

After mastering control structures, you'll learn about loops (for, while, do-while) which provide repetitive execution control. Control structures and loops together form the foundation of program flow control in C.

## Practice Exercises

Try modifying the code to:
1. Add more grade levels to the grading system
2. Create a simple calculator using switch statements
3. Implement a number guessing game with nested conditions
4. Write a program that categorizes ages into life stages