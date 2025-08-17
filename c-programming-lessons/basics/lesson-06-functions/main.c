#include <stdio.h>

// Function declarations (prototypes)
void greet(void);
int add(int a, int b);
float calculate_average(float num1, float num2, float num3);
void print_array(int arr[], int size);
int factorial(int n);
void swap_values(int *a, int *b);
int is_even(int number);

int main() {
    printf("=== C Functions Demonstration ===\n\n");
    
    // 1. Simple function call with no parameters
    printf("1. Simple function call:\n");
    greet();
    printf("\n");
    
    // 2. Function with parameters and return value
    printf("2. Function with parameters and return value:\n");
    int sum = add(15, 25);
    printf("add(15, 25) = %d\n\n", sum);
    
    // 3. Function with multiple parameters
    printf("3. Function with multiple parameters:\n");
    float avg = calculate_average(85.5, 92.0, 78.5);
    printf("Average of 85.5, 92.0, 78.5 = %.2f\n\n", avg);
    
    // 4. Function with array parameter
    printf("4. Function with array parameter:\n");
    int numbers[] = {10, 20, 30, 40, 50};
    int array_size = sizeof(numbers) / sizeof(numbers[0]);
    printf("Array contents: ");
    print_array(numbers, array_size);
    printf("\n");
    
    // 5. Recursive function
    printf("5. Recursive function:\n");
    int num = 5;
    int fact = factorial(num);
    printf("Factorial of %d = %d\n\n", num, fact);
    
    // 6. Function with pointer parameters (pass by reference)
    printf("6. Function with pointer parameters:\n");
    int x = 10, y = 20;
    printf("Before swap: x = %d, y = %d\n", x, y);
    swap_values(&x, &y);
    printf("After swap: x = %d, y = %d\n\n", x, y);
    
    // 7. Function returning boolean-like value
    printf("7. Function returning boolean-like value:\n");
    int test_numbers[] = {4, 7, 12, 15};
    int test_size = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (int i = 0; i < test_size; i++) {
        if (is_even(test_numbers[i])) {
            printf("%d is even\n", test_numbers[i]);
        } else {
            printf("%d is odd\n", test_numbers[i]);
        }
    }
    
    return 0;
}

// Function definitions

// Simple function with no parameters and no return value
void greet(void) {
    printf("Hello from the greet() function!\n");
}

// Function with parameters and return value
int add(int a, int b) {
    return a + b;
}

// Function with multiple parameters
float calculate_average(float num1, float num2, float num3) {
    return (num1 + num2 + num3) / 3.0;
}

// Function that takes an array as parameter
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Recursive function
int factorial(int n) {
    if (n <= 1) {
        return 1;  // Base case
    }
    return n * factorial(n - 1);  // Recursive call
}

// Function with pointer parameters (pass by reference)
void swap_values(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function returning boolean-like value (0 for false, non-zero for true)
int is_even(int number) {
    return (number % 2 == 0);
}