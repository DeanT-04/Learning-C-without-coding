#include <stdio.h>

int main() {
    printf("=== C Operators and Expressions Demo ===\n\n");
    
    // Variables for demonstrations
    int a = 15, b = 4, c = 10;
    int result;
    float x = 7.5, y = 2.5;
    
    // 1. ARITHMETIC OPERATORS
    printf("1. ARITHMETIC OPERATORS\n");
    printf("a = %d, b = %d\n", a, b);
    printf("Addition (a + b): %d\n", a + b);
    printf("Subtraction (a - b): %d\n", a - b);
    printf("Multiplication (a * b): %d\n", a * b);
    printf("Division (a / b): %d\n", a / b);
    printf("Modulus (a %% b): %d\n", a % b);
    printf("Float division (%.1f / %.1f): %.2f\n\n", x, y, x / y);
    
    // 2. RELATIONAL OPERATORS
    printf("2. RELATIONAL OPERATORS\n");
    printf("a = %d, b = %d, c = %d\n", a, b, c);
    printf("a > b: %s\n", (a > b) ? "true" : "false");
    printf("a < b: %s\n", (a < b) ? "true" : "false");
    printf("a >= c: %s\n", (a >= c) ? "true" : "false");
    printf("a <= c: %s\n", (a <= c) ? "true" : "false");
    printf("a == c: %s\n", (a == c) ? "true" : "false");
    printf("a != b: %s\n\n", (a != b) ? "true" : "false");
    
    // 3. LOGICAL OPERATORS
    printf("3. LOGICAL OPERATORS\n");
    int p = 1, q = 0;  // 1 = true, 0 = false
    printf("p = %d (true), q = %d (false)\n", p, q);
    printf("p && q (AND): %d\n", p && q);
    printf("p || q (OR): %d\n", p || q);
    printf("!p (NOT p): %d\n", !p);
    printf("!q (NOT q): %d\n\n", !q);
    
    // 4. BITWISE OPERATORS
    printf("4. BITWISE OPERATORS\n");
    unsigned int m = 12, n = 10;  // 12 = 1100, 10 = 1010 in binary
    printf("m = %u (binary: 1100), n = %u (binary: 1010)\n", m, n);
    printf("m & n (AND): %u\n", m & n);      // 1000 = 8
    printf("m | n (OR): %u\n", m | n);       // 1110 = 14
    printf("m ^ n (XOR): %u\n", m ^ n);      // 0110 = 6
    printf("~m (NOT): %u\n", ~m);            // Bitwise complement
    printf("m << 1 (Left shift): %u\n", m << 1);   // 11000 = 24
    printf("m >> 1 (Right shift): %u\n\n", m >> 1); // 0110 = 6
    
    // 5. ASSIGNMENT OPERATORS
    printf("5. ASSIGNMENT OPERATORS\n");
    result = a;
    printf("result = a: %d\n", result);
    result += b;
    printf("result += b: %d\n", result);
    result -= 5;
    printf("result -= 5: %d\n", result);
    result *= 2;
    printf("result *= 2: %d\n", result);
    result /= 3;
    printf("result /= 3: %d\n", result);
    result %= 4;
    printf("result %%= 4: %d\n\n", result);
    
    // 6. INCREMENT/DECREMENT OPERATORS
    printf("6. INCREMENT/DECREMENT OPERATORS\n");
    int i = 5, j = 5;
    printf("Initial: i = %d, j = %d\n", i, j);
    printf("Pre-increment ++i: %d\n", ++i);
    printf("Post-increment j++: %d\n", j++);
    printf("After increment: i = %d, j = %d\n", i, j);
    printf("Pre-decrement --i: %d\n", --i);
    printf("Post-decrement j--: %d\n", j--);
    printf("Final values: i = %d, j = %d\n\n", i, j);
    
    // 7. OPERATOR PRECEDENCE EXAMPLES
    printf("7. OPERATOR PRECEDENCE EXAMPLES\n");
    int val1 = 2 + 3 * 4;           // Multiplication first: 2 + 12 = 14
    int val2 = (2 + 3) * 4;         // Parentheses first: 5 * 4 = 20
    int val3 = 10 > 5 && 3 < 7;     // Relational then logical: 1 && 1 = 1
    printf("2 + 3 * 4 = %d (multiplication first)\n", val1);
    printf("(2 + 3) * 4 = %d (parentheses first)\n", val2);
    printf("10 > 5 && 3 < 7 = %d (relational then logical)\n\n", val3);
    
    // 8. ASSOCIATIVITY EXAMPLES
    printf("8. ASSOCIATIVITY EXAMPLES\n");
    int assoc1 = 20 - 10 - 5;       // Left-to-right: (20 - 10) - 5 = 5
    int assoc2 = 2 * 3 * 4;         // Left-to-right: (2 * 3) * 4 = 24
    printf("20 - 10 - 5 = %d (left-to-right associativity)\n", assoc1);
    printf("2 * 3 * 4 = %d (left-to-right associativity)\n\n", assoc2);
    
    // 9. CONDITIONAL (TERNARY) OPERATOR
    printf("9. CONDITIONAL (TERNARY) OPERATOR\n");
    int max = (a > b) ? a : b;
    printf("max = (a > b) ? a : b = %d\n", max);
    printf("Status: %s\n\n", (a > 10) ? "High value" : "Low value");
    
    // 10. SIZEOF OPERATOR
    printf("10. SIZEOF OPERATOR\n");
    printf("sizeof(int): %zu bytes\n", sizeof(int));
    printf("sizeof(float): %zu bytes\n", sizeof(float));
    printf("sizeof(double): %zu bytes\n", sizeof(double));
    printf("sizeof(char): %zu bytes\n\n", sizeof(char));
    
    return 0;
}