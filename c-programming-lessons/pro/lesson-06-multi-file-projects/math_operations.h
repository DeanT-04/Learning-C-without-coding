#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

// Basic arithmetic operations for doubles
double add_double(double a, double b);
double subtract_double(double a, double b);
double multiply_double(double a, double b);
double divide_double(double a, double b);
double power_double(double base, double exponent);
double sqrt_double(double x);

// Advanced mathematical functions
long factorial(int n);
long fibonacci(int n);
int gcd(int a, int b);
int lcm(int a, int b);
int is_prime(int n);

// Utility functions
double absolute_double(double x);
double max_double(double a, double b);
double min_double(double a, double b);
int max_int(int a, int b);
int min_int(int a, int b);

#endif // MATH_OPERATIONS_H