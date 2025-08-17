# Lesson 03: Operators and Expressions

## Overview

This lesson covers all types of operators in C programming and demonstrates how they work together in expressions. Understanding operators and their precedence is crucial for writing correct and efficient C code.

## What You'll Learn

- Arithmetic operators for mathematical calculations
- Relational operators for comparisons
- Logical operators for boolean operations
- Bitwise operators for bit-level manipulation
- Assignment operators and their shortcuts
- Increment/decrement operators
- Operator precedence and associativity rules
- The conditional (ternary) operator
- The sizeof operator

## Operator Categories

### 1. Arithmetic Operators

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| + | Addition | 5 + 3 | 8 |
| - | Subtraction | 5 - 3 | 2 |
| * | Multiplication | 5 * 3 | 15 |
| / | Division | 5 / 3 | 1 (integer division) |
| % | Modulus | 5 % 3 | 2 (remainder) |

**Key Points:**
- Integer division truncates the decimal part
- Modulus operator only works with integers
- Use float/double for precise division

### 2. Relational Operators

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| > | Greater than | 5 > 3 | 1 (true) |
| < | Less than | 5 < 3 | 0 (false) |
| >= | Greater than or equal | 5 >= 5 | 1 (true) |
| <= | Less than or equal | 5 <= 3 | 0 (false) |
| == | Equal to | 5 == 5 | 1 (true) |
| != | Not equal to | 5 != 3 | 1 (true) |

**Key Points:**
- Return 1 for true, 0 for false
- Don't confuse == (comparison) with = (assignment)
- Can be used with any data types

### 3. Logical Operators

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| && | Logical AND | 1 && 1 | 1 (true) |
| \|\| | Logical OR | 1 \|\| 0 | 1 (true) |
| ! | Logical NOT | !1 | 0 (false) |

**Key Points:**
- Short-circuit evaluation: && stops at first false, \|\| stops at first true
- Any non-zero value is considered true
- Zero is considered false

### 4. Bitwise Operators

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| & | Bitwise AND | 12 & 10 | 8 |
| \| | Bitwise OR | 12 \| 10 | 14 |
| ^ | Bitwise XOR | 12 ^ 10 | 6 |
| ~ | Bitwise NOT | ~12 | -13 |
| << | Left shift | 12 << 1 | 24 |
| >> | Right shift | 12 >> 1 | 6 |

**Key Points:**
- Work on individual bits
- Useful for low-level programming and optimization
- Shift operators multiply/divide by powers of 2

### 5. Assignment Operators

| Operator | Name | Example | Equivalent |
|----------|------|---------|------------|
| = | Assignment | a = 5 | a = 5 |
| += | Add and assign | a += 3 | a = a + 3 |
| -= | Subtract and assign | a -= 3 | a = a - 3 |
| *= | Multiply and assign | a *= 3 | a = a * 3 |
| /= | Divide and assign | a /= 3 | a = a / 3 |
| %= | Modulus and assign | a %= 3 | a = a % 3 |

### 6. Increment/Decrement Operators

| Operator | Name | Example | Description |
|----------|------|---------|-------------|
| ++var | Pre-increment | ++i | Increment first, then use |
| var++ | Post-increment | i++ | Use first, then increment |
| --var | Pre-decrement | --i | Decrement first, then use |
| var-- | Post-decrement | i-- | Use first, then decrement |

## Operator Precedence Table

Higher precedence operators are evaluated first:

| Precedence | Operators | Associativity |
|------------|-----------|---------------|
| 1 (Highest) | () [] -> . | Left to right |
| 2 | ! ~ ++ -- + - * & (type) sizeof | Right to left |
| 3 | * / % | Left to right |
| 4 | + - | Left to right |
| 5 | << >> | Left to right |
| 6 | < <= > >= | Left to right |
| 7 | == != | Left to right |
| 8 | & | Left to right |
| 9 | ^ | Left to right |
| 10 | \| | Left to right |
| 11 | && | Left to right |
| 12 | \|\| | Left to right |
| 13 | ?: | Right to left |
| 14 (Lowest) | = += -= *= /= %= | Right to left |

## Key Concepts

### Operator Precedence
- Determines the order of evaluation in expressions
- Use parentheses to override default precedence
- Example: `2 + 3 * 4` equals `14`, not `20`

### Associativity
- Determines evaluation order for operators of same precedence
- Most operators are left-to-right associative
- Assignment operators are right-to-left associative

### Expression Evaluation
- Expressions combine operands and operators
- Side effects (like ++ and --) can affect evaluation order
- Avoid undefined behavior with multiple side effects

## Common Pitfalls

1. **Assignment vs Comparison**: Don't confuse `=` with `==`
2. **Integer Division**: `5/2` equals `2`, not `2.5`
3. **Operator Precedence**: `a + b * c` is `a + (b * c)`, not `(a + b) * c`
4. **Bitwise vs Logical**: `&` vs `&&`, `|` vs `||`
5. **Pre vs Post Increment**: `++i` vs `i++` in complex expressions

## Best Practices

1. Use parentheses to make precedence explicit
2. Avoid complex expressions with multiple side effects
3. Use meaningful variable names in expressions
4. Break complex expressions into simpler parts
5. Use appropriate data types for operations

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

The program demonstrates each operator type with clear examples and explanations, showing how different operators work and interact with each other.

## Next Steps

After mastering operators and expressions, you'll learn about control structures (if/else, switch) in the next lesson, which use these operators to make decisions in your programs.