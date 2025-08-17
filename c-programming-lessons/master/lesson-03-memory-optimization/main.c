/*
 * Memory Optimization Lesson
 * Demonstrates memory-efficient programming techniques and performance optimization
 * 
 * This lesson covers:
 * - Memory alignment and padding
 * - Cache-friendly data structures and algorithms
 * - Memory pool allocation
 * - Stack vs heap optimization
 * - Memory access patterns and locality
 * - Structure packing and optimization
 * - Performance measurement and profiling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdalign.h>

#ifdef _WIN32
    #include <windows.h>
    #define CACHE_LINE_SIZE 64
#else
    #include <sys/time.h>
    #include <unistd.h>
    #define CACHE_LINE_SIZE 64
#endif

// Constants for demonstrations
#define ARRAY_SIZE 1000000
#define ITERATIONS 100
#define POOL_SIZE 1024
#define BLOCK_SIZE 64

// Structure alignment demonstrations
struct unaligned_struct {
    char a;      // 1 byte
    int b;       // 4 bytes
    char c;      // 1 byte
    double d;    // 8 bytes
    char e;      // 1 byte
};

struct aligned_struct {
    double d;    // 8 bytes (largest alignment requirement first)
    int b;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte
    char e;      // 1 byte
    // 3 bytes padding to align to 8-byte boundary
};

// Packed structure (no padding)
#pragma pack(push, 1)
struct packed_struct {
    char a;      // 1 byte
    int b;       // 4 bytes
    char c;      // 1 byte
    double d;    // 8 bytes
    char e;      // 1 byte
};
#pragma pack(pop)

// Cache-aligned structure
struct cache_aligned_struct {
    alignas(CACHE_LINE_SIZE) int data[16];
};

// Memory pool structure
typedef struct memory_pool {
    char *pool;
    size_t size;
    size_t used;
    size_t block_size;
} memory_pool_t;

// Function prototypes
void demonstrate_structure_alignment(void);
void demonstrate_cache_optimization(void);
void demonstrate_memory_pools(void);
void demonstrate_stack_vs_heap(void);
void demonstrate_memory_access_patterns(void);
void demonstrate_data_structure_optimization(void);
void demonstrate_compiler_optimizations(void);

// Utility functions
double get_time_diff(clock_t start, clock_t end);
void print_memory_usage(void);
memory_pool_t* create_memory_pool(size_t pool_size, size_t block_size);
void* pool_alloc(memory_pool_t *pool);
void destroy_memory_pool(memory_pool_t *pool);

// Cache performance test functions
void test_sequential_access(int *array, int size);
void test_random_access(int *array, int size);
void test_strided_access(int *array, int size, int stride);

int main() {
    printf("=== Memory Optimization Lesson ===\n\n");
    
    printf("This lesson demonstrates memory optimization techniques\n");
    printf("for high-performance C programming.\n\n");
    
    // Demonstrate various memory optimization concepts
    demonstrate_structure_alignment();
    demonstrate_cache_optimization();
    demonstrate_memory_pools();
    demonstrate_stack_vs_heap();
    demonstrate_memory_access_patterns();
    demonstrate_data_structure_optimization();
    demonstrate_compiler_optimizations();
    
    printf("=== Memory Optimization Lesson Complete ===\n");
    return 0;
}

void demonstrate_structure_alignment(void) {
    printf("1. STRUCTURE ALIGNMENT AND PADDING\n");
    printf("==================================\n\n");
    
    printf("Structure sizes and alignment:\n");
    printf("Unaligned struct: %zu bytes\n", sizeof(struct unaligned_struct));
    printf("Aligned struct:   %zu bytes\n", sizeof(struct aligned_struct));
    printf("Packed struct:    %zu bytes\n", sizeof(struct packed_struct));
    printf("Cache-aligned:    %zu bytes\n", sizeof(struct cache_aligned_struct));
    
    printf("\nMemory layout analysis:\n");
    
    struct unaligned_struct unaligned;
    printf("Unaligned struct member offsets:\n");
    printf("  a (char):   offset %zu\n", offsetof(struct unaligned_struct, a));
    printf("  b (int):    offset %zu\n", offsetof(struct unaligned_struct, b));
    printf("  c (char):   offset %zu\n", offsetof(struct unaligned_struct, c));
    printf("  d (double): offset %zu\n", offsetof(struct unaligned_struct, d));
    printf("  e (char):   offset %zu\n", offsetof(struct unaligned_struct, e));
    
    struct aligned_struct aligned;
    printf("\nAligned struct member offsets:\n");
    printf("  d (double): offset %zu\n", offsetof(struct aligned_struct, d));
    printf("  b (int):    offset %zu\n", offsetof(struct aligned_struct, b));
    printf("  a (char):   offset %zu\n", offsetof(struct aligned_struct, a));
    printf("  c (char):   offset %zu\n", offsetof(struct aligned_struct, c));
    printf("  e (char):   offset %zu\n", offsetof(struct aligned_struct, e));
    
    // Demonstrate memory waste
    size_t unaligned_waste = sizeof(struct unaligned_struct) - 
                            (sizeof(char) * 3 + sizeof(int) + sizeof(double));
    size_t aligned_waste = sizeof(struct aligned_struct) - 
                          (sizeof(char) * 3 + sizeof(int) + sizeof(double));
    
    printf("\nPadding overhead:\n");
    printf("  Unaligned struct: %zu bytes wasted\n", unaligned_waste);
    printf("  Aligned struct:   %zu bytes wasted\n", aligned_waste);
    printf("  Packed struct:    0 bytes wasted (but may be slower)\n");
    
    // Performance comparison
    const int test_size = 100000;
    struct unaligned_struct *unaligned_array = malloc(test_size * sizeof(struct unaligned_struct));
    struct aligned_struct *aligned_array = malloc(test_size * sizeof(struct aligned_struct));
    
    if (unaligned_array && aligned_array) {
        clock_t start, end;
        
        // Test unaligned access
        start = clock();
        for (int i = 0; i < test_size; i++) {
            unaligned_array[i].a = 1;
            unaligned_array[i].b = i;
            unaligned_array[i].c = 2;
            unaligned_array[i].d = i * 1.5;
            unaligned_array[i].e = 3;
        }
        end = clock();
        double unaligned_time = get_time_diff(start, end);
        
        // Test aligned access
        start = clock();
        for (int i = 0; i < test_size; i++) {
            aligned_array[i].d = i * 1.5;
            aligned_array[i].b = i;
            aligned_array[i].a = 1;
            aligned_array[i].c = 2;
            aligned_array[i].e = 3;
        }
        end = clock();
        double aligned_time = get_time_diff(start, end);
        
        printf("\nPerformance comparison (%d iterations):\n", test_size);
        printf("  Unaligned struct: %.6f seconds\n", unaligned_time);
        printf("  Aligned struct:   %.6f seconds\n", aligned_time);
        printf("  Speedup:          %.2fx\n", unaligned_time / aligned_time);
        
        free(unaligned_array);
        free(aligned_array);
    }
    
    printf("\n");
}

void demonstrate_cache_optimization(void) {
    printf("2. CACHE OPTIMIZATION\n");
    printf("=====================\n\n");
    
    printf("Cache line size: %d bytes\n", CACHE_LINE_SIZE);
    printf("Testing different memory access patterns...\n\n");
    
    // Allocate test array
    int *test_array = malloc(ARRAY_SIZE * sizeof(int));
    if (!test_array) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Initialize array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        test_array[i] = i;
    }
    
    clock_t start, end;
    
    // Sequential access (cache-friendly)
    printf("Sequential access test:\n");
    start = clock();
    test_sequential_access(test_array, ARRAY_SIZE);
    end = clock();
    double sequential_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds\n", sequential_time);
    
    // Random access (cache-unfriendly)
    printf("\nRandom access test:\n");
    start = clock();
    test_random_access(test_array, ARRAY_SIZE);
    end = clock();
    double random_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds\n", random_time);
    
    // Strided access with different strides
    printf("\nStrided access tests:\n");
    int strides[] = {1, 2, 4, 8, 16, 32, 64};
    int num_strides = sizeof(strides) / sizeof(strides[0]);
    
    for (int i = 0; i < num_strides; i++) {
        start = clock();
        test_strided_access(test_array, ARRAY_SIZE, strides[i]);
        end = clock();
        double strided_time = get_time_diff(start, end);
        printf("  Stride %2d: %.6f seconds\n", strides[i], strided_time);
    }
    
    printf("\nCache performance analysis:\n");
    printf("  Sequential vs Random: %.2fx faster\n", random_time / sequential_time);
    printf("  Cache line utilization is crucial for performance\n");
    
    free(test_array);
    printf("\n");
}

void demonstrate_memory_pools(void) {
    printf("3. MEMORY POOL ALLOCATION\n");
    printf("=========================\n\n");
    
    printf("Comparing malloc vs memory pool allocation...\n");
    
    const int num_allocations = 10000;
    clock_t start, end;
    
    // Test standard malloc/free
    printf("\nStandard malloc/free test:\n");
    start = clock();
    void **ptrs = malloc(num_allocations * sizeof(void*));
    for (int i = 0; i < num_allocations; i++) {
        ptrs[i] = malloc(BLOCK_SIZE);
        if (ptrs[i]) {
            memset(ptrs[i], i % 256, BLOCK_SIZE);
        }
    }
    for (int i = 0; i < num_allocations; i++) {
        free(ptrs[i]);
    }
    free(ptrs);
    end = clock();
    double malloc_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds\n", malloc_time);
    
    // Test memory pool allocation
    printf("\nMemory pool allocation test:\n");
    start = clock();
    memory_pool_t *pool = create_memory_pool(POOL_SIZE * BLOCK_SIZE, BLOCK_SIZE);
    if (pool) {
        void **pool_ptrs = malloc(num_allocations * sizeof(void*));
        int successful_allocs = 0;
        
        for (int i = 0; i < num_allocations && i < POOL_SIZE; i++) {
            pool_ptrs[i] = pool_alloc(pool);
            if (pool_ptrs[i]) {
                memset(pool_ptrs[i], i % 256, BLOCK_SIZE);
                successful_allocs++;
            }
        }
        
        destroy_memory_pool(pool);
        free(pool_ptrs);
        
        printf("  Successful allocations: %d/%d\n", successful_allocs, num_allocations);
    }
    end = clock();
    double pool_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds\n", pool_time);
    
    printf("\nMemory pool advantages:\n");
    printf("  - Reduced fragmentation\n");
    printf("  - Faster allocation/deallocation\n");
    printf("  - Better cache locality\n");
    printf("  - Predictable memory usage\n");
    
    if (pool_time > 0) {
        printf("  Speedup: %.2fx faster\n", malloc_time / pool_time);
    }
    
    printf("\n");
}

void demonstrate_stack_vs_heap(void) {
    printf("4. STACK VS HEAP OPTIMIZATION\n");
    printf("==============================\n\n");
    
    const int test_size = 100000;
    clock_t start, end;
    
    // Stack allocation test (using alloca or VLA)
    printf("Stack allocation test (Variable Length Arrays):\n");
    start = clock();
    for (int i = 0; i < test_size; i++) {
        int stack_array[100];  // Stack allocated
        for (int j = 0; j < 100; j++) {
            stack_array[j] = i + j;
        }
        // Array automatically deallocated when leaving scope
    }
    end = clock();
    double stack_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds\n", stack_time);
    
    // Heap allocation test
    printf("\nHeap allocation test:\n");
    start = clock();
    for (int i = 0; i < test_size; i++) {
        int *heap_array = malloc(100 * sizeof(int));
        if (heap_array) {
            for (int j = 0; j < 100; j++) {
                heap_array[j] = i + j;
            }
            free(heap_array);
        }
    }
    end = clock();
    double heap_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds\n", heap_time);
    
    printf("\nStack vs Heap comparison:\n");
    printf("  Stack allocation: %.2fx faster\n", heap_time / stack_time);
    printf("  Stack advantages: No allocation overhead, automatic cleanup\n");
    printf("  Stack limitations: Limited size, scope-bound lifetime\n");
    printf("  Heap advantages: Large allocations, flexible lifetime\n");
    printf("  Heap disadvantages: Allocation overhead, manual management\n");
    
    printf("\n");
}

void demonstrate_memory_access_patterns(void) {
    printf("5. MEMORY ACCESS PATTERNS\n");
    printf("=========================\n\n");
    
    const int matrix_size = 512;
    int **matrix = malloc(matrix_size * sizeof(int*));
    for (int i = 0; i < matrix_size; i++) {
        matrix[i] = malloc(matrix_size * sizeof(int));
        for (int j = 0; j < matrix_size; j++) {
            matrix[i][j] = i * matrix_size + j;
        }
    }
    
    clock_t start, end;
    long sum;
    
    // Row-major access (cache-friendly)
    printf("Row-major access (cache-friendly):\n");
    start = clock();
    sum = 0;
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            sum += matrix[i][j];
        }
    }
    end = clock();
    double row_major_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds, Sum: %ld\n", row_major_time, sum);
    
    // Column-major access (cache-unfriendly)
    printf("\nColumn-major access (cache-unfriendly):\n");
    start = clock();
    sum = 0;
    for (int j = 0; j < matrix_size; j++) {
        for (int i = 0; i < matrix_size; i++) {
            sum += matrix[i][j];
        }
    }
    end = clock();
    double col_major_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds, Sum: %ld\n", col_major_time, sum);
    
    printf("\nAccess pattern impact:\n");
    printf("  Column-major is %.2fx slower than row-major\n", col_major_time / row_major_time);
    printf("  Reason: Poor cache locality in column-major access\n");
    
    // Cleanup
    for (int i = 0; i < matrix_size; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    printf("\n");
}

void demonstrate_data_structure_optimization(void) {
    printf("6. DATA STRUCTURE OPTIMIZATION\n");
    printf("===============================\n\n");
    
    // Array of Structures vs Structure of Arrays
    const int num_elements = 100000;
    
    // Array of Structures (AoS)
    typedef struct {
        float x, y, z;
        int id;
    } point_aos_t;
    
    point_aos_t *aos = malloc(num_elements * sizeof(point_aos_t));
    
    // Structure of Arrays (SoA)
    typedef struct {
        float *x, *y, *z;
        int *id;
    } points_soa_t;
    
    points_soa_t soa;
    soa.x = malloc(num_elements * sizeof(float));
    soa.y = malloc(num_elements * sizeof(float));
    soa.z = malloc(num_elements * sizeof(float));
    soa.id = malloc(num_elements * sizeof(int));
    
    if (!aos || !soa.x || !soa.y || !soa.z || !soa.id) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Initialize data
    for (int i = 0; i < num_elements; i++) {
        aos[i].x = soa.x[i] = i * 1.0f;
        aos[i].y = soa.y[i] = i * 2.0f;
        aos[i].z = soa.z[i] = i * 3.0f;
        aos[i].id = soa.id[i] = i;
    }
    
    clock_t start, end;
    float sum;
    
    // Test AoS performance (accessing only x coordinates)
    printf("Array of Structures (AoS) - accessing x coordinates:\n");
    start = clock();
    sum = 0.0f;
    for (int i = 0; i < num_elements; i++) {
        sum += aos[i].x;
    }
    end = clock();
    double aos_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds, Sum: %.2f\n", aos_time, sum);
    
    // Test SoA performance (accessing only x coordinates)
    printf("\nStructure of Arrays (SoA) - accessing x coordinates:\n");
    start = clock();
    sum = 0.0f;
    for (int i = 0; i < num_elements; i++) {
        sum += soa.x[i];
    }
    end = clock();
    double soa_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds, Sum: %.2f\n", soa_time, sum);
    
    printf("\nData structure comparison:\n");
    printf("  SoA is %.2fx faster for selective field access\n", aos_time / soa_time);
    printf("  AoS: Better for accessing all fields of an element\n");
    printf("  SoA: Better for accessing single fields across elements\n");
    printf("  SoA: More cache-friendly for vectorization\n");
    
    // Cleanup
    free(aos);
    free(soa.x);
    free(soa.y);
    free(soa.z);
    free(soa.id);
    
    printf("\n");
}

void demonstrate_compiler_optimizations(void) {
    printf("7. COMPILER OPTIMIZATION TECHNIQUES\n");
    printf("===================================\n\n");
    
    printf("Compiler optimization flags and their effects:\n");
    printf("  -O0: No optimization (debug builds)\n");
    printf("  -O1: Basic optimizations\n");
    printf("  -O2: Standard optimizations (recommended for release)\n");
    printf("  -O3: Aggressive optimizations (may increase code size)\n");
    printf("  -Os: Optimize for size\n");
    printf("  -Ofast: Aggressive optimizations (may break standards compliance)\n\n");
    
    printf("Key optimization techniques:\n");
    printf("  1. Loop unrolling: Reduces loop overhead\n");
    printf("  2. Function inlining: Eliminates call overhead\n");
    printf("  3. Dead code elimination: Removes unused code\n");
    printf("  4. Constant folding: Evaluates constants at compile time\n");
    printf("  5. Vectorization: Uses SIMD instructions\n");
    printf("  6. Register allocation: Minimizes memory access\n\n");
    
    // Demonstrate loop unrolling effect
    const int loop_size = 1000000;
    int *array = malloc(loop_size * sizeof(int));
    if (!array) return;
    
    for (int i = 0; i < loop_size; i++) {
        array[i] = i;
    }
    
    clock_t start, end;
    long sum;
    
    // Regular loop
    printf("Regular loop performance:\n");
    start = clock();
    sum = 0;
    for (int i = 0; i < loop_size; i++) {
        sum += array[i];
    }
    end = clock();
    double regular_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds, Sum: %ld\n", regular_time, sum);
    
    // Manually unrolled loop (4x)
    printf("\nManually unrolled loop (4x):\n");
    start = clock();
    sum = 0;
    int i;
    for (i = 0; i < loop_size - 3; i += 4) {
        sum += array[i] + array[i+1] + array[i+2] + array[i+3];
    }
    // Handle remaining elements
    for (; i < loop_size; i++) {
        sum += array[i];
    }
    end = clock();
    double unrolled_time = get_time_diff(start, end);
    printf("  Time: %.6f seconds, Sum: %ld\n", unrolled_time, sum);
    
    if (unrolled_time > 0) {
        printf("\nLoop unrolling effect: %.2fx speedup\n", regular_time / unrolled_time);
    }
    
    printf("\nOptimization best practices:\n");
    printf("  - Profile before optimizing\n");
    printf("  - Use appropriate compiler flags\n");
    printf("  - Consider algorithmic improvements first\n");
    printf("  - Measure performance impact\n");
    printf("  - Balance code readability with performance\n");
    
    free(array);
    printf("\n");
}

// Utility function implementations
double get_time_diff(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void test_sequential_access(int *array, int size) {
    volatile long sum = 0;  // volatile to prevent optimization
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
}

void test_random_access(int *array, int size) {
    volatile long sum = 0;
    srand(42);  // Fixed seed for reproducible results
    for (int i = 0; i < size; i++) {
        int index = rand() % size;
        sum += array[index];
    }
}

void test_strided_access(int *array, int size, int stride) {
    volatile long sum = 0;
    for (int i = 0; i < size; i += stride) {
        sum += array[i];
    }
}

memory_pool_t* create_memory_pool(size_t pool_size, size_t block_size) {
    memory_pool_t *pool = malloc(sizeof(memory_pool_t));
    if (!pool) return NULL;
    
    pool->pool = malloc(pool_size);
    if (!pool->pool) {
        free(pool);
        return NULL;
    }
    
    pool->size = pool_size;
    pool->used = 0;
    pool->block_size = block_size;
    
    return pool;
}

void* pool_alloc(memory_pool_t *pool) {
    if (!pool || pool->used + pool->block_size > pool->size) {
        return NULL;
    }
    
    void *ptr = pool->pool + pool->used;
    pool->used += pool->block_size;
    return ptr;
}

void destroy_memory_pool(memory_pool_t *pool) {
    if (pool) {
        free(pool->pool);
        free(pool);
    }
}