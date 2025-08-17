#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== C Pointers and Memory Lesson ===\n\n");
    
    // 1. Basic pointer declaration and initialization
    printf("1. Basic Pointer Declaration and Initialization:\n");
    int number = 42;
    int *ptr = &number;  // Pointer to int, initialized with address of number
    
    printf("   Value of number: %d\n", number);
    printf("   Address of number: %p\n", (void*)&number);
    printf("   Value of ptr (address it points to): %p\n", (void*)ptr);
    printf("   Value pointed to by ptr: %d\n", *ptr);
    printf("   Address of ptr itself: %p\n\n", (void*)&ptr);
    
    // 2. Pointer dereferencing and modification
    printf("2. Pointer Dereferencing and Modification:\n");
    printf("   Original value: %d\n", number);
    *ptr = 100;  // Modify value through pointer
    printf("   After *ptr = 100: %d\n", number);
    printf("   Both number and *ptr show: %d\n\n", *ptr);
    
    // 3. Address-of operator examples
    printf("3. Address-of Operator (&) Examples:\n");
    char character = 'A';
    float decimal = 3.14f;
    double precision = 2.71828;
    
    char *char_ptr = &character;
    float *float_ptr = &decimal;
    double *double_ptr = &precision;
    
    printf("   char variable '%c' at address: %p (via pointer: %c)\n", character, (void*)char_ptr, *char_ptr);
    printf("   float variable %.2f at address: %p (via pointer: %.2f)\n", decimal, (void*)float_ptr, *float_ptr);
    printf("   double variable %.5f at address: %p (via pointer: %.5f)\n\n", precision, (void*)double_ptr, *double_ptr);
    
    // 4. Pointer arithmetic
    printf("4. Pointer Arithmetic:\n");
    int array[5] = {10, 20, 30, 40, 50};
    int *array_ptr = array;  // Points to first element
    
    printf("   Array elements using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("   array_ptr + %d = %p, value = %d\n", 
               i, (void*)(array_ptr + i), *(array_ptr + i));
    }
    
    printf("\n   Moving pointer through array:\n");
    array_ptr = array;  // Reset to beginning
    for (int i = 0; i < 5; i++) {
        printf("   Current position: %p, value: %d\n", (void*)array_ptr, *array_ptr);
        array_ptr++;  // Move to next element
    }
    printf("\n");
    
    // 5. Null pointers and safety
    printf("5. Null Pointers and Safety:\n");
    int *null_ptr = NULL;
    printf("   Null pointer value: %p\n", (void*)null_ptr);
    
    // Safe pointer usage - always check before dereferencing
    if (null_ptr != NULL) {
        printf("   Safe to dereference: %d\n", *null_ptr);
    } else {
        printf("   Pointer is NULL - cannot dereference safely\n");
    }
    
    // Initialize pointer properly
    int safe_value = 123;
    null_ptr = &safe_value;
    if (null_ptr != NULL) {
        printf("   Now pointer is safe: %d\n", *null_ptr);
    }
    printf("\n");
    
    // 6. Pointer to pointer
    printf("6. Pointer to Pointer:\n");
    int original = 999;
    int *first_ptr = &original;
    int **second_ptr = &first_ptr;  // Pointer to pointer
    
    printf("   Original value: %d\n", original);
    printf("   Value through first_ptr: %d\n", *first_ptr);
    printf("   Value through second_ptr: %d\n", **second_ptr);
    printf("   Address of original: %p\n", (void*)&original);
    printf("   Value of first_ptr: %p\n", (void*)first_ptr);
    printf("   Value of second_ptr: %p\n", (void*)second_ptr);
    printf("   Address of first_ptr: %p\n\n", (void*)&first_ptr);
    
    // 7. Dynamic memory allocation (basic example)
    printf("7. Dynamic Memory Allocation:\n");
    int *dynamic_ptr = (int*)malloc(sizeof(int));
    
    if (dynamic_ptr != NULL) {
        *dynamic_ptr = 777;
        printf("   Dynamically allocated value: %d\n", *dynamic_ptr);
        printf("   Address of dynamic memory: %p\n", (void*)dynamic_ptr);
        
        // Always free dynamically allocated memory
        free(dynamic_ptr);
        printf("   Memory freed successfully\n");
        
        // Good practice: set pointer to NULL after freeing
        dynamic_ptr = NULL;
    } else {
        printf("   Memory allocation failed!\n");
    }
    
    printf("\n=== End of Pointers and Memory Lesson ===\n");
    return 0;
}