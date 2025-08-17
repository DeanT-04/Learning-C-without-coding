/*
 * Advanced Algorithms Lesson
 * Demonstrates sorting and searching algorithms with complexity analysis
 * 
 * This lesson covers:
 * - Bubble Sort, Selection Sort, Insertion Sort (O(n²))
 * - Quick Sort, Merge Sort (O(n log n))
 * - Binary Search (O(log n))
 * - Algorithm complexity analysis and optimization techniques
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1000
#define SMALL_ARRAY_SIZE 10

// Function prototypes
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void quick_sort(int arr[], int low, int high);
void merge_sort(int arr[], int left, int right);
int binary_search(int arr[], int n, int target);
int linear_search(int arr[], int n, int target);

// Utility functions
void print_array(int arr[], int n);
void copy_array(int source[], int dest[], int n);
void generate_random_array(int arr[], int n);
double measure_time(void (*sort_func)(int[], int), int arr[], int n);
double measure_search_time(int (*search_func)(int[], int, int), int arr[], int n, int target);

// Partition function for Quick Sort
int partition(int arr[], int low, int high);

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right);

int main() {
    printf("=== Advanced Algorithms Lesson ===\n\n");
    
    // Small array for demonstration
    int demo_array[SMALL_ARRAY_SIZE] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    int temp_array[SMALL_ARRAY_SIZE];
    
    printf("Original array: ");
    print_array(demo_array, SMALL_ARRAY_SIZE);
    printf("\n");
    
    // Demonstrate different sorting algorithms
    printf("1. SORTING ALGORITHMS\n");
    printf("====================\n\n");
    
    // Bubble Sort
    copy_array(demo_array, temp_array, SMALL_ARRAY_SIZE);
    printf("Bubble Sort (O(n²)):\n");
    printf("Before: ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    bubble_sort(temp_array, SMALL_ARRAY_SIZE);
    printf("After:  ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    printf("\n");
    
    // Selection Sort
    copy_array(demo_array, temp_array, SMALL_ARRAY_SIZE);
    printf("Selection Sort (O(n²)):\n");
    printf("Before: ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    selection_sort(temp_array, SMALL_ARRAY_SIZE);
    printf("After:  ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    printf("\n");
    
    // Insertion Sort
    copy_array(demo_array, temp_array, SMALL_ARRAY_SIZE);
    printf("Insertion Sort (O(n²)):\n");
    printf("Before: ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    insertion_sort(temp_array, SMALL_ARRAY_SIZE);
    printf("After:  ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    printf("\n");
    
    // Quick Sort
    copy_array(demo_array, temp_array, SMALL_ARRAY_SIZE);
    printf("Quick Sort (O(n log n)):\n");
    printf("Before: ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    quick_sort(temp_array, 0, SMALL_ARRAY_SIZE - 1);
    printf("After:  ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    printf("\n");
    
    // Merge Sort
    copy_array(demo_array, temp_array, SMALL_ARRAY_SIZE);
    printf("Merge Sort (O(n log n)):\n");
    printf("Before: ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    merge_sort(temp_array, 0, SMALL_ARRAY_SIZE - 1);
    printf("After:  ");
    print_array(temp_array, SMALL_ARRAY_SIZE);
    printf("\n");
    
    // Searching algorithms
    printf("2. SEARCHING ALGORITHMS\n");
    printf("=======================\n\n");
    
    // Create a sorted array for binary search
    int sorted_array[SMALL_ARRAY_SIZE] = {11, 12, 22, 25, 34, 50, 64, 76, 88, 90};
    int target = 25;
    
    printf("Sorted array: ");
    print_array(sorted_array, SMALL_ARRAY_SIZE);
    printf("Searching for: %d\n\n", target);
    
    // Linear Search
    int linear_result = linear_search(sorted_array, SMALL_ARRAY_SIZE, target);
    printf("Linear Search (O(n)): ");
    if (linear_result != -1) {
        printf("Found at index %d\n", linear_result);
    } else {
        printf("Not found\n");
    }
    
    // Binary Search
    int binary_result = binary_search(sorted_array, SMALL_ARRAY_SIZE, target);
    printf("Binary Search (O(log n)): ");
    if (binary_result != -1) {
        printf("Found at index %d\n", binary_result);
    } else {
        printf("Not found\n");
    }
    
    printf("\n");
    
    // Performance comparison
    printf("3. PERFORMANCE ANALYSIS\n");
    printf("=======================\n\n");
    
    // Generate larger arrays for performance testing
    int *large_array = malloc(MAX_SIZE * sizeof(int));
    int *test_array = malloc(MAX_SIZE * sizeof(int));
    
    if (large_array == NULL || test_array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    generate_random_array(large_array, MAX_SIZE);
    
    printf("Performance comparison with %d elements:\n", MAX_SIZE);
    printf("Algorithm          | Time (seconds)\n");
    printf("-------------------|---------------\n");
    
    // Test sorting algorithms
    double time_taken;
    
    copy_array(large_array, test_array, MAX_SIZE);
    time_taken = measure_time(bubble_sort, test_array, MAX_SIZE);
    printf("Bubble Sort        | %.6f\n", time_taken);
    
    copy_array(large_array, test_array, MAX_SIZE);
    time_taken = measure_time(selection_sort, test_array, MAX_SIZE);
    printf("Selection Sort     | %.6f\n", time_taken);
    
    copy_array(large_array, test_array, MAX_SIZE);
    time_taken = measure_time(insertion_sort, test_array, MAX_SIZE);
    printf("Insertion Sort     | %.6f\n", time_taken);
    
    printf("\nNote: Quick Sort and Merge Sort are too fast to measure accurately\n");
    printf("with this simple timing method on small arrays.\n\n");
    
    // Search performance comparison
    quick_sort(large_array, 0, MAX_SIZE - 1); // Sort for binary search
    int search_target = large_array[MAX_SIZE / 2]; // Pick middle element
    
    printf("Search performance comparison:\n");
    printf("Algorithm          | Time (seconds)\n");
    printf("-------------------|---------------\n");
    
    time_taken = measure_search_time(linear_search, large_array, MAX_SIZE, search_target);
    printf("Linear Search      | %.6f\n", time_taken);
    
    time_taken = measure_search_time(binary_search, large_array, MAX_SIZE, search_target);
    printf("Binary Search      | %.6f\n", time_taken);
    
    printf("\n4. ALGORITHM COMPLEXITY SUMMARY\n");
    printf("===============================\n\n");
    printf("Sorting Algorithms:\n");
    printf("- Bubble Sort:    Best O(n), Average O(n²), Worst O(n²)\n");
    printf("- Selection Sort: Best O(n²), Average O(n²), Worst O(n²)\n");
    printf("- Insertion Sort: Best O(n), Average O(n²), Worst O(n²)\n");
    printf("- Quick Sort:     Best O(n log n), Average O(n log n), Worst O(n²)\n");
    printf("- Merge Sort:     Best O(n log n), Average O(n log n), Worst O(n log n)\n\n");
    
    printf("Searching Algorithms:\n");
    printf("- Linear Search:  Best O(1), Average O(n), Worst O(n)\n");
    printf("- Binary Search:  Best O(1), Average O(log n), Worst O(log n)\n\n");
    
    printf("Space Complexity:\n");
    printf("- Bubble, Selection, Insertion Sort: O(1) - In-place\n");
    printf("- Quick Sort: O(log n) - Recursive stack\n");
    printf("- Merge Sort: O(n) - Additional array needed\n");
    
    free(large_array);
    free(test_array);
    
    return 0;
}

// Bubble Sort Implementation
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // Optimization: if no swapping occurred, array is sorted
        if (!swapped) break;
    }
}

// Selection Sort Implementation
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap minimum element with first element
        if (min_idx != i) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}

// Insertion Sort Implementation
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Move elements greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort Implementation
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = (low - 1);     // Index of smaller element
    
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

// Merge Sort Implementation
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    int *left_arr = malloc(n1 * sizeof(int));
    int *right_arr = malloc(n2 * sizeof(int));
    
    if (left_arr == NULL || right_arr == NULL) {
        printf("Memory allocation failed in merge!\n");
        return;
    }
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        right_arr[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back into arr[left..right]
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
    
    // Copy remaining elements
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

// Binary Search Implementation
int binary_search(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target)
            return mid;
        
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    
    return -1; // Element not found
}

// Linear Search Implementation
int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1; // Element not found
}

// Utility Functions
void print_array(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]");
}

void copy_array(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void generate_random_array(int arr[], int n) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Random numbers 0-999
    }
}

double measure_time(void (*sort_func)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double measure_search_time(int (*search_func)(int[], int, int), int arr[], int n, int target) {
    clock_t start = clock();
    search_func(arr, n, target);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}