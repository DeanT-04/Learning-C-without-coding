#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for demonstration
struct Student {
    int id;
    char *name;
    float gpa;
};

// Function prototypes
void demonstrate_malloc(void);
void demonstrate_calloc(void);
void demonstrate_realloc(void);
void demonstrate_memory_leaks(void);
void demonstrate_dynamic_arrays(void);
void demonstrate_dynamic_structures(void);
void demonstrate_2d_arrays(void);
void safe_memory_practices(void);

int main(void) {
    printf("=== Dynamic Memory Allocation in C ===\n\n");
    
    demonstrate_malloc();
    demonstrate_calloc();
    demonstrate_realloc();
    demonstrate_dynamic_arrays();
    demonstrate_dynamic_structures();
    demonstrate_2d_arrays();
    demonstrate_memory_leaks();
    safe_memory_practices();
    
    return 0;
}

void demonstrate_malloc(void) {
    printf("1. malloc() - Memory Allocation:\n");
    printf("--------------------------------\n");
    
    // Allocate memory for integers
    int *ptr = malloc(5 * sizeof(int));
    
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    printf("Allocated memory for 5 integers\n");
    
    // Initialize and display values
    for (int i = 0; i < 5; i++) {
        ptr[i] = (i + 1) * 10;
        printf("ptr[%d] = %d (uninitialized was: garbage)\n", i, ptr[i]);
    }
    
    printf("Memory address: %p\n", (void*)ptr);
    printf("Size allocated: %zu bytes\n", 5 * sizeof(int));
    
    // Free the memory
    free(ptr);
    ptr = NULL;  // Good practice to avoid dangling pointers
    printf("Memory freed and pointer set to NULL\n\n");
}

void demonstrate_calloc(void) {
    printf("2. calloc() - Cleared Memory Allocation:\n");
    printf("----------------------------------------\n");
    
    // Allocate and initialize memory to zero
    int *ptr = calloc(5, sizeof(int));
    
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    printf("Allocated memory for 5 integers (initialized to 0)\n");
    
    // Display initial zero values
    printf("Initial values: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // Set some values
    for (int i = 0; i < 5; i++) {
        ptr[i] = (i + 1) * 20;
    }
    
    printf("After assignment: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    free(ptr);
    printf("Memory freed\n\n");
}

void demonstrate_realloc(void) {
    printf("3. realloc() - Memory Reallocation:\n");
    printf("-----------------------------------\n");
    
    // Initial allocation
    int *ptr = malloc(3 * sizeof(int));
    if (ptr == NULL) {
        printf("Initial allocation failed!\n");
        return;
    }
    
    // Initialize initial values
    for (int i = 0; i < 3; i++) {
        ptr[i] = i + 1;
    }
    
    printf("Initial array (3 elements): ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // Expand the array
    ptr = realloc(ptr, 6 * sizeof(int));
    if (ptr == NULL) {
        printf("Reallocation failed!\n");
        return;
    }
    
    // Initialize new elements
    for (int i = 3; i < 6; i++) {
        ptr[i] = i + 1;
    }
    
    printf("Expanded array (6 elements): ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // Shrink the array
    ptr = realloc(ptr, 4 * sizeof(int));
    if (ptr == NULL) {
        printf("Reallocation failed!\n");
        return;
    }
    
    printf("Shrunk array (4 elements): ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // Free with realloc(ptr, 0) - equivalent to free(ptr)
    ptr = realloc(ptr, 0);
    printf("Memory freed using realloc(ptr, 0)\n\n");
}

void demonstrate_dynamic_arrays(void) {
    printf("4. Dynamic Arrays:\n");
    printf("------------------\n");
    
    int size;
    printf("Enter array size: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid input, using default size 5\n");
        size = 5;
    }
    
    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    // Allocate dynamic array
    double *array = malloc(size * sizeof(double));
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Fill array with values
    printf("Filling array with squares:\n");
    for (int i = 0; i < size; i++) {
        array[i] = (i + 1) * (i + 1) * 1.5;
        printf("array[%d] = %.2f\n", i, array[i]);
    }
    
    // Calculate sum
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    printf("Sum of all elements: %.2f\n", sum);
    
    free(array);
    printf("Dynamic array freed\n\n");
}

void demonstrate_dynamic_structures(void) {
    printf("5. Dynamic Structures:\n");
    printf("----------------------\n");
    
    // Allocate memory for a student
    struct Student *student = malloc(sizeof(struct Student));
    if (student == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Initialize student data
    student->id = 12345;
    student->gpa = 3.75;
    
    // Allocate memory for name
    student->name = malloc(50 * sizeof(char));
    if (student->name == NULL) {
        printf("Name allocation failed!\n");
        free(student);
        return;
    }
    
    strcpy(student->name, "John Smith");
    
    printf("Student created:\n");
    printf("ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("GPA: %.2f\n", student->gpa);
    
    // Create array of students
    int num_students = 3;
    struct Student *students = malloc(num_students * sizeof(struct Student));
    if (students == NULL) {
        printf("Students array allocation failed!\n");
        free(student->name);
        free(student);
        return;
    }
    
    // Initialize students array
    for (int i = 0; i < num_students; i++) {
        students[i].id = 1000 + i;
        students[i].gpa = 3.0 + (i * 0.25);
        students[i].name = malloc(30 * sizeof(char));
        if (students[i].name != NULL) {
            sprintf(students[i].name, "Student_%d", i + 1);
        }
    }
    
    printf("\nStudents array:\n");
    for (int i = 0; i < num_students; i++) {
        if (students[i].name != NULL) {
            printf("Student %d: ID=%d, Name=%s, GPA=%.2f\n", 
                   i + 1, students[i].id, students[i].name, students[i].gpa);
        }
    }
    
    // Free all allocated memory
    free(student->name);
    free(student);
    
    for (int i = 0; i < num_students; i++) {
        free(students[i].name);
    }
    free(students);
    
    printf("All student memory freed\n\n");
}

void demonstrate_2d_arrays(void) {
    printf("6. Dynamic 2D Arrays:\n");
    printf("---------------------\n");
    
    int rows = 3, cols = 4;
    
    // Method 1: Array of pointers
    int **matrix1 = malloc(rows * sizeof(int*));
    if (matrix1 == NULL) {
        printf("Matrix allocation failed!\n");
        return;
    }
    
    for (int i = 0; i < rows; i++) {
        matrix1[i] = malloc(cols * sizeof(int));
        if (matrix1[i] == NULL) {
            printf("Row %d allocation failed!\n", i);
            // Free previously allocated rows
            for (int j = 0; j < i; j++) {
                free(matrix1[j]);
            }
            free(matrix1);
            return;
        }
    }
    
    // Fill and display matrix
    printf("Matrix 1 (array of pointers method):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] = i * cols + j + 1;
            printf("%3d ", matrix1[i][j]);
        }
        printf("\n");
    }
    
    // Method 2: Single allocation with pointer arithmetic
    int *matrix2 = malloc(rows * cols * sizeof(int));
    if (matrix2 == NULL) {
        printf("Matrix2 allocation failed!\n");
        // Free matrix1 first
        for (int i = 0; i < rows; i++) {
            free(matrix1[i]);
        }
        free(matrix1);
        return;
    }
    
    printf("\nMatrix 2 (single allocation method):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix2[i * cols + j] = (i + 1) * (j + 1);
            printf("%3d ", matrix2[i * cols + j]);
        }
        printf("\n");
    }
    
    // Free memory
    for (int i = 0; i < rows; i++) {
        free(matrix1[i]);
    }
    free(matrix1);
    free(matrix2);
    
    printf("2D arrays freed\n\n");
}

void demonstrate_memory_leaks(void) {
    printf("7. Memory Leak Prevention:\n");
    printf("--------------------------\n");
    
    printf("Common memory leak scenarios:\n\n");
    
    // Scenario 1: Forgetting to free
    printf("Scenario 1: Always free allocated memory\n");
    int *ptr1 = malloc(100 * sizeof(int));
    if (ptr1 != NULL) {
        printf("Memory allocated at %p\n", (void*)ptr1);
        // Do some work...
        free(ptr1);  // Don't forget this!
        ptr1 = NULL; // Prevent accidental reuse
        printf("Memory properly freed\n");
    }
    
    // Scenario 2: Double free prevention
    printf("\nScenario 2: Prevent double free\n");
    int *ptr2 = malloc(50 * sizeof(int));
    if (ptr2 != NULL) {
        printf("Memory allocated\n");
        free(ptr2);
        ptr2 = NULL;  // Set to NULL after freeing
        
        // This would be safe now (free(NULL) is safe)
        free(ptr2);  // This is safe - free(NULL) does nothing
        printf("Double free prevented by setting pointer to NULL\n");
    }
    
    // Scenario 3: Memory leak in error conditions
    printf("\nScenario 3: Proper cleanup in error conditions\n");
    char *buffer1 = malloc(1000);
    char *buffer2 = malloc(2000);
    
    if (buffer1 == NULL || buffer2 == NULL) {
        printf("Allocation failed - cleaning up\n");
        free(buffer1);  // Safe even if NULL
        free(buffer2);  // Safe even if NULL
        return;
    }
    
    printf("Both buffers allocated successfully\n");
    // Simulate some work...
    
    // Clean up
    free(buffer1);
    free(buffer2);
    printf("All memory properly cleaned up\n\n");
}

void safe_memory_practices(void) {
    printf("8. Safe Memory Management Practices:\n");
    printf("------------------------------------\n");
    
    printf("Best practices demonstrated:\n");
    
    // Practice 1: Always check return values
    printf("\n1. Always check malloc return value:\n");
    size_t size = 1000000000;  // Very large allocation
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("   ✓ Allocation failed gracefully handled\n");
    } else {
        printf("   Allocation succeeded (unexpected for this size)\n");
        free(ptr);
    }
    
    // Practice 2: Initialize pointers
    printf("\n2. Initialize pointers to NULL:\n");
    int *safe_ptr = NULL;
    if (safe_ptr == NULL) {
        printf("   ✓ Pointer safely initialized to NULL\n");
    }
    
    // Practice 3: Set pointers to NULL after freeing
    printf("\n3. Set pointers to NULL after freeing:\n");
    safe_ptr = malloc(sizeof(int));
    if (safe_ptr != NULL) {
        *safe_ptr = 42;
        printf("   Value stored: %d\n", *safe_ptr);
        free(safe_ptr);
        safe_ptr = NULL;  // Prevent dangling pointer
        printf("   ✓ Pointer set to NULL after freeing\n");
    }
    
    // Practice 4: Use const for read-only data
    printf("\n4. Use const for read-only allocated data:\n");
    const char *message = malloc(20);
    if (message != NULL) {
        // message[0] = 'H';  // This would cause compiler error with const
        printf("   ✓ Const prevents accidental modification\n");
        free((void*)message);  // Cast away const for freeing
    }
    
    printf("\nMemory management summary:\n");
    printf("- Always check malloc/calloc/realloc return values\n");
    printf("- Free every allocated block exactly once\n");
    printf("- Set pointers to NULL after freeing\n");
    printf("- Use tools like valgrind to detect leaks\n");
    printf("- Match every malloc with exactly one free\n");
}