#include <stdio.h>

// Global variables (external linkage by default)
int global_var = 100;
static int static_global = 200;  // Internal linkage (file scope only)

// External declaration (defined in another file, if it existed)
// extern int external_var;

// Function prototypes
void demonstrate_local_scope(void);
void demonstrate_static_local(void);
void demonstrate_register_storage(void);
void demonstrate_global_access(void);
void demonstrate_variable_shadowing(void);
void recursive_function(int n);

int main() {
    printf("=== Scope and Storage Classes in C ===\n\n");
    
    // 1. Global Variables
    printf("1. Global Variables:\n");
    printf("   global_var (accessible everywhere): %d\n", global_var);
    printf("   static_global (file scope only): %d\n", static_global);
    
    // Modify global variable
    global_var = 150;
    printf("   Modified global_var: %d\n\n", global_var);
    
    // 2. Local Scope Demonstration
    printf("2. Local Scope:\n");
    demonstrate_local_scope();
    printf("\n");
    
    // 3. Static Local Variables
    printf("3. Static Local Variables:\n");
    printf("   Calling demonstrate_static_local() multiple times:\n");
    for (int i = 0; i < 5; i++) {
        demonstrate_static_local();
    }
    printf("\n");
    
    // 4. Register Storage Class
    printf("4. Register Storage Class:\n");
    demonstrate_register_storage();
    printf("\n");
    
    // 5. Global Variable Access from Functions
    printf("5. Global Variable Access:\n");
    demonstrate_global_access();
    printf("\n");
    
    // 6. Variable Shadowing
    printf("6. Variable Shadowing:\n");
    demonstrate_variable_shadowing();
    printf("\n");
    
    // 7. Automatic Variables in Blocks
    printf("7. Block Scope (Automatic Variables):\n");
    {
        int block_var = 999;  // Only exists in this block
        printf("   Inside block: block_var = %d\n", block_var);
        
        {
            int inner_block_var = 777;  // Nested block scope
            printf("   Inside inner block: inner_block_var = %d\n", inner_block_var);
            printf("   Can still access block_var: %d\n", block_var);
        }
        // inner_block_var is no longer accessible here
        printf("   Back in outer block: block_var = %d\n", block_var);
    }
    // block_var is no longer accessible here
    printf("   Outside block: block_var is no longer accessible\n\n");
    
    // 8. Function Parameters Scope
    printf("8. Function Parameters and Recursion:\n");
    printf("   Demonstrating parameter scope in recursion:\n");
    recursive_function(3);
    printf("\n");
    
    // 9. Storage Duration Examples
    printf("9. Storage Duration Summary:\n");
    printf("   - Automatic: Created when entering scope, destroyed when leaving\n");
    printf("   - Static: Created once, persists for program lifetime\n");
    printf("   - Dynamic: Manually managed with malloc/free\n");
    printf("   - Thread: One instance per thread (C11 feature)\n\n");
    
    // 10. Linkage Examples
    printf("10. Linkage Types:\n");
    printf("   - External linkage: Accessible from other files (global variables)\n");
    printf("   - Internal linkage: Accessible only within current file (static global)\n");
    printf("   - No linkage: Local variables, function parameters\n");
    
    printf("\n=== End of Scope and Storage Classes Lesson ===\n");
    return 0;
}

void demonstrate_local_scope(void) {
    int local_var = 42;  // Automatic storage class
    printf("   Inside function: local_var = %d\n", local_var);
    
    // Local variable shadows global variable
    int local_global_var = 999;  // This shadows the global global_var
    printf("   Local variable (shadows global): %d\n", local_global_var);
    // In C, once a global variable is shadowed by a local variable,
    // the global variable becomes inaccessible in that scope
    
    local_var = 84;
    printf("   Modified local_var: %d\n", local_var);
    // local_var will be destroyed when function exits
}

void demonstrate_static_local(void) {
    static int static_counter = 0;  // Initialized only once
    int auto_counter = 0;           // Initialized every time function is called
    
    static_counter++;
    auto_counter++;
    
    printf("   static_counter: %d, auto_counter: %d\n", static_counter, auto_counter);
}

void demonstrate_register_storage(void) {
    register int fast_var = 100;  // Hint to compiler to use CPU register
    
    printf("   register variable: %d\n", fast_var);
    // Note: Cannot take address of register variable
    // printf("Address: %p\n", &fast_var);  // This would cause an error
    
    // Register is just a hint; compiler may ignore it
    for (register int i = 0; i < 5; i++) {
        printf("   Loop iteration: %d\n", i);
    }
}

void demonstrate_global_access(void) {
    printf("   Accessing global_var from function: %d\n", global_var);
    printf("   Accessing static_global from function: %d\n", static_global);
    
    // Modify global variables
    global_var += 50;
    static_global += 25;
    
    printf("   After modification - global_var: %d, static_global: %d\n", 
           global_var, static_global);
}

void demonstrate_variable_shadowing(void) {
    int x = 10;  // Local variable
    printf("   Outer scope x: %d\n", x);
    
    {
        int x = 20;  // This shadows the outer x
        printf("   Inner scope x (shadows outer): %d\n", x);
        
        {
            int x = 30;  // This shadows both outer x variables
            printf("   Innermost scope x: %d\n", x);
        }
        
        printf("   Back to inner scope x: %d\n", x);
    }
    
    printf("   Back to outer scope x: %d\n", x);
    
    // Demonstrate shadowing with global variable
    int global_var = 555;  // Shadows the global global_var
    printf("   Local global_var (shadows global): %d\n", global_var);
}

void recursive_function(int n) {
    printf("   Entering recursive_function with n = %d\n", n);
    
    // Each recursive call has its own copy of parameter 'n'
    if (n > 0) {
        int local_var = n * 10;  // Each call has its own local_var
        printf("   Local variable in this call: %d\n", local_var);
        recursive_function(n - 1);
        printf("   Returning from call with n = %d, local_var = %d\n", n, local_var);
    } else {
        printf("   Base case reached\n");
    }
}