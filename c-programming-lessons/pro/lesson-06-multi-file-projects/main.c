#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_operations.h"
#include "string_utils.h"
#include "student_manager.h"
#include "config.h"

int main(void) {
    printf("=== Multi-File Project Demonstration ===\n");
    printf("Version: %s\n", PROJECT_VERSION);
    printf("Build Date: %s\n", BUILD_DATE);
    printf("Debug Mode: %s\n\n", DEBUG_MODE ? "ON" : "OFF");
    
    // Demonstrate math operations module
    printf("1. Math Operations Module:\n");
    printf("--------------------------\n");
    
    double a = 15.5, b = 4.2;
    printf("a = %.2f, b = %.2f\n", a, b);
    printf("Addition: %.2f + %.2f = %.2f\n", a, b, add_double(a, b));
    printf("Subtraction: %.2f - %.2f = %.2f\n", a, b, subtract_double(a, b));
    printf("Multiplication: %.2f * %.2f = %.2f\n", a, b, multiply_double(a, b));
    printf("Division: %.2f / %.2f = %.2f\n", a, b, divide_double(a, b));
    printf("Power: %.2f ^ %.2f = %.2f\n", a, b, power_double(a, b));
    printf("Square root of %.2f = %.2f\n", a, sqrt_double(a));
    
    int x = 25, y = 7;
    printf("\nInteger operations: x = %d, y = %d\n", x, y);
    printf("GCD(%d, %d) = %d\n", x, y, gcd(x, y));
    printf("LCM(%d, %d) = %d\n", x, y, lcm(x, y));
    printf("Factorial(%d) = %ld\n", 5, factorial(5));
    printf("Fibonacci(10) = %ld\n", fibonacci(10));
    printf("Is %d prime? %s\n", 17, is_prime(17) ? "Yes" : "No");
    printf("Is %d prime? %s\n", 18, is_prime(18) ? "Yes" : "No");
    
    // Demonstrate string utilities module
    printf("\n2. String Utilities Module:\n");
    printf("---------------------------\n");
    
    char str1[] = "Hello World";
    char str2[] = "Programming";
    char result[100];
    
    printf("Original string: '%s'\n", str1);
    
    string_to_upper(str1);
    printf("Uppercase: '%s'\n", str1);
    
    strcpy(str1, "Hello World");  // Reset
    string_to_lower(str1);
    printf("Lowercase: '%s'\n", str1);
    
    strcpy(str1, "Hello World");  // Reset
    string_reverse(str1);
    printf("Reversed: '%s'\n", str1);
    
    strcpy(str1, "Hello World");  // Reset
    printf("Length: %zu\n", string_length(str1));
    printf("Word count: %d\n", count_words(str1));
    
    strcpy(str1, "Hello");
    strcpy(str2, "World");
    string_concat(str1, str2, result, sizeof(result));
    printf("Concatenation: '%s' + '%s' = '%s'\n", str1, str2, result);
    
    char *trimmed = string_trim("  Hello World  ");
    printf("Trimmed: '%s'\n", trimmed);
    free(trimmed);
    
    printf("Contains 'World' in 'Hello World': %s\n", 
           string_contains("Hello World", "World") ? "Yes" : "No");
    
    // Demonstrate student manager module
    printf("\n3. Student Manager Module:\n");
    printf("--------------------------\n");
    
    StudentManager *manager = create_student_manager();
    if (manager == NULL) {
        printf("Failed to create student manager\n");
        return 1;
    }
    
    // Add students
    printf("Adding students...\n");
    add_student(manager, 101, "Alice Johnson", 3.85);
    add_student(manager, 102, "Bob Smith", 3.92);
    add_student(manager, 103, "Carol Davis", 3.78);
    add_student(manager, 104, "David Wilson", 3.65);
    
    printf("Total students: %d\n", get_student_count(manager));
    
    // Display all students
    printf("\nAll students:\n");
    display_all_students(manager);
    
    // Find student
    printf("\nSearching for student with ID 102:\n");
    Student *found = find_student(manager, 102);
    if (found != NULL) {
        printf("Found: ID=%d, Name=%s, GPA=%.2f\n", 
               found->id, found->name, found->gpa);
    }
    
    // Update student
    printf("\nUpdating student 103's GPA to 3.90:\n");
    if (update_student_gpa(manager, 103, 3.90)) {
        printf("Update successful\n");
    }
    
    // Calculate statistics
    printf("\nClass statistics:\n");
    printf("Average GPA: %.2f\n", calculate_average_gpa(manager));
    printf("Highest GPA: %.2f\n", calculate_highest_gpa(manager));
    printf("Lowest GPA: %.2f\n", calculate_lowest_gpa(manager));
    
    // Sort students
    printf("\nSorting students by GPA (descending):\n");
    sort_students_by_gpa(manager);
    display_all_students(manager);
    
    // Remove student
    printf("\nRemoving student with ID 102:\n");
    if (remove_student(manager, 102)) {
        printf("Student removed successfully\n");
        printf("Remaining students: %d\n", get_student_count(manager));
        display_all_students(manager);
    }
    
    // Save to file
    printf("\nSaving students to file...\n");
    if (save_students_to_file(manager, "students.txt")) {
        printf("Students saved successfully\n");
    }
    
    // Clear and load from file
    printf("\nClearing manager and loading from file...\n");
    clear_all_students(manager);
    printf("Students after clearing: %d\n", get_student_count(manager));
    
    if (load_students_from_file(manager, "students.txt")) {
        printf("Students loaded successfully\n");
        printf("Students after loading: %d\n", get_student_count(manager));
        display_all_students(manager);
    }
    
    // Clean up
    destroy_student_manager(manager);
    
    printf("\n4. Project Structure Summary:\n");
    printf("-----------------------------\n");
    printf("This multi-file project demonstrates:\n");
    printf("- Modular code organization\n");
    printf("- Header file interfaces\n");
    printf("- Implementation separation\n");
    printf("- Complex Makefile usage\n");
    printf("- Configuration management\n");
    printf("- Cross-module dependencies\n");
    printf("- Professional project structure\n");
    
    return 0;
}