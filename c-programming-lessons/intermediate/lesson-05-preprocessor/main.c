#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include our custom headers
#include "config.h"
#include "math_utils.h"

// Preprocessor directives demonstration

// 1. Simple #define macros
#define PROGRAM_NAME "Preprocessor Demo"
#define AUTHOR "C Programming Course"
#define YEAR 2024

// 2. Function-like macros
#define PRINT_HEADER(title) \
    printf("=== %s ===\n", title)

#define PRINT_SEPARATOR() \
    printf("----------------------------------------\n")

// 3. Multi-line macros
#define PRINT_VARIABLE(var) \
    do { \
        printf("Variable: %s = %d\n", #var, var); \
    } while(0)

// 4. Conditional compilation
#define FEATURE_EXPERIMENTAL 0

#if FEATURE_EXPERIMENTAL
    #define EXPERIMENTAL_FUNCTION() printf("Experimental feature enabled!\n")
#else
    #define EXPERIMENTAL_FUNCTION() printf("Experimental feature disabled.\n")
#endif

// 5. Predefined macros demonstration
void show_predefined_macros(void) {
    printf("Predefined Macros:\n");
    printf("  __FILE__: %s\n", __FILE__);
    printf("  __LINE__: %d\n", __LINE__);
    printf("  __DATE__: %s\n", __DATE__);
    printf("  __TIME__: %s\n", __TIME__);
    printf("  __FUNCTION__: %s\n", __FUNCTION__);
    
    #ifdef __STDC__
        printf("  __STDC__: %d (Standard C compliant)\n", __STDC__);
    #endif
    
    #ifdef __STDC_VERSION__
        printf("  __STDC_VERSION__: %ld\n", __STDC_VERSION__);
    #endif
}

// 6. Macro with variable arguments
#define DEBUG_PRINTF(format, ...) \
    printf("[DEBUG %s:%d] " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

// 7. Token pasting operator (##)
#define DECLARE_VARIABLE(type, name) \
    type var_##name

#define PRINT_VAR(name) \
    printf("var_%s = %d\n", #name, var_##name)

int main() {
    PRINT_HEADER(PROGRAM_NAME);
    printf("Author: %s\n", AUTHOR);
    printf("Year: %d\n", YEAR);
    printf("Version: %s\n", VERSION_STRING);
    printf("Platform: %s\n", PLATFORM);
    printf("\n");
    
    // 1. Basic macro usage
    PRINT_HEADER("Basic Macro Usage");
    printf("Maximum buffer size: %d\n", MAX_BUFFER_SIZE);
    printf("Default timeout: %d seconds\n", DEFAULT_TIMEOUT);
    PRINT_SEPARATOR();
    printf("\n");
    
    // 2. Function-like macros
    PRINT_HEADER("Function-like Macros");
    int a = 10, b = 20;
    printf("a = %d, b = %d\n", a, b);
    printf("MAX(a, b) = %d\n", MAX(a, b));
    printf("MIN(a, b) = %d\n", MIN(a, b));
    printf("SQUARE(5) = %d\n", SQUARE(5));
    printf("ABS(-15) = %d\n", ABS(-15));
    
    int value = 25;
    printf("CLAMP(25, 10, 20) = %d\n", CLAMP(value, 10, 20));
    PRINT_SEPARATOR();
    printf("\n");
    
    // 3. Mathematical macros
    PRINT_HEADER("Mathematical Macros");
    printf("PI = %.6f\n", PI);
    printf("E = %.6f\n", E);
    printf("25°C in Fahrenheit: %.1f°F\n", CELSIUS_TO_FAHRENHEIT(25));
    printf("77°F in Celsius: %.1f°C\n", FAHRENHEIT_TO_CELSIUS(77));
    PRINT_SEPARATOR();
    printf("\n");
    
    // 4. Bit manipulation macros
    PRINT_HEADER("Bit Manipulation Macros");
    unsigned int number = 0;
    printf("Initial number: %u (binary: ", number);
    for (int i = 7; i >= 0; i--) {
        printf("%d", CHECK_BIT(number, i));
    }
    printf(")\n");
    
    SET_BIT(number, 2);
    SET_BIT(number, 5);
    printf("After setting bits 2 and 5: %u (binary: ", number);
    for (int i = 7; i >= 0; i--) {
        printf("%d", CHECK_BIT(number, i));
    }
    printf(")\n");
    
    TOGGLE_BIT(number, 2);
    printf("After toggling bit 2: %u (binary: ", number);
    for (int i = 7; i >= 0; i--) {
        printf("%d", CHECK_BIT(number, i));
    }
    printf(")\n");
    PRINT_SEPARATOR();
    printf("\n");
    
    // 5. Stringification operator (#)
    PRINT_HEADER("Stringification Operator");
    int test_var = 42;
    PRINT_VARIABLE(test_var);
    PRINT_SEPARATOR();
    printf("\n");
    
    // 6. Token pasting operator (##)
    PRINT_HEADER("Token Pasting Operator");
    DECLARE_VARIABLE(int, counter);
    DECLARE_VARIABLE(int, total);
    
    var_counter = 5;
    var_total = 100;
    
    PRINT_VAR(counter);
    PRINT_VAR(total);
    PRINT_SEPARATOR();
    printf("\n");
    
    // 7. Conditional compilation
    PRINT_HEADER("Conditional Compilation");
    
    #if ENABLE_DEBUG
        printf("Debug mode is ENABLED\n");
        DEBUG_PRINT("This is a debug message with value: %d", 123);
    #else
        printf("Debug mode is DISABLED\n");
    #endif
    
    #if ENABLE_LOGGING
        LOG_INFO("Logging is enabled");
        LOG_ERROR("This is an error message");
    #endif
    
    EXPERIMENTAL_FUNCTION();
    
    #ifdef VERSION_MAJOR
        printf("Version major is defined: %d\n", VERSION_MAJOR);
    #endif
    
    #ifndef UNDEFINED_MACRO
        printf("UNDEFINED_MACRO is not defined\n");
    #endif
    
    PRINT_SEPARATOR();
    printf("\n");
    
    // 8. Predefined macros
    PRINT_HEADER("Predefined Macros");
    show_predefined_macros();
    PRINT_SEPARATOR();
    printf("\n");
    
    // 9. Array size macro
    PRINT_HEADER("Array Size Macro");
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("Array: ");
    for (size_t i = 0; i < ARRAY_SIZE(numbers); i++) {
        printf("%d ", numbers[i]);
    }
    printf("\nArray size: %zu elements\n", ARRAY_SIZE(numbers));
    PRINT_SEPARATOR();
    printf("\n");
    
    // 10. Macro with variable arguments
    PRINT_HEADER("Variable Arguments Macro");
    DEBUG_PRINTF("Simple debug message");
    DEBUG_PRINTF("Debug with number: %d", 42);
    DEBUG_PRINTF("Debug with multiple values: %d, %s, %.2f", 100, "test", 3.14);
    PRINT_SEPARATOR();
    printf("\n");
    
    // 11. Platform-specific code
    PRINT_HEADER("Platform-Specific Code");
    printf("Running on: %s\n", PLATFORM);
    printf("Path separator: '%c'\n", PATH_SEPARATOR);
    
    #ifdef _WIN32
        printf("Windows-specific code would go here\n");
    #elif defined(__linux__)
        printf("Linux-specific code would go here\n");
    #elif defined(__APPLE__)
        printf("macOS-specific code would go here\n");
    #else
        printf("Generic Unix code would go here\n");
    #endif
    
    PRINT_SEPARATOR();
    printf("\n");
    
    printf("=== End of Preprocessor Directives Lesson ===\n");
    return 0;
}