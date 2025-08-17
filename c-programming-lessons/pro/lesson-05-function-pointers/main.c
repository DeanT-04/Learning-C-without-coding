#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Function prototypes for basic operations
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);

// Function prototypes for array operations
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);

// Function prototypes for comparison functions
int ascending_compare(const void *a, const void *b);
int descending_compare(const void *a, const void *b);

// Function prototypes for callback demonstrations
void process_array(int arr[], int size, void (*callback)(int));
void print_element(int element);
void square_element(int element);

// Function prototypes for event handling simulation
typedef void (*EventHandler)(const char* event_data);
void button_click_handler(const char* data);
void mouse_move_handler(const char* data);
void key_press_handler(const char* data);

// Function prototypes for strategy pattern
typedef double (*DiscountStrategy)(double price);
double no_discount(double price);
double student_discount(double price);
double senior_discount(double price);
double member_discount(double price);

// Function prototypes for demonstrations
void demonstrate_basic_function_pointers(void);
void demonstrate_function_pointer_arrays(void);
void demonstrate_callback_functions(void);
void demonstrate_qsort_with_function_pointers(void);
void demonstrate_event_handling(void);
void demonstrate_strategy_pattern(void);
void demonstrate_function_pointer_as_parameter(void);
void demonstrate_returning_function_pointers(void);

int main(void) {
    printf("=== Function Pointers in C ===\n\n");
    
    demonstrate_basic_function_pointers();
    demonstrate_function_pointer_arrays();
    demonstrate_callback_functions();
    demonstrate_qsort_with_function_pointers();
    demonstrate_event_handling();
    demonstrate_strategy_pattern();
    demonstrate_function_pointer_as_parameter();
    demonstrate_returning_function_pointers();
    
    return 0;
}

// Basic arithmetic functions
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0;
    }
    return a / b;
}

void demonstrate_basic_function_pointers(void) {
    printf("1. Basic Function Pointers:\n");
    printf("---------------------------\n");
    
    // Declare function pointer
    int (*operation)(int, int);
    
    // Point to add function
    operation = add;
    printf("Using function pointer to add: 10 + 5 = %d\n", operation(10, 5));
    
    // Point to subtract function
    operation = subtract;
    printf("Using function pointer to subtract: 10 - 5 = %d\n", operation(10, 5));
    
    // Alternative syntax for calling function pointer
    operation = multiply;
    printf("Using (*operation) syntax: 10 * 5 = %d\n", (*operation)(10, 5));
    
    // Point to divide function
    operation = &divide;  // & is optional but explicit
    printf("Using function pointer to divide: 10 / 5 = %d\n", operation(10, 5));
    
    // Show function addresses
    printf("\nFunction addresses:\n");
    printf("add function address: %p\n", (void*)(uintptr_t)add);
    printf("subtract function address: %p\n", (void*)(uintptr_t)subtract);
    printf("multiply function address: %p\n", (void*)(uintptr_t)multiply);
    printf("divide function address: %p\n", (void*)(uintptr_t)divide);
    
    printf("\n");
}

void demonstrate_function_pointer_arrays(void) {
    printf("2. Function Pointer Arrays:\n");
    printf("---------------------------\n");
    
    // Array of function pointers
    int (*operations[])(int, int) = {add, subtract, multiply, divide};
    const char* operation_names[] = {"Addition", "Subtraction", "Multiplication", "Division"};
    
    int a = 20, b = 4;
    
    printf("Performing operations on %d and %d:\n", a, b);
    for (int i = 0; i < 4; i++) {
        printf("%s: %d\n", operation_names[i], operations[i](a, b));
    }
    
    // Calculator simulation using function pointer array
    printf("\nSimple Calculator Menu:\n");
    printf("0: Addition, 1: Subtraction, 2: Multiplication, 3: Division\n");
    
    int choice = 2;  // Simulate user choosing multiplication
    printf("Selected operation %d: %s\n", choice, operation_names[choice]);
    printf("Result: %d %s %d = %d\n", a, 
           (choice == 0) ? "+" : (choice == 1) ? "-" : (choice == 2) ? "*" : "/",
           b, operations[choice](a, b));
    
    printf("\n");
}

void demonstrate_callback_functions(void) {
    printf("3. Callback Functions:\n");
    printf("----------------------\n");
    
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("Processing array with print callback:\n");
    process_array(numbers, size, print_element);
    
    printf("Processing array with square callback:\n");
    process_array(numbers, size, square_element);
    
    printf("\n");
}

void process_array(int arr[], int size, void (*callback)(int)) {
    printf("Processing: ");
    for (int i = 0; i < size; i++) {
        callback(arr[i]);
    }
    printf("\n");
}

void print_element(int element) {
    printf("%d ", element);
}

void square_element(int element) {
    printf("%d ", element * element);
}

// Sorting functions
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void demonstrate_qsort_with_function_pointers(void) {
    printf("4. Using qsort with Function Pointers:\n");
    printf("--------------------------------------\n");
    
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // Sort in ascending order
    int ascending_copy[7];
    memcpy(ascending_copy, numbers, sizeof(numbers));
    qsort(ascending_copy, size, sizeof(int), ascending_compare);
    
    printf("Sorted ascending: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", ascending_copy[i]);
    }
    printf("\n");
    
    // Sort in descending order
    int descending_copy[7];
    memcpy(descending_copy, numbers, sizeof(numbers));
    qsort(descending_copy, size, sizeof(int), descending_compare);
    
    printf("Sorted descending: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", descending_copy[i]);
    }
    printf("\n");
    
    // Demonstrate custom sorting algorithms using function pointers
    printf("\nCustom sorting algorithms:\n");
    
    void (*sort_algorithms[])(int[], int) = {bubble_sort, selection_sort, insertion_sort};
    const char* algorithm_names[] = {"Bubble Sort", "Selection Sort", "Insertion Sort"};
    
    for (int i = 0; i < 3; i++) {
        int test_array[7];
        memcpy(test_array, numbers, sizeof(numbers));
        
        printf("%s: ", algorithm_names[i]);
        sort_algorithms[i](test_array, size);
        
        for (int j = 0; j < size; j++) {
            printf("%d ", test_array[j]);
        }
        printf("\n");
    }
    
    printf("\n");
}

int ascending_compare(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int descending_compare(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    
    if (int_a > int_b) return -1;
    if (int_a < int_b) return 1;
    return 0;
}

void demonstrate_event_handling(void) {
    printf("5. Event Handling Simulation:\n");
    printf("------------------------------\n");
    
    // Array of event handlers
    EventHandler handlers[] = {button_click_handler, mouse_move_handler, key_press_handler};
    const char* event_names[] = {"Button Click", "Mouse Move", "Key Press"};
    const char* event_data[] = {"Button1", "x:100,y:200", "Key:Enter"};
    
    printf("Simulating event handling:\n");
    for (int i = 0; i < 3; i++) {
        printf("Event: %s, Data: %s\n", event_names[i], event_data[i]);
        handlers[i](event_data[i]);
        printf("\n");
    }
}

void button_click_handler(const char* data) {
    printf("  Button click handler called with data: %s\n", data);
    printf("  Processing button click event...\n");
}

void mouse_move_handler(const char* data) {
    printf("  Mouse move handler called with data: %s\n", data);
    printf("  Updating cursor position...\n");
}

void key_press_handler(const char* data) {
    printf("  Key press handler called with data: %s\n", data);
    printf("  Processing keyboard input...\n");
}

void demonstrate_strategy_pattern(void) {
    printf("6. Strategy Pattern with Function Pointers:\n");
    printf("-------------------------------------------\n");
    
    double price = 100.0;
    
    // Array of discount strategies
    DiscountStrategy strategies[] = {no_discount, student_discount, senior_discount, member_discount};
    const char* strategy_names[] = {"No Discount", "Student Discount", "Senior Discount", "Member Discount"};
    
    printf("Original price: $%.2f\n", price);
    printf("Applying different discount strategies:\n");
    
    for (int i = 0; i < 4; i++) {
        double discounted_price = strategies[i](price);
        printf("  %s: $%.2f (saved: $%.2f)\n", 
               strategy_names[i], discounted_price, price - discounted_price);
    }
    
    printf("\n");
}

double no_discount(double price) {
    return price;
}

double student_discount(double price) {
    return price * 0.9;  // 10% discount
}

double senior_discount(double price) {
    return price * 0.85;  // 15% discount
}

double member_discount(double price) {
    return price * 0.8;  // 20% discount
}

// Function that takes function pointer as parameter
void execute_operation(int a, int b, int (*op)(int, int), const char* op_name) {
    printf("Executing %s: %d and %d = %d\n", op_name, a, b, op(a, b));
}

void demonstrate_function_pointer_as_parameter(void) {
    printf("7. Function Pointers as Parameters:\n");
    printf("-----------------------------------\n");
    
    int x = 15, y = 3;
    
    printf("Passing different operations as parameters:\n");
    execute_operation(x, y, add, "addition");
    execute_operation(x, y, subtract, "subtraction");
    execute_operation(x, y, multiply, "multiplication");
    execute_operation(x, y, divide, "division");
    
    printf("\n");
}

// Function that returns function pointer
int (*get_operation(char op))(int, int) {
    switch (op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide;
        default: return NULL;
    }
}

void demonstrate_returning_function_pointers(void) {
    printf("8. Returning Function Pointers:\n");
    printf("-------------------------------\n");
    
    char operators[] = {'+', '-', '*', '/'};
    int a = 12, b = 3;
    
    printf("Getting operations dynamically:\n");
    for (int i = 0; i < 4; i++) {
        int (*operation)(int, int) = get_operation(operators[i]);
        if (operation != NULL) {
            printf("%d %c %d = %d\n", a, operators[i], b, operation(a, b));
        } else {
            printf("Unknown operator: %c\n", operators[i]);
        }
    }
    
    // Demonstrate with invalid operator
    printf("\nTesting with invalid operator:\n");
    int (*invalid_op)(int, int) = get_operation('%');
    if (invalid_op == NULL) {
        printf("Invalid operator '%%' - function pointer is NULL\n");
    }
    
    printf("\nFunction Pointer Syntax Summary:\n");
    printf("--------------------------------\n");
    printf("Declaration: return_type (*pointer_name)(parameter_types)\n");
    printf("Assignment:  pointer_name = function_name\n");
    printf("Call:        pointer_name(arguments) or (*pointer_name)(arguments)\n");
    printf("Array:       return_type (*array_name[])(parameter_types)\n");
    printf("Parameter:   void func(return_type (*fp)(parameter_types))\n");
    printf("Return:      return_type (*func())(parameter_types)\n");
}