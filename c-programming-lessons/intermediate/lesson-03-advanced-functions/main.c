#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void demonstrate_pass_by_value(int x);
void demonstrate_pass_by_reference(int *x);
void swap_values(int *a, int *b);
int factorial_recursive(int n);
int factorial_iterative(int n);
int fibonacci_recursive(int n);
int fibonacci_iterative(int n);
void print_array(int arr[], int size);
void modify_array(int arr[], int size);
int find_maximum(int arr[], int size);
double calculate_average(int arr[], int size);
void reverse_string(char *str);
int string_length_recursive(char *str);
void tower_of_hanoi(int n, char from, char to, char aux);
int binary_search(int arr[], int left, int right, int target);

int main() {
    printf("=== Advanced Functions in C ===\n\n");
    
    // 1. Pass by Value vs Pass by Reference
    printf("1. Pass by Value vs Pass by Reference:\n");
    int original = 42;
    
    printf("   Original value: %d\n", original);
    demonstrate_pass_by_value(original);
    printf("   After pass by value: %d\n", original);
    
    demonstrate_pass_by_reference(&original);
    printf("   After pass by reference: %d\n\n", original);
    
    // 2. Function Parameters and Return Values
    printf("2. Function Parameters and Return Values:\n");
    int a = 10, b = 20;
    printf("   Before swap: a = %d, b = %d\n", a, b);
    swap_values(&a, &b);
    printf("   After swap: a = %d, b = %d\n\n", a, b);
    
    // 3. Recursive Functions
    printf("3. Recursive Functions:\n");
    int n = 5;
    printf("   Factorial of %d (recursive): %d\n", n, factorial_recursive(n));
    printf("   Factorial of %d (iterative): %d\n", n, factorial_iterative(n));
    
    printf("   Fibonacci sequence (recursive): ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", fibonacci_recursive(i));
    }
    printf("\n");
    
    printf("   Fibonacci sequence (iterative): ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", fibonacci_iterative(i));
    }
    printf("\n\n");
    
    // 4. Functions with Arrays
    printf("4. Functions with Arrays:\n");
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("   Original array: ");
    print_array(numbers, size);
    
    printf("   Maximum value: %d\n", find_maximum(numbers, size));
    printf("   Average value: %.2f\n", calculate_average(numbers, size));
    
    modify_array(numbers, size);
    printf("   Modified array: ");
    print_array(numbers, size);
    printf("\n");
    
    // 5. Functions with Strings
    printf("5. Functions with Strings:\n");
    char text[] = "Hello World";
    printf("   Original string: \"%s\"\n", text);
    printf("   String length (recursive): %d\n", string_length_recursive(text));
    
    reverse_string(text);
    printf("   Reversed string: \"%s\"\n\n", text);
    
    // 6. Advanced Recursion Example
    printf("6. Advanced Recursion - Tower of Hanoi:\n");
    printf("   Solution for 3 disks:\n");
    tower_of_hanoi(3, 'A', 'C', 'B');
    printf("\n");
    
    // 7. Recursive Search Algorithm
    printf("7. Recursive Search - Binary Search:\n");
    int sorted_array[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int array_size = sizeof(sorted_array) / sizeof(sorted_array[0]);
    int target = 23;
    
    printf("   Sorted array: ");
    print_array(sorted_array, array_size);
    
    int result = binary_search(sorted_array, 0, array_size - 1, target);
    if (result != -1) {
        printf("   Found %d at index %d\n", target, result);
    } else {
        printf("   %d not found in array\n", target);
    }
    
    target = 99;
    result = binary_search(sorted_array, 0, array_size - 1, target);
    if (result != -1) {
        printf("   Found %d at index %d\n", target, result);
    } else {
        printf("   %d not found in array\n", target);
    }
    
    printf("\n=== End of Advanced Functions Lesson ===\n");
    return 0;
}

// Function implementations

void demonstrate_pass_by_value(int x) {
    printf("   Inside pass_by_value: x = %d\n", x);
    x = 999;  // This change won't affect the original variable
    printf("   Modified x inside function: %d\n", x);
}

void demonstrate_pass_by_reference(int *x) {
    printf("   Inside pass_by_reference: *x = %d\n", *x);
    *x = 777;  // This change will affect the original variable
    printf("   Modified *x inside function: %d\n", *x);
}

void swap_values(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int factorial_recursive(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial_recursive(n - 1);
}

int factorial_iterative(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int fibonacci_recursive(int n) {
    // Base cases
    if (n <= 1) {
        return n;
    }
    // Recursive case
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

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

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void modify_array(int arr[], int size) {
    // Double each element
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int find_maximum(int arr[], int size) {
    if (size <= 0) return 0;
    
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

double calculate_average(int arr[], int size) {
    if (size <= 0) return 0.0;
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

void reverse_string(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

int string_length_recursive(char *str) {
    // Base case
    if (*str == '\0') {
        return 0;
    }
    // Recursive case
    return 1 + string_length_recursive(str + 1);
}

void tower_of_hanoi(int n, char from, char to, char aux) {
    // Base case
    if (n == 1) {
        printf("   Move disk 1 from %c to %c\n", from, to);
        return;
    }
    
    // Recursive cases
    tower_of_hanoi(n - 1, from, aux, to);
    printf("   Move disk %d from %c to %c\n", n, from, to);
    tower_of_hanoi(n - 1, aux, to, from);
}

int binary_search(int arr[], int left, int right, int target) {
    // Base case: element not found
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    // Base case: element found
    if (arr[mid] == target) {
        return mid;
    }
    
    // Recursive cases
    if (target < arr[mid]) {
        return binary_search(arr, left, mid - 1, target);
    } else {
        return binary_search(arr, mid + 1, right, target);
    }
}