#include <stdio.h>

int main() {
    printf("=== C Programming: Loops Lesson ===\n\n");
    
    // 1. FOR LOOP EXAMPLES
    printf("1. FOR LOOP EXAMPLES:\n");
    printf("-------------------\n");
    
    // Basic for loop
    printf("Basic for loop (counting 1 to 5):\n");
    for (int i = 1; i <= 5; i++) {
        printf("Count: %d\n", i);
    }
    printf("\n");
    
    // For loop with different increment
    printf("For loop with increment of 2:\n");
    for (int i = 0; i <= 10; i += 2) {
        printf("Even number: %d\n", i);
    }
    printf("\n");
    
    // For loop counting backwards
    printf("For loop counting backwards:\n");
    for (int i = 5; i >= 1; i--) {
        printf("Countdown: %d\n", i);
    }
    printf("\n");
    
    // 2. WHILE LOOP EXAMPLES
    printf("2. WHILE LOOP EXAMPLES:\n");
    printf("----------------------\n");
    
    // Basic while loop
    printf("Basic while loop (counting 1 to 3):\n");
    int count = 1;
    while (count <= 3) {
        printf("While count: %d\n", count);
        count++;
    }
    printf("\n");
    
    // While loop with user input simulation
    printf("While loop with condition checking:\n");
    int number = 16;
    while (number > 1) {
        printf("Number: %d\n", number);
        number /= 2;  // Divide by 2 each iteration
    }
    printf("Final number: %d\n\n", number);
    
    // 3. DO-WHILE LOOP EXAMPLES
    printf("3. DO-WHILE LOOP EXAMPLES:\n");
    printf("-------------------------\n");
    
    // Basic do-while loop
    printf("Basic do-while loop (executes at least once):\n");
    int value = 0;
    do {
        printf("Do-while value: %d\n", value);
        value++;
    } while (value < 3);
    printf("\n");
    
    // Do-while vs while comparison
    printf("Do-while vs while when condition is false from start:\n");
    int test = 10;
    
    printf("Do-while (executes once even when condition is false):\n");
    do {
        printf("Do-while executed with test = %d\n", test);
        test++;
    } while (test < 5);  // Condition is false from start
    
    test = 10;  // Reset
    printf("While loop (doesn't execute when condition is false):\n");
    while (test < 5) {  // Condition is false from start
        printf("While executed with test = %d\n", test);
        test++;
    }
    printf("While loop didn't execute because condition was false\n\n");
    
    // 4. NESTED LOOPS
    printf("4. NESTED LOOPS:\n");
    printf("---------------\n");
    
    // Nested for loops - multiplication table
    printf("Multiplication table (3x3):\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("%d x %d = %d\t", i, j, i * j);
        }
        printf("\n");
    }
    printf("\n");
    
    // Nested loops - pattern printing
    printf("Star pattern using nested loops:\n");
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    printf("\n");
    
    // 5. LOOP CONTROL STATEMENTS
    printf("5. LOOP CONTROL STATEMENTS:\n");
    printf("---------------------------\n");
    
    // Break statement
    printf("Using 'break' to exit loop early:\n");
    for (int i = 1; i <= 10; i++) {
        if (i == 6) {
            printf("Breaking at i = %d\n", i);
            break;  // Exit the loop when i equals 6
        }
        printf("i = %d\n", i);
    }
    printf("\n");
    
    // Continue statement
    printf("Using 'continue' to skip iterations:\n");
    for (int i = 1; i <= 8; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        printf("Odd number: %d\n", i);
    }
    printf("\n");
    
    // Break and continue in nested loops
    printf("Break and continue in nested loops:\n");
    for (int i = 1; i <= 3; i++) {
        printf("Outer loop i = %d:\n", i);
        for (int j = 1; j <= 5; j++) {
            if (j == 3) {
                printf("  Skipping j = %d\n", j);
                continue;  // Skip when j = 3
            }
            if (j == 5) {
                printf("  Breaking at j = %d\n", j);
                break;  // Break inner loop when j = 5
            }
            printf("  Inner loop j = %d\n", j);
        }
    }
    printf("\n");
    
    // 6. PRACTICAL EXAMPLES
    printf("6. PRACTICAL EXAMPLES:\n");
    printf("---------------------\n");
    
    // Sum of numbers
    printf("Sum of numbers 1 to 10 using for loop:\n");
    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        sum += i;
    }
    printf("Sum = %d\n\n", sum);
    
    // Factorial calculation
    printf("Factorial of 5 using while loop:\n");
    int factorial = 1;
    int n = 5;
    int temp = n;
    while (temp > 0) {
        factorial *= temp;
        temp--;
    }
    printf("%d! = %d\n\n", n, factorial);
    
    // Finding prime numbers
    printf("Prime numbers between 2 and 20:\n");
    for (int num = 2; num <= 20; num++) {
        int is_prime = 1;  // Assume prime
        
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0;  // Not prime
                break;
            }
        }
        
        if (is_prime) {
            printf("%d ", num);
        }
    }
    printf("\n\n");
    
    printf("=== End of Loops Lesson ===\n");
    return 0;
}