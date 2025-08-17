/*
 * Lesson 02: Variables and Data Types
 * 
 * This program demonstrates the fundamental data types in C programming,
 * including their declaration, initialization, and usage.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>

int main() {
    printf("=== C Programming: Variables and Data Types ===\n\n");
    
    // Integer data types
    printf("1. INTEGER DATA TYPES:\n");
    printf("-------------------\n");
    
    // char - smallest integer type (usually 1 byte)
    char letter = 'A';
    char digit = '5';
    printf("char letter = '%c' (ASCII value: %d)\n", letter, letter);
    printf("char digit = '%c' (ASCII value: %d)\n", digit, digit);
    printf("Size of char: %zu bytes\n", sizeof(char));
    printf("Range: %d to %d\n\n", CHAR_MIN, CHAR_MAX);
    
    // signed char - explicitly signed character
    signed char signed_char = -50;
    printf("signed char = %d\n", signed_char);
    printf("Size of signed char: %zu bytes\n", sizeof(signed char));
    printf("Range: %d to %d\n\n", SCHAR_MIN, SCHAR_MAX);
    
    // unsigned char - unsigned character
    unsigned char unsigned_char = 200;
    printf("unsigned char = %u\n", unsigned_char);
    printf("Size of unsigned char: %zu bytes\n", sizeof(unsigned char));
    printf("Range: 0 to %u\n\n", UCHAR_MAX);
    
    // short int
    short int short_num = 32000;
    printf("short int = %d\n", short_num);
    printf("Size of short: %zu bytes\n", sizeof(short));
    printf("Range: %d to %d\n\n", SHRT_MIN, SHRT_MAX);
    
    // int - most commonly used integer type
    int integer = 42;
    printf("int = %d\n", integer);
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Range: %d to %d\n\n", INT_MIN, INT_MAX);
    
    // long int
    long int long_num = 1000000L;
    printf("long int = %ld\n", long_num);
    printf("Size of long: %zu bytes\n", sizeof(long));
    printf("Range: %ld to %ld\n\n", LONG_MIN, LONG_MAX);
    
    // long long int
    long long int long_long_num = 9223372036854775807LL;
    printf("long long int = %lld\n", long_long_num);
    printf("Size of long long: %zu bytes\n", sizeof(long long));
    printf("Range: %lld to %lld\n\n", LLONG_MIN, LLONG_MAX);
    
    // unsigned variants
    unsigned int unsigned_int = 4000000000U;
    printf("unsigned int = %u\n", unsigned_int);
    printf("Size of unsigned int: %zu bytes\n", sizeof(unsigned int));
    printf("Range: 0 to %u\n\n", UINT_MAX);
    
    // Floating-point data types
    printf("2. FLOATING-POINT DATA TYPES:\n");
    printf("-----------------------------\n");
    
    // float - single precision
    float float_num = 3.14159f;
    printf("float = %.5f\n", float_num);
    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Precision: %d decimal digits\n", FLT_DIG);
    printf("Range: %e to %e\n\n", FLT_MIN, FLT_MAX);
    
    // double - double precision
    double double_num = 3.141592653589793;
    printf("double = %.15f\n", double_num);
    printf("Size of double: %zu bytes\n", sizeof(double));
    printf("Precision: %d decimal digits\n", DBL_DIG);
    printf("Range: %e to %e\n\n", DBL_MIN, DBL_MAX);
    
    // long double - extended precision
    long double long_double_num = 3.141592653589793238L;
    printf("long double = %.18Lf\n", long_double_num);
    printf("Size of long double: %zu bytes\n", sizeof(long double));
    printf("Precision: %d decimal digits\n\n", LDBL_DIG);
    
    // Boolean type (C99 and later)
    printf("3. BOOLEAN DATA TYPE:\n");
    printf("--------------------\n");
    
    bool is_true = true;
    bool is_false = false;
    printf("bool is_true = %s\n", is_true ? "true" : "false");
    printf("bool is_false = %s\n", is_false ? "true" : "false");
    printf("Size of bool: %zu bytes\n\n", sizeof(bool));
    
    // Void type demonstration
    printf("4. VOID TYPE:\n");
    printf("------------\n");
    printf("void is used for functions that don't return a value\n");
    printf("and for generic pointers (void*)\n\n");
    
    // Variable initialization examples
    printf("5. VARIABLE INITIALIZATION:\n");
    printf("---------------------------\n");
    
    // Uninitialized variable (contains garbage value)
    int uninitialized;
    printf("Uninitialized int (garbage value): %d\n", uninitialized);
    
    // Zero initialization
    int zero_init = 0;
    printf("Zero initialized int: %d\n", zero_init);
    
    // Direct initialization
    int direct_init = 100;
    printf("Direct initialized int: %d\n", direct_init);
    
    // Multiple variable declaration
    int a = 10, b = 20, c = 30;
    printf("Multiple variables: a=%d, b=%d, c=%d\n\n", a, b, c);
    
    // Constants
    printf("6. CONSTANTS:\n");
    printf("------------\n");
    
    const int CONSTANT_VALUE = 42;
    printf("const int CONSTANT_VALUE = %d\n", CONSTANT_VALUE);
    
    // Attempting to modify a constant would cause a compilation error
    // CONSTANT_VALUE = 50; // This would cause an error
    
    printf("\nNote: Constants cannot be modified after initialization\n\n");
    
    // Type casting examples
    printf("7. TYPE CASTING:\n");
    printf("---------------\n");
    
    int int_val = 65;
    char char_from_int = (char)int_val;
    printf("int %d cast to char: '%c'\n", int_val, char_from_int);
    
    float float_val = 3.7f;
    int int_from_float = (int)float_val;
    printf("float %.1f cast to int: %d (truncated)\n", float_val, int_from_float);
    
    double large_double = 1234.5678;
    float float_from_double = (float)large_double;
    printf("double %.4f cast to float: %.4f\n\n", large_double, float_from_double);
    
    printf("=== End of Variables and Data Types Demo ===\n");
    
    return 0;
}