/*
 * Advanced Debugging Techniques Lesson
 * Demonstrates debugging methodologies and common bug patterns
 * 
 * This lesson covers:
 * - Common bug patterns and how to identify them
 * - Debugging tools and techniques (GDB, Valgrind, static analysis)
 * - Memory debugging (leaks, corruption, bounds checking)
 * - Debugging strategies and methodologies
 * - Logging and assertion techniques
 * - Performance debugging and profiling
 * - Debugging in different environments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
    #include <crtdbg.h>
#else
    #include <unistd.h>
    #include <signal.h>
    #include <execinfo.h>
#endif

// Debug configuration
#define DEBUG_ENABLED 1
#define LOG_LEVEL_ERROR   0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_INFO    2
#define LOG_LEVEL_DEBUG   3

static int current_log_level = LOG_LEVEL_DEBUG;

// Debug macros
#define DEBUG_PRINT(level, fmt, ...) \
    do { \
        if (DEBUG_ENABLED && level <= current_log_level) { \
            debug_log(level, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
        } \
    } while(0)

#define ASSERT_MSG(condition, msg) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s at %s:%d in %s()\n", \
                    msg, __FILE__, __LINE__, __func__); \
            abort(); \
        } \
    } while(0)

#define CHECK_NULL(ptr, msg) \
    do { \
        if ((ptr) == NULL) { \
            DEBUG_PRINT(LOG_LEVEL_ERROR, "NULL pointer: %s", msg); \
        } \
    } while(0)

#define CHECK_BOUNDS(index, size, msg) \
    do { \
        if ((index) >= (size)) { \
            DEBUG_PRINT(LOG_LEVEL_ERROR, "Bounds check failed: %s (index=%zu, size=%zu)", \
                       msg, (size_t)(index), (size_t)(size)); \
        } \
    } while(0)

// Memory tracking structure
typedef struct memory_block {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    const char *func;
    struct memory_block *next;
} memory_block_t;

static memory_block_t *memory_list = NULL;
static size_t total_allocated = 0;
static size_t allocation_count = 0;

// Function prototypes
void demonstrate_common_bugs(void);
void demonstrate_memory_debugging(void);
void demonstrate_debugging_tools(void);
void demonstrate_logging_techniques(void);
void demonstrate_assertion_techniques(void);
void demonstrate_performance_debugging(void);
void demonstrate_debugging_strategies(void);

// Debugging utility functions
void debug_log(int level, const char *file, int line, const char *func, const char *fmt, ...);
void* debug_malloc(size_t size, const char *file, int line, const char *func);
void debug_free(void *ptr, const char *file, int line, const char *func);
void print_memory_leaks(void);
void print_stack_trace(void);

// Bug demonstration functions
void buffer_overflow_example(void);
void memory_leak_example(void);
void use_after_free_example(void);
void null_pointer_dereference_example(void);
void integer_overflow_example(void);
void uninitialized_variable_example(void);
void race_condition_example(void);

// Performance debugging functions
void performance_bottleneck_example(void);
void cache_miss_example(void);

// Debug memory allocation macros
#define DEBUG_MALLOC(size) debug_malloc(size, __FILE__, __LINE__, __func__)
#define DEBUG_FREE(ptr) debug_free(ptr, __FILE__, __LINE__, __func__)

int main() {
    printf("=== Advanced Debugging Techniques Lesson ===\n\n");
    
    printf("This lesson demonstrates advanced debugging techniques,\n");
    printf("common bug patterns, and debugging methodologies.\n\n");
    
    // Set up debugging environment
#ifdef _WIN32
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    
    // Demonstrate various debugging concepts
    demonstrate_logging_techniques();
    demonstrate_assertion_techniques();
    demonstrate_common_bugs();
    demonstrate_memory_debugging();
    demonstrate_debugging_tools();
    demonstrate_performance_debugging();
    demonstrate_debugging_strategies();
    
    // Check for memory leaks
    print_memory_leaks();
    
    printf("=== Advanced Debugging Lesson Complete ===\n");
    return 0;
}

void demonstrate_logging_techniques(void) {
    printf("1. LOGGING TECHNIQUES\n");
    printf("=====================\n\n");
    
    printf("Demonstrating different log levels:\n");
    
    DEBUG_PRINT(LOG_LEVEL_ERROR, "This is an error message");
    DEBUG_PRINT(LOG_LEVEL_WARNING, "This is a warning message");
    DEBUG_PRINT(LOG_LEVEL_INFO, "This is an info message");
    DEBUG_PRINT(LOG_LEVEL_DEBUG, "This is a debug message");
    
    printf("\nChanging log level to WARNING and above:\n");
    current_log_level = LOG_LEVEL_WARNING;
    
    DEBUG_PRINT(LOG_LEVEL_ERROR, "Error still shown");
    DEBUG_PRINT(LOG_LEVEL_WARNING, "Warning still shown");
    DEBUG_PRINT(LOG_LEVEL_INFO, "Info message filtered out");
    DEBUG_PRINT(LOG_LEVEL_DEBUG, "Debug message filtered out");
    
    // Reset log level
    current_log_level = LOG_LEVEL_DEBUG;
    
    printf("\nLogging best practices:\n");
    printf("- Use different log levels appropriately\n");
    printf("- Include context information (file, line, function)\n");
    printf("- Make log messages searchable and actionable\n");
    printf("- Consider performance impact of logging\n");
    printf("- Use structured logging for complex applications\n\n");
}

void demonstrate_assertion_techniques(void) {
    printf("2. ASSERTION TECHNIQUES\n");
    printf("=======================\n\n");
    
    printf("Demonstrating assertion usage:\n");
    
    // Valid assertions
    int array_size = 10;
    int index = 5;
    
    assert(array_size > 0);  // Standard assertion
    ASSERT_MSG(index < array_size, "Index within bounds");
    
    printf("Assertions passed successfully\n");
    
    // Demonstrate precondition checking
    char *test_string = "Hello, World!";
    CHECK_NULL(test_string, "test_string should not be NULL");
    
    printf("NULL check passed\n");
    
    // Demonstrate bounds checking
    CHECK_BOUNDS(index, array_size, "Array index bounds check");
    
    printf("Bounds check passed\n");
    
    printf("\nAssertion best practices:\n");
    printf("- Use assertions for debugging, not error handling\n");
    printf("- Check preconditions and postconditions\n");
    printf("- Include meaningful error messages\n");
    printf("- Disable assertions in release builds if needed\n");
    printf("- Use static assertions for compile-time checks\n\n");
}

void demonstrate_common_bugs(void) {
    printf("3. COMMON BUG PATTERNS\n");
    printf("======================\n\n");
    
    printf("This section demonstrates common bugs (safely):\n\n");
    
    printf("1. Buffer Overflow Prevention:\n");
    printf("------------------------------\n");
    buffer_overflow_example();
    
    printf("\n2. Memory Leak Detection:\n");
    printf("-------------------------\n");
    memory_leak_example();
    
    printf("\n3. Use After Free Prevention:\n");
    printf("-----------------------------\n");
    use_after_free_example();
    
    printf("\n4. Null Pointer Dereference Prevention:\n");
    printf("---------------------------------------\n");
    null_pointer_dereference_example();
    
    printf("\n5. Integer Overflow Detection:\n");
    printf("------------------------------\n");
    integer_overflow_example();
    
    printf("\n6. Uninitialized Variable Detection:\n");
    printf("------------------------------------\n");
    uninitialized_variable_example();
    
    printf("\n");
}

void demonstrate_memory_debugging(void) {
    printf("4. MEMORY DEBUGGING\n");
    printf("===================\n\n");
    
    printf("Demonstrating memory tracking:\n");
    
    // Allocate some memory with tracking
    void *ptr1 = DEBUG_MALLOC(100);
    void *ptr2 = DEBUG_MALLOC(200);
    void *ptr3 = DEBUG_MALLOC(50);
    
    printf("Allocated 3 blocks of memory\n");
    
    // Free some memory
    DEBUG_FREE(ptr2);
    printf("Freed middle block\n");
    
    // Intentionally leave ptr1 and ptr3 allocated to demonstrate leak detection
    
    printf("\nMemory debugging techniques:\n");
    printf("- Track all allocations and deallocations\n");
    printf("- Use tools like Valgrind, AddressSanitizer\n");
    printf("- Implement custom memory allocators for debugging\n");
    printf("- Use static analysis tools\n");
    printf("- Enable compiler warnings and sanitizers\n\n");
}

void demonstrate_debugging_tools(void) {
    printf("5. DEBUGGING TOOLS AND TECHNIQUES\n");
    printf("=================================\n\n");
    
    printf("Common debugging tools:\n");
    printf("----------------------\n");
    printf("1. GDB (GNU Debugger):\n");
    printf("   - Set breakpoints: break main\n");
    printf("   - Step through code: step, next, continue\n");
    printf("   - Examine variables: print var, info locals\n");
    printf("   - Examine memory: x/10x ptr\n");
    printf("   - Backtrace: bt, bt full\n\n");
    
    printf("2. Valgrind (Linux/macOS):\n");
    printf("   - Memory error detection: valgrind --tool=memcheck\n");
    printf("   - Memory leak detection: --leak-check=full\n");
    printf("   - Cache profiling: --tool=cachegrind\n");
    printf("   - Heap profiling: --tool=massif\n\n");
    
    printf("3. AddressSanitizer (ASan):\n");
    printf("   - Compile with: -fsanitize=address\n");
    printf("   - Detects buffer overflows, use-after-free\n");
    printf("   - Fast runtime checking\n\n");
    
    printf("4. Static Analysis Tools:\n");
    printf("   - Clang Static Analyzer\n");
    printf("   - Cppcheck\n");
    printf("   - PC-lint/PC-lint Plus\n");
    printf("   - Coverity\n\n");
    
    printf("5. Profiling Tools:\n");
    printf("   - gprof: Function-level profiling\n");
    printf("   - perf: Hardware counter analysis\n");
    printf("   - Intel VTune: Advanced profiling\n");
    printf("   - Instruments (macOS)\n\n");
    
    // Demonstrate stack trace (if available)
    printf("Stack trace example:\n");
    print_stack_trace();
    printf("\n");
}

void demonstrate_performance_debugging(void) {
    printf("6. PERFORMANCE DEBUGGING\n");
    printf("=========================\n\n");
    
    printf("Performance debugging example:\n");
    performance_bottleneck_example();
    
    printf("\nCache performance example:\n");
    cache_miss_example();
    
    printf("\nPerformance debugging techniques:\n");
    printf("- Profile before optimizing\n");
    printf("- Use appropriate profiling tools\n");
    printf("- Analyze algorithm complexity\n");
    printf("- Check memory access patterns\n");
    printf("- Monitor system resources\n");
    printf("- Use performance counters\n\n");
}

void demonstrate_debugging_strategies(void) {
    printf("7. DEBUGGING STRATEGIES\n");
    printf("=======================\n\n");
    
    printf("Systematic debugging approach:\n");
    printf("------------------------------\n");
    printf("1. Reproduce the bug consistently\n");
    printf("2. Isolate the problem area\n");
    printf("3. Form hypotheses about the cause\n");
    printf("4. Test hypotheses systematically\n");
    printf("5. Fix the root cause, not symptoms\n");
    printf("6. Verify the fix doesn't break anything else\n");
    printf("7. Add tests to prevent regression\n\n");
    
    printf("Debugging techniques:\n");
    printf("--------------------\n");
    printf("- Binary search debugging (divide and conquer)\n");
    printf("- Rubber duck debugging (explain to someone/something)\n");
    printf("- Print debugging (strategic printf statements)\n");
    printf("- Interactive debugging (GDB, IDE debuggers)\n");
    printf("- Static analysis (code review, tools)\n");
    printf("- Dynamic analysis (runtime tools)\n\n");
    
    printf("Common debugging mistakes:\n");
    printf("-------------------------\n");
    printf("- Fixing symptoms instead of root causes\n");
    printf("- Making multiple changes at once\n");
    printf("- Not testing the fix thoroughly\n");
    printf("- Ignoring compiler warnings\n");
    printf("- Not using version control effectively\n");
    printf("- Debugging optimized code\n\n");
}

// Utility function implementations
void debug_log(int level, const char *file, int line, const char *func, const char *fmt, ...) {
    const char *level_names[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
    
    // Get timestamp
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    
    // Print log header
    printf("[%s] %s %s:%d %s() - ", 
           timestamp, level_names[level], file, line, func);
    
    // Print formatted message
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    
    printf("\n");
}

void* debug_malloc(size_t size, const char *file, int line, const char *func) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        DEBUG_PRINT(LOG_LEVEL_ERROR, "malloc failed for size %zu", size);
        return NULL;
    }
    
    // Track allocation
    memory_block_t *block = malloc(sizeof(memory_block_t));
    if (block) {
        block->ptr = ptr;
        block->size = size;
        block->file = file;
        block->line = line;
        block->func = func;
        block->next = memory_list;
        memory_list = block;
        
        total_allocated += size;
        allocation_count++;
        
        DEBUG_PRINT(LOG_LEVEL_DEBUG, "Allocated %zu bytes at %p", size, ptr);
    }
    
    return ptr;
}

void debug_free(void *ptr, const char *file, int line, const char *func) {
    (void)file; (void)line; (void)func; // Suppress unused parameter warnings
    
    if (ptr == NULL) {
        DEBUG_PRINT(LOG_LEVEL_WARNING, "Attempting to free NULL pointer");
        return;
    }
    
    // Find and remove from tracking list
    memory_block_t **current = &memory_list;
    while (*current) {
        if ((*current)->ptr == ptr) {
            memory_block_t *to_remove = *current;
            *current = (*current)->next;
            
            total_allocated -= to_remove->size;
            allocation_count--;
            
            DEBUG_PRINT(LOG_LEVEL_DEBUG, "Freed %zu bytes at %p", to_remove->size, ptr);
            
            free(to_remove);
            free(ptr);
            return;
        }
        current = &(*current)->next;
    }
    
    DEBUG_PRINT(LOG_LEVEL_WARNING, "Attempting to free untracked pointer %p", ptr);
    free(ptr);  // Free anyway, but warn
}

void print_memory_leaks(void) {
    printf("Memory Leak Report:\n");
    printf("==================\n");
    
    if (memory_list == NULL) {
        printf("No memory leaks detected!\n");
        return;
    }
    
    printf("Memory leaks detected:\n");
    memory_block_t *current = memory_list;
    size_t leak_count = 0;
    size_t leak_size = 0;
    
    while (current) {
        printf("  Leak: %zu bytes at %p (allocated in %s:%d %s())\n",
               current->size, current->ptr, current->file, current->line, current->func);
        leak_count++;
        leak_size += current->size;
        current = current->next;
    }
    
    printf("Total leaks: %zu allocations, %zu bytes\n", leak_count, leak_size);
}

void print_stack_trace(void) {
#ifdef __GNUC__
    #ifndef _WIN32
        void *array[10];
        size_t size = backtrace(array, 10);
        char **strings = backtrace_symbols(array, size);
        
        if (strings != NULL) {
            printf("Stack trace (%zu frames):\n", size);
            for (size_t i = 0; i < size; i++) {
                printf("  %s\n", strings[i]);
            }
            free(strings);
        } else {
            printf("Stack trace not available\n");
        }
    #else
        printf("Stack trace not implemented on Windows\n");
    #endif
#else
    printf("Stack trace requires GCC\n");
#endif
}

// Bug demonstration functions (safe versions)
void buffer_overflow_example(void) {
    printf("Safe buffer handling example:\n");
    
    char buffer[10];
    const char *input = "This is a very long string that would overflow";
    
    // Unsafe: strcpy(buffer, input);  // Would cause buffer overflow
    
    // Safe version:
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination
    
    printf("Safely copied: '%.9s'\n", buffer);
    printf("Prevention: Use strncpy, snprintf, or bounds checking\n");
}

void memory_leak_example(void) {
    printf("Memory leak demonstration:\n");
    
    // Intentionally allocate without freeing to show leak detection
    void *leaked_ptr = DEBUG_MALLOC(42);
    printf("Allocated memory that won't be freed (intentional leak)\n");
    printf("Detection: Use memory tracking or tools like Valgrind\n");
    
    // This pointer will be reported as a leak
    (void)leaked_ptr;  // Suppress unused variable warning
}

void use_after_free_example(void) {
    printf("Use after free prevention:\n");
    
    char *ptr = DEBUG_MALLOC(20);
    strcpy(ptr, "Hello");
    printf("Before free: %s\n", ptr);
    
    DEBUG_FREE(ptr);
    ptr = NULL;  // Set to NULL after freeing
    
    // Safe check before use
    if (ptr != NULL) {
        printf("After free: %s\n", ptr);
    } else {
        printf("Pointer safely set to NULL after free\n");
    }
    
    printf("Prevention: Set pointers to NULL after freeing\n");
}

void null_pointer_dereference_example(void) {
    printf("Null pointer dereference prevention:\n");
    
    char *ptr = NULL;
    
    // Unsafe: printf("Value: %s\n", ptr);  // Would crash
    
    // Safe version:
    if (ptr != NULL) {
        printf("Value: %s\n", ptr);
    } else {
        printf("Pointer is NULL, cannot dereference\n");
    }
    
    printf("Prevention: Always check pointers before dereferencing\n");
}

void integer_overflow_example(void) {
    printf("Integer overflow detection:\n");
    
    int a = 2000000000;  // Close to INT_MAX
    int b = 2000000000;
    
    // Check for overflow before operation
    if (a > 0 && b > 0 && a > (INT_MAX - b)) {
        printf("Addition would overflow: %d + %d\n", a, b);
        printf("Using safer approach or larger type\n");
    } else {
        int result = a + b;
        printf("Safe addition: %d + %d = %d\n", a, b, result);
    }
    
    printf("Prevention: Check bounds before arithmetic operations\n");
}

void uninitialized_variable_example(void) {
    printf("Uninitialized variable prevention:\n");
    
    int initialized_var = 42;  // Good: explicitly initialized
    int uninitialized_var;     // Bad: not initialized
    
    // Initialize before use
    uninitialized_var = 0;
    
    printf("Initialized variable: %d\n", initialized_var);
    printf("Now initialized variable: %d\n", uninitialized_var);
    printf("Prevention: Initialize all variables at declaration\n");
}

void race_condition_example(void) {
    printf("Race condition awareness:\n");
    printf("In multi-threaded programs, shared data access must be synchronized\n");
    printf("Use mutexes, atomic operations, or other synchronization primitives\n");
    printf("Tools: ThreadSanitizer, Helgrind can detect race conditions\n");
}

void performance_bottleneck_example(void) {
    const int size = 100000;
    clock_t start, end;
    
    // Inefficient algorithm
    start = clock();
    volatile long sum1 = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 100; j++) {
            sum1 += i * j;
        }
    }
    end = clock();
    double slow_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // More efficient algorithm
    start = clock();
    volatile long sum2 = 0;
    for (int i = 0; i < size; i++) {
        long temp = i * (100 * 99 / 2);  // Mathematical optimization
        sum2 += temp;
    }
    end = clock();
    double fast_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Inefficient algorithm: %.6f seconds\n", slow_time);
    printf("Optimized algorithm:   %.6f seconds\n", fast_time);
    if (fast_time > 0) {
        printf("Speedup: %.2fx\n", slow_time / fast_time);
    }
}

void cache_miss_example(void) {
    const int size = 500;  // Reduced size to prevent stack overflow
    int **matrix = malloc(size * sizeof(int*));
    if (!matrix) {
        printf("Memory allocation failed for matrix\n");
        return;
    }
    
    for (int i = 0; i < size; i++) {
        matrix[i] = malloc(size * sizeof(int));
        if (!matrix[i]) {
            printf("Memory allocation failed for matrix row %d\n", i);
            // Clean up previously allocated rows
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return;
        }
    }
    
    clock_t start, end;
    
    // Initialize matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = i * size + j;
        }
    }
    
    // Cache-friendly access (row-major)
    start = clock();
    volatile long sum1 = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum1 += matrix[i][j];
        }
    }
    end = clock();
    double row_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Cache-unfriendly access (column-major)
    start = clock();
    volatile long sum2 = 0;
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            sum2 += matrix[i][j];
        }
    }
    end = clock();
    double col_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Row-major access (cache-friendly):   %.6f seconds\n", row_time);
    printf("Column-major access (cache-unfriendly): %.6f seconds\n", col_time);
    if (row_time > 0) {
        printf("Performance difference: %.2fx\n", col_time / row_time);
    }
    
    // Clean up allocated memory
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}