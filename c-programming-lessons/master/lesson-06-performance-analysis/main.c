/*
 * Performance Analysis Lesson
 * Demonstrates profiling and performance measurement techniques
 * 
 * This lesson covers:
 * - Performance measurement and benchmarking
 * - Profiling tools and techniques (gprof, perf, custom profilers)
 * - Bottleneck identification and optimization
 * - Memory performance analysis
 * - CPU performance optimization
 * - I/O performance considerations
 * - Scalability analysis and testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
#else
    #include <sys/time.h>
    #include <sys/resource.h>
    #include <unistd.h>
#endif

// Performance measurement constants
#define BENCHMARK_ITERATIONS 1000000
#define MATRIX_SIZE 512
#define ARRAY_SIZE 1000000
#define CACHE_LINE_SIZE 64

// Performance measurement structures
typedef struct {
    double cpu_time;
    double wall_time;
    size_t memory_used;
    size_t peak_memory;
} performance_metrics_t;

typedef struct {
    const char *name;
    void (*function)(void);
    performance_metrics_t metrics;
} benchmark_t;

// Function prototypes
void demonstrate_timing_techniques(void);
void demonstrate_cpu_profiling(void);
void demonstrate_memory_profiling(void);
void demonstrate_cache_performance(void);
void demonstrate_algorithm_analysis(void);
void demonstrate_io_performance(void);
void demonstrate_scalability_analysis(void);

// Performance measurement functions
double get_cpu_time(void);
double get_wall_time(void);
size_t get_memory_usage(void);
size_t get_peak_memory_usage(void);
void start_performance_measurement(performance_metrics_t *metrics);
void end_performance_measurement(performance_metrics_t *metrics);

// Benchmark functions
void benchmark_sorting_algorithms(void);
void benchmark_memory_access_patterns(void);
void benchmark_mathematical_operations(void);
void benchmark_string_operations(void);
void benchmark_file_operations(void);

// Algorithm implementations for benchmarking
void bubble_sort(int arr[], int n);
void quick_sort(int arr[], int low, int high);
void merge_sort(int arr[], int left, int right);
int partition(int arr[], int low, int high);
void merge(int arr[], int left, int mid, int right);

// Performance test functions
void cpu_intensive_task(void);
void memory_intensive_task(void);
void cache_friendly_access(void);
void cache_unfriendly_access(void);
void io_intensive_task(void);

// Utility functions
void print_performance_metrics(const char *name, const performance_metrics_t *metrics);
void run_benchmark(benchmark_t *benchmark);
void generate_test_data(int *array, int size);
void copy_array(int *src, int *dest, int size);

// Global variables for performance tracking
static double start_cpu_time = 0.0;
static double start_wall_time = 0.0;
static size_t start_memory = 0;

int main() {
    printf("=== Performance Analysis Lesson ===\n\n");
    
    printf("This lesson demonstrates performance analysis techniques,\n");
    printf("profiling methods, and optimization strategies.\n\n");
    
    // Demonstrate various performance analysis concepts
    demonstrate_timing_techniques();
    demonstrate_cpu_profiling();
    demonstrate_memory_profiling();
    demonstrate_cache_performance();
    demonstrate_algorithm_analysis();
    demonstrate_io_performance();
    demonstrate_scalability_analysis();
    
    printf("=== Performance Analysis Lesson Complete ===\n");
    return 0;
}

void demonstrate_timing_techniques(void) {
    printf("1. TIMING AND MEASUREMENT TECHNIQUES\n");
    printf("====================================\n\n");
    
    printf("Different timing methods:\n");
    printf("-------------------------\n");
    
    // CPU time measurement
    clock_t cpu_start = clock();
    
    // Wall clock time measurement
    double wall_start = get_wall_time();
    
    // Simulate some work
    volatile long sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += i * i;
    }
    
    clock_t cpu_end = clock();
    double wall_end = get_wall_time();
    
    double cpu_time = ((double)(cpu_end - cpu_start)) / CLOCKS_PER_SEC;
    double wall_time = wall_end - wall_start;
    
    printf("CPU time:  %.6f seconds\n", cpu_time);
    printf("Wall time: %.6f seconds\n", wall_time);
    printf("Difference: %.6f seconds\n", wall_time - cpu_time);
    
    printf("\nTiming considerations:\n");
    printf("- CPU time: Time spent by CPU on this process\n");
    printf("- Wall time: Real-world elapsed time\n");
    printf("- Wall time > CPU time indicates I/O wait or system overhead\n");
    printf("- Use multiple measurements for statistical significance\n");
    printf("- Warm up caches before timing critical sections\n\n");
    
    // Demonstrate measurement precision
    printf("Timing precision analysis:\n");
    printf("-------------------------\n");
    
    const int precision_tests = 1000;
    double min_time = 1e9, max_time = 0, total_time = 0;
    
    for (int i = 0; i < precision_tests; i++) {
        double start = get_wall_time();
        // Minimal work
        volatile int x = i;
        (void)x;
        double end = get_wall_time();
        double elapsed = end - start;
        
        if (elapsed < min_time) min_time = elapsed;
        if (elapsed > max_time) max_time = elapsed;
        total_time += elapsed;
    }
    
    printf("Minimum measured time: %.9f seconds\n", min_time);
    printf("Maximum measured time: %.9f seconds\n", max_time);
    printf("Average measured time: %.9f seconds\n", total_time / precision_tests);
    printf("Timer resolution: ~%.9f seconds\n", min_time);
    
    printf("\n");
}

void demonstrate_cpu_profiling(void) {
    printf("2. CPU PROFILING AND ANALYSIS\n");
    printf("==============================\n\n");
    
    printf("CPU-intensive benchmark comparison:\n");
    printf("-----------------------------------\n");
    
    // Define benchmarks
    benchmark_t benchmarks[] = {
        {"Mathematical Operations", benchmark_mathematical_operations, {0, 0, 0, 0}},
        {"String Operations", benchmark_string_operations, {0, 0, 0, 0}},
        {"Sorting Algorithms", benchmark_sorting_algorithms, {0, 0, 0, 0}},
        {"Memory Access Patterns", benchmark_memory_access_patterns, {0, 0, 0, 0}}
    };
    
    int num_benchmarks = sizeof(benchmarks) / sizeof(benchmarks[0]);
    
    // Run benchmarks
    for (int i = 0; i < num_benchmarks; i++) {
        printf("Running %s benchmark...\n", benchmarks[i].name);
        run_benchmark(&benchmarks[i]);
        print_performance_metrics(benchmarks[i].name, &benchmarks[i].metrics);
        printf("\n");
    }
    
    printf("CPU profiling techniques:\n");
    printf("------------------------\n");
    printf("1. Function-level profiling (gprof):\n");
    printf("   - Compile with -pg flag\n");
    printf("   - Run program to generate gmon.out\n");
    printf("   - Analyze with 'gprof program gmon.out'\n\n");
    
    printf("2. Statistical profiling (perf):\n");
    printf("   - perf record ./program\n");
    printf("   - perf report\n");
    printf("   - perf stat ./program\n\n");
    
    printf("3. Hardware performance counters:\n");
    printf("   - Cache misses, branch mispredictions\n");
    printf("   - Instructions per cycle (IPC)\n");
    printf("   - Memory bandwidth utilization\n\n");
}

void demonstrate_memory_profiling(void) {
    printf("3. MEMORY PROFILING AND ANALYSIS\n");
    printf("=================================\n\n");
    
    printf("Memory usage analysis:\n");
    printf("---------------------\n");
    
    size_t initial_memory = get_memory_usage();
    printf("Initial memory usage: %zu KB\n", initial_memory / 1024);
    
    // Allocate memory in chunks and measure
    const int chunk_size = 1024 * 1024; // 1MB chunks
    const int num_chunks = 10;
    void *chunks[num_chunks];
    
    for (int i = 0; i < num_chunks; i++) {
        chunks[i] = malloc(chunk_size);
        if (chunks[i]) {
            memset(chunks[i], i, chunk_size); // Touch the memory
            size_t current_memory = get_memory_usage();
            printf("After allocating chunk %d: %zu KB (+%zu KB)\n", 
                   i + 1, current_memory / 1024, 
                   (current_memory - initial_memory) / 1024);
        }
    }
    
    // Free memory and measure
    for (int i = 0; i < num_chunks; i++) {
        free(chunks[i]);
        chunks[i] = NULL;
    }
    
    size_t final_memory = get_memory_usage();
    printf("Final memory usage: %zu KB\n", final_memory / 1024);
    
    printf("\nMemory profiling tools:\n");
    printf("----------------------\n");
    printf("1. Valgrind Massif:\n");
    printf("   - valgrind --tool=massif ./program\n");
    printf("   - ms_print massif.out.pid\n\n");
    
    printf("2. AddressSanitizer:\n");
    printf("   - Compile with -fsanitize=address\n");
    printf("   - Detects leaks and corruption\n\n");
    
    printf("3. Custom memory tracking:\n");
    printf("   - Override malloc/free\n");
    printf("   - Track allocations and peak usage\n\n");
    
    printf("Memory performance considerations:\n");
    printf("---------------------------------\n");
    printf("- Memory allocation overhead\n");
    printf("- Fragmentation effects\n");
    printf("- Cache locality and access patterns\n");
    printf("- Memory bandwidth limitations\n");
    printf("- NUMA effects on large systems\n\n");
}

void demonstrate_cache_performance(void) {
    printf("4. CACHE PERFORMANCE ANALYSIS\n");
    printf("==============================\n\n");
    
    printf("Cache behavior demonstration:\n");
    printf("-----------------------------\n");
    
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
    
    // Test different access patterns
    performance_metrics_t sequential_metrics = {0};
    performance_metrics_t random_metrics = {0};
    performance_metrics_t strided_metrics = {0};
    
    // Sequential access
    start_performance_measurement(&sequential_metrics);
    volatile long sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += test_array[i];
    }
    end_performance_measurement(&sequential_metrics);
    
    // Random access
    srand(42); // Fixed seed for reproducible results
    start_performance_measurement(&random_metrics);
    sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int index = rand() % ARRAY_SIZE;
        sum += test_array[index];
    }
    end_performance_measurement(&random_metrics);
    
    // Strided access (every 16th element)
    start_performance_measurement(&strided_metrics);
    sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i += 16) {
        sum += test_array[i];
    }
    end_performance_measurement(&strided_metrics);
    
    print_performance_metrics("Sequential Access", &sequential_metrics);
    print_performance_metrics("Random Access", &random_metrics);
    print_performance_metrics("Strided Access", &strided_metrics);
    
    printf("Cache performance insights:\n");
    printf("--------------------------\n");
    printf("- Sequential access is cache-friendly\n");
    printf("- Random access causes cache misses\n");
    printf("- Strided access depends on stride size\n");
    printf("- Cache line size affects performance\n");
    printf("- Prefetching can help predictable patterns\n\n");
    
    free(test_array);
}

void demonstrate_algorithm_analysis(void) {
    printf("5. ALGORITHM PERFORMANCE ANALYSIS\n");
    printf("==================================\n\n");
    
    printf("Sorting algorithm comparison:\n");
    printf("-----------------------------\n");
    
    const int sizes[] = {1000, 5000, 10000, 25000};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("Array Size | Bubble Sort | Quick Sort | Merge Sort\n");
    printf("-----------|-------------|------------|------------\n");
    
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        
        // Generate test data
        int *original = malloc(size * sizeof(int));
        int *test_array = malloc(size * sizeof(int));
        
        if (!original || !test_array) {
            printf("Memory allocation failed for size %d\n", size);
            continue;
        }
        
        generate_test_data(original, size);
        
        // Bubble sort
        copy_array(original, test_array, size);
        clock_t start = clock();
        bubble_sort(test_array, size);
        clock_t end = clock();
        double bubble_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Quick sort
        copy_array(original, test_array, size);
        start = clock();
        quick_sort(test_array, 0, size - 1);
        end = clock();
        double quick_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Merge sort
        copy_array(original, test_array, size);
        start = clock();
        merge_sort(test_array, 0, size - 1);
        end = clock();
        double merge_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("%10d | %11.6f | %10.6f | %10.6f\n", 
               size, bubble_time, quick_time, merge_time);
        
        free(original);
        free(test_array);
    }
    
    printf("\nComplexity analysis:\n");
    printf("-------------------\n");
    printf("- Bubble Sort: O(n²) - Quadratic growth\n");
    printf("- Quick Sort:  O(n log n) average, O(n²) worst\n");
    printf("- Merge Sort:  O(n log n) guaranteed\n");
    printf("- Performance scales with theoretical complexity\n\n");
}

void demonstrate_io_performance(void) {
    printf("6. I/O PERFORMANCE ANALYSIS\n");
    printf("============================\n\n");
    
    printf("File I/O performance test:\n");
    printf("--------------------------\n");
    
    const char *test_file = "performance_test.dat";
    const int buffer_sizes[] = {1, 64, 1024, 4096, 65536};
    const int num_buffer_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);
    const int total_data = 1024 * 1024; // 1MB total
    
    printf("Buffer Size | Write Time | Read Time  | Total Time\n");
    printf("------------|------------|------------|------------\n");
    
    for (int b = 0; b < num_buffer_sizes; b++) {
        int buffer_size = buffer_sizes[b];
        char *buffer = malloc(buffer_size);
        if (!buffer) continue;
        
        memset(buffer, 'A', buffer_size);
        
        // Write test
        clock_t start = clock();
        FILE *file = fopen(test_file, "wb");
        if (file) {
            int bytes_written = 0;
            while (bytes_written < total_data) {
                int to_write = (total_data - bytes_written < buffer_size) ? 
                              (total_data - bytes_written) : buffer_size;
                fwrite(buffer, 1, to_write, file);
                bytes_written += to_write;
            }
            fclose(file);
        }
        clock_t write_end = clock();
        double write_time = ((double)(write_end - start)) / CLOCKS_PER_SEC;
        
        // Read test
        start = clock();
        file = fopen(test_file, "rb");
        if (file) {
            int bytes_read = 0;
            while (bytes_read < total_data) {
                int to_read = (total_data - bytes_read < buffer_size) ? 
                             (total_data - bytes_read) : buffer_size;
                fread(buffer, 1, to_read, file);
                bytes_read += to_read;
            }
            fclose(file);
        }
        clock_t read_end = clock();
        double read_time = ((double)(read_end - start)) / CLOCKS_PER_SEC;
        
        printf("%11d | %10.6f | %10.6f | %10.6f\n", 
               buffer_size, write_time, read_time, write_time + read_time);
        
        free(buffer);
    }
    
    // Clean up
    remove(test_file);
    
    printf("\nI/O performance insights:\n");
    printf("------------------------\n");
    printf("- Larger buffers reduce system call overhead\n");
    printf("- Optimal buffer size depends on system and storage\n");
    printf("- Sequential I/O is faster than random I/O\n");
    printf("- Buffered I/O vs unbuffered I/O trade-offs\n");
    printf("- Network I/O has different characteristics\n\n");
}

void demonstrate_scalability_analysis(void) {
    printf("7. SCALABILITY ANALYSIS\n");
    printf("========================\n\n");
    
    printf("Performance scaling with input size:\n");
    printf("------------------------------------\n");
    
    const int base_size = 1000;
    const double scale_factors[] = {1.0, 2.0, 4.0, 8.0, 16.0};
    const int num_factors = sizeof(scale_factors) / sizeof(scale_factors[0]);
    
    printf("Scale Factor | Input Size | Time (sec) | Time Ratio\n");
    printf("-------------|------------|------------|------------\n");
    
    double base_time = 0;
    
    for (int f = 0; f < num_factors; f++) {
        int size = (int)(base_size * scale_factors[f]);
        
        // Simulate O(n log n) algorithm
        clock_t start = clock();
        volatile double result = 0;
        for (int i = 1; i <= size; i++) {
            result += i * log(i);
        }
        clock_t end = clock();
        
        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (f == 0) {
            base_time = elapsed;
        }
        
        double ratio = (base_time > 0) ? elapsed / base_time : 1.0;
        
        printf("%12.1f | %10d | %10.6f | %10.2f\n", 
               scale_factors[f], size, elapsed, ratio);
    }
    
    printf("\nScalability considerations:\n");
    printf("--------------------------\n");
    printf("- Linear scaling: 2x input → 2x time\n");
    printf("- Logarithmic scaling: 2x input → <2x time\n");
    printf("- Quadratic scaling: 2x input → 4x time\n");
    printf("- Memory bandwidth limitations\n");
    printf("- Parallel processing opportunities\n");
    printf("- System resource constraints\n\n");
    
    printf("Performance optimization strategies:\n");
    printf("-----------------------------------\n");
    printf("1. Algorithm optimization (biggest impact)\n");
    printf("2. Data structure optimization\n");
    printf("3. Memory access pattern optimization\n");
    printf("4. Compiler optimization flags\n");
    printf("5. Platform-specific optimizations\n");
    printf("6. Parallel processing\n");
    printf("7. Hardware acceleration\n\n");
}

// Performance measurement function implementations
double get_cpu_time(void) {
    return ((double)clock()) / CLOCKS_PER_SEC;
}

double get_wall_time(void) {
#ifdef _WIN32
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / frequency.QuadPart;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
#endif
}

size_t get_memory_usage(void) {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize;
    }
    return 0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss * 1024; // Convert KB to bytes on Linux
    }
    return 0;
#endif
}

size_t get_peak_memory_usage(void) {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.PeakWorkingSetSize;
    }
    return 0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss * 1024;
    }
    return 0;
#endif
}

void start_performance_measurement(performance_metrics_t *metrics) {
    (void)metrics; // Suppress unused parameter warning
    start_cpu_time = get_cpu_time();
    start_wall_time = get_wall_time();
    start_memory = get_memory_usage();
}

void end_performance_measurement(performance_metrics_t *metrics) {
    metrics->cpu_time = get_cpu_time() - start_cpu_time;
    metrics->wall_time = get_wall_time() - start_wall_time;
    metrics->memory_used = get_memory_usage() - start_memory;
    metrics->peak_memory = get_peak_memory_usage();
}

void print_performance_metrics(const char *name, const performance_metrics_t *metrics) {
    printf("%s Performance:\n", name);
    printf("  CPU Time:     %.6f seconds\n", metrics->cpu_time);
    printf("  Wall Time:    %.6f seconds\n", metrics->wall_time);
    printf("  Memory Used:  %zu bytes\n", metrics->memory_used);
    printf("  Peak Memory:  %zu bytes\n", metrics->peak_memory);
}

void run_benchmark(benchmark_t *benchmark) {
    start_performance_measurement(&benchmark->metrics);
    benchmark->function();
    end_performance_measurement(&benchmark->metrics);
}

// Benchmark function implementations
void benchmark_mathematical_operations(void) {
    volatile double result = 0;
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        result += sin(i) * cos(i) + sqrt(i);
    }
}

void benchmark_string_operations(void) {
    char buffer[1000];
    for (int i = 0; i < BENCHMARK_ITERATIONS / 1000; i++) {
        sprintf(buffer, "Test string %d with formatting %f", i, i * 3.14159);
        int len = strlen(buffer);
        (void)len; // Suppress unused variable warning
    }
}

void benchmark_sorting_algorithms(void) {
    const int size = 1000;
    int *array = malloc(size * sizeof(int));
    if (array) {
        generate_test_data(array, size);
        quick_sort(array, 0, size - 1);
        free(array);
    }
}

void benchmark_memory_access_patterns(void) {
    const int size = 100000;
    int *array = malloc(size * sizeof(int));
    if (array) {
        // Sequential access
        volatile long sum = 0;
        for (int i = 0; i < size; i++) {
            array[i] = i;
            sum += array[i];
        }
        free(array);
    }
}

// Algorithm implementations
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

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return (i + 1);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *left_arr = malloc(n1 * sizeof(int));
    int *right_arr = malloc(n2 * sizeof(int));
    
    if (!left_arr || !right_arr) {
        free(left_arr);
        free(right_arr);
        return;
    }
    
    for (int i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        right_arr[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
    
    free(left_arr);
    free(right_arr);
}

// Utility function implementations
void generate_test_data(int *array, int size) {
    srand(42); // Fixed seed for reproducible results
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000;
    }
}

void copy_array(int *src, int *dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}