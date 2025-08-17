#include <math.h>
#include "math_operations.h"
#include "config.h"

// Basic arithmetic operations for doubles
double add_double(double a, double b) {
    DEBUG_PRINT("Adding %.2f + %.2f", a, b);
    return a + b;
}

double subtract_double(double a, double b) {
    DEBUG_PRINT("Subtracting %.2f - %.2f", a, b);
    return a - b;
}

double multiply_double(double a, double b) {
    DEBUG_PRINT("Multiplying %.2f * %.2f", a, b);
    return a * b;
}

double divide_double(double a, double b) {
    DEBUG_PRINT("Dividing %.2f / %.2f", a, b);
    if (b == 0.0) {
        DEBUG_PRINT("Division by zero detected");
        return 0.0;  // Or could return NaN or handle error differently
    }
    return a / b;
}

double power_double(double base, double exponent) {
    DEBUG_PRINT("Calculating %.2f ^ %.2f", base, exponent);
    return pow(base, exponent);
}

double sqrt_double(double x) {
    DEBUG_PRINT("Calculating square root of %.2f", x);
    if (x < 0.0) {
        DEBUG_PRINT("Negative input for square root");
        return 0.0;  // Or could return NaN
    }
    return sqrt(x);
}

// Advanced mathematical functions
long factorial(int n) {
    DEBUG_PRINT("Calculating factorial of %d", n);
    if (n < 0) {
        return 0;  // Undefined for negative numbers
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    
    long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

long fibonacci(int n) {
    DEBUG_PRINT("Calculating fibonacci of %d", n);
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    long prev = 0, curr = 1, next;
    for (int i = 2; i <= n; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int gcd(int a, int b) {
    DEBUG_PRINT("Calculating GCD of %d and %d", a, b);
    a = abs(a);  // Work with positive numbers
    b = abs(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    DEBUG_PRINT("Calculating LCM of %d and %d", a, b);
    if (a == 0 || b == 0) {
        return 0;
    }
    return abs(a * b) / gcd(a, b);
}

int is_prime(int n) {
    DEBUG_PRINT("Checking if %d is prime", n);
    if (n < 2) {
        return 0;  // Not prime
    }
    if (n == 2) {
        return 1;  // Prime
    }
    if (n % 2 == 0) {
        return 0;  // Even numbers > 2 are not prime
    }
    
    // Check odd divisors up to sqrt(n)
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return 0;  // Not prime
        }
    }
    return 1;  // Prime
}

// Utility functions
double absolute_double(double x) {
    return (x < 0.0) ? -x : x;
}

double max_double(double a, double b) {
    return (a > b) ? a : b;
}

double min_double(double a, double b) {
    return (a < b) ? a : b;
}

int max_int(int a, int b) {
    return (a > b) ? a : b;
}

int min_int(int a, int b) {
    return (a < b) ? a : b;
}