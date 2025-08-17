/*
 * Bit Manipulation Lesson
 * Demonstrates bitwise operations and practical applications
 * 
 * This lesson covers:
 * - Basic bitwise operations (AND, OR, XOR, NOT, shifts)
 * - Bit manipulation techniques and tricks
 * - Bit fields and packed data structures
 * - Practical applications (flags, masks, compression)
 * - Performance optimization using bit operations
 * - Binary representation and endianness
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <time.h>

// Bit manipulation macros
#define SET_BIT(x, n)       ((x) |= (1U << (n)))
#define CLEAR_BIT(x, n)     ((x) &= ~(1U << (n)))
#define TOGGLE_BIT(x, n)    ((x) ^= (1U << (n)))
#define CHECK_BIT(x, n)     (((x) >> (n)) & 1U)
#define MASK(n)             ((1U << (n)) - 1)
#define EXTRACT_BITS(x, start, len) (((x) >> (start)) & MASK(len))
#define INSERT_BITS(x, val, start, len) \
    ((x) = ((x) & ~(MASK(len) << (start))) | (((val) & MASK(len)) << (start)))

// Bit field structures
struct flags {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int flag3 : 1;
    unsigned int reserved : 5;
    unsigned int value : 8;
    unsigned int status : 16;
};

struct rgb_color {
    unsigned int red : 8;
    unsigned int green : 8;
    unsigned int blue : 8;
    unsigned int alpha : 8;
};

// Union for endianness demonstration
union endian_test {
    uint32_t value;
    uint8_t bytes[4];
};

// Function prototypes
void demonstrate_basic_operations(void);
void demonstrate_bit_manipulation_tricks(void);
void demonstrate_bit_fields(void);
void demonstrate_practical_applications(void);
void demonstrate_performance_optimizations(void);
void demonstrate_binary_representation(void);
void demonstrate_advanced_techniques(void);

// Utility functions
void print_binary(uint32_t value, int bits);
void print_binary_8(uint8_t value);
void print_binary_16(uint16_t value);
void print_binary_32(uint32_t value);
int count_set_bits(uint32_t value);
int count_set_bits_fast(uint32_t value);
uint32_t reverse_bits(uint32_t value);
int find_first_set_bit(uint32_t value);
int is_power_of_two(uint32_t value);
uint32_t next_power_of_two(uint32_t value);

int main() {
    printf("=== Bit Manipulation Lesson ===\n\n");
    
    printf("This lesson demonstrates bitwise operations and their\n");
    printf("practical applications in systems programming.\n\n");
    
    // Demonstrate various bit manipulation concepts
    demonstrate_basic_operations();
    demonstrate_bit_manipulation_tricks();
    demonstrate_bit_fields();
    demonstrate_practical_applications();
    demonstrate_performance_optimizations();
    demonstrate_binary_representation();
    demonstrate_advanced_techniques();
    
    printf("=== Bit Manipulation Lesson Complete ===\n");
    return 0;
}

void demonstrate_basic_operations(void) {
    printf("1. BASIC BITWISE OPERATIONS\n");
    printf("===========================\n\n");
    
    uint8_t a = 0b10110101;  // 181 in decimal
    uint8_t b = 0b11001010;  // 202 in decimal
    
    printf("Input values:\n");
    printf("a = ");
    print_binary_8(a);
    printf(" (%d)\n", a);
    printf("b = ");
    print_binary_8(b);
    printf(" (%d)\n", b);
    printf("\n");
    
    // AND operation
    uint8_t and_result = a & b;
    printf("AND (a & b):\n");
    printf("Result = ");
    print_binary_8(and_result);
    printf(" (%d)\n", and_result);
    printf("Use case: Masking bits, checking flags\n\n");
    
    // OR operation
    uint8_t or_result = a | b;
    printf("OR (a | b):\n");
    printf("Result = ");
    print_binary_8(or_result);
    printf(" (%d)\n", or_result);
    printf("Use case: Setting bits, combining flags\n\n");
    
    // XOR operation
    uint8_t xor_result = a ^ b;
    printf("XOR (a ^ b):\n");
    printf("Result = ");
    print_binary_8(xor_result);
    printf(" (%d)\n", xor_result);
    printf("Use case: Toggling bits, encryption, checksums\n\n");
    
    // NOT operation
    uint8_t not_a = ~a;
    printf("NOT (~a):\n");
    printf("Result = ");
    print_binary_8(not_a);
    printf(" (%d)\n", not_a);
    printf("Use case: Bit inversion, creating masks\n\n");
    
    // Left shift
    uint8_t left_shift = a << 2;
    printf("Left Shift (a << 2):\n");
    printf("Result = ");
    print_binary_8(left_shift);
    printf(" (%d)\n", left_shift);
    printf("Use case: Multiplication by powers of 2\n\n");
    
    // Right shift
    uint8_t right_shift = a >> 2;
    printf("Right Shift (a >> 2):\n");
    printf("Result = ");
    print_binary_8(right_shift);
    printf(" (%d)\n", right_shift);
    printf("Use case: Division by powers of 2\n\n");
}

void demonstrate_bit_manipulation_tricks(void) {
    printf("2. BIT MANIPULATION TRICKS\n");
    printf("==========================\n\n");
    
    uint32_t test_value = 0b11010110101100101010110110101010;
    
    printf("Test value: ");
    print_binary_32(test_value);
    printf(" (%u)\n\n", test_value);
    
    // Set specific bit
    uint32_t set_result = test_value;
    SET_BIT(set_result, 5);
    printf("Set bit 5: ");
    print_binary_32(set_result);
    printf("\n");
    
    // Clear specific bit
    uint32_t clear_result = test_value;
    CLEAR_BIT(clear_result, 10);
    printf("Clear bit 10: ");
    print_binary_32(clear_result);
    printf("\n");
    
    // Toggle specific bit
    uint32_t toggle_result = test_value;
    TOGGLE_BIT(toggle_result, 15);
    printf("Toggle bit 15: ");
    print_binary_32(toggle_result);
    printf("\n");
    
    // Check specific bit
    int bit_status = CHECK_BIT(test_value, 20);
    printf("Bit 20 is: %s\n", bit_status ? "SET" : "CLEAR");
    
    // Extract bits
    uint32_t extracted = EXTRACT_BITS(test_value, 8, 8);
    printf("Extract 8 bits starting at position 8: ");
    print_binary_8((uint8_t)extracted);
    printf(" (%u)\n", extracted);
    
    // Insert bits
    uint32_t insert_result = test_value;
    INSERT_BITS(insert_result, 0xFF, 16, 8);
    printf("Insert 0xFF at position 16 (8 bits): ");
    print_binary_32(insert_result);
    printf("\n");
    
    printf("\nCommon bit manipulation tricks:\n");
    
    // Count set bits
    int bit_count = count_set_bits(test_value);
    printf("Number of set bits: %d\n", bit_count);
    
    // Check if power of two
    uint32_t power_test = 64;
    printf("%u is %sa power of two\n", power_test, 
           is_power_of_two(power_test) ? "" : "not ");
    
    // Find first set bit
    int first_bit = find_first_set_bit(test_value);
    printf("First set bit position: %d\n", first_bit);
    
    // Reverse bits
    uint32_t reversed = reverse_bits(test_value);
    printf("Reversed bits: ");
    print_binary_32(reversed);
    printf("\n");
    
    // Next power of two
    uint32_t next_pow2 = next_power_of_two(100);
    printf("Next power of two after 100: %u\n", next_pow2);
    
    printf("\n");
}

void demonstrate_bit_fields(void) {
    printf("3. BIT FIELDS AND PACKED STRUCTURES\n");
    printf("===================================\n\n");
    
    printf("Bit field structure sizes:\n");
    printf("struct flags: %zu bytes\n", sizeof(struct flags));
    printf("struct rgb_color: %zu bytes\n", sizeof(struct rgb_color));
    printf("Regular int: %zu bytes\n\n", sizeof(int));
    
    // Demonstrate flags structure
    struct flags system_flags = {0};
    system_flags.flag1 = 1;
    system_flags.flag2 = 0;
    system_flags.flag3 = 1;
    system_flags.value = 42;
    system_flags.status = 0x1234;
    
    printf("Flags structure:\n");
    printf("flag1: %u\n", system_flags.flag1);
    printf("flag2: %u\n", system_flags.flag2);
    printf("flag3: %u\n", system_flags.flag3);
    printf("value: %u\n", system_flags.value);
    printf("status: 0x%04X\n", system_flags.status);
    
    // Show raw memory representation
    uint32_t *raw_flags = (uint32_t*)&system_flags;
    printf("Raw memory: ");
    print_binary_32(*raw_flags);
    printf(" (0x%08X)\n\n", *raw_flags);
    
    // Demonstrate RGB color structure
    struct rgb_color color = {255, 128, 64, 200};
    printf("RGB Color structure:\n");
    printf("Red: %u, Green: %u, Blue: %u, Alpha: %u\n", 
           color.red, color.green, color.blue, color.alpha);
    
    uint32_t *raw_color = (uint32_t*)&color;
    printf("Raw color value: 0x%08X\n", *raw_color);
    printf("HTML color: #%02X%02X%02X (alpha: %02X)\n", 
           color.red, color.green, color.blue, color.alpha);
    
    printf("\nBit field advantages:\n");
    printf("- Memory efficient for flags and small values\n");
    printf("- Hardware register mapping\n");
    printf("- Protocol field packing\n");
    printf("\nBit field disadvantages:\n");
    printf("- Non-portable bit ordering\n");
    printf("- Cannot take address of bit fields\n");
    printf("- Potential performance overhead\n\n");
}

void demonstrate_practical_applications(void) {
    printf("4. PRACTICAL APPLICATIONS\n");
    printf("=========================\n\n");
    
    // Permission system (like Unix file permissions)
    printf("Permission System Example:\n");
    printf("-------------------------\n");
    
    #define PERM_READ    0x4  // 100
    #define PERM_WRITE   0x2  // 010
    #define PERM_EXECUTE 0x1  // 001
    
    uint8_t file_permissions = PERM_READ | PERM_WRITE;
    
    printf("File permissions: ");
    print_binary_8(file_permissions);
    printf(" (");
    if (file_permissions & PERM_READ) printf("r");
    else printf("-");
    if (file_permissions & PERM_WRITE) printf("w");
    else printf("-");
    if (file_permissions & PERM_EXECUTE) printf("x");
    else printf("-");
    printf(")\n");
    
    // Add execute permission
    file_permissions |= PERM_EXECUTE;
    printf("After adding execute: ");
    print_binary_8(file_permissions);
    printf(" (rwx)\n");
    
    // Remove write permission
    file_permissions &= ~PERM_WRITE;
    printf("After removing write: ");
    print_binary_8(file_permissions);
    printf(" (r-x)\n\n");
    
    // Bit set implementation
    printf("Bit Set Implementation:\n");
    printf("----------------------\n");
    
    #define SET_SIZE 64
    uint64_t bit_set = 0;
    
    // Add elements to set
    int elements[] = {5, 12, 23, 31, 45, 63};
    int num_elements = sizeof(elements) / sizeof(elements[0]);
    
    for (int i = 0; i < num_elements; i++) {
        bit_set |= (1ULL << elements[i]);
    }
    
    printf("Set contains: ");
    for (int i = 0; i < SET_SIZE; i++) {
        if (bit_set & (1ULL << i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    // Check membership
    int test_element = 23;
    printf("Element %d is %sin the set\n", test_element,
           (bit_set & (1ULL << test_element)) ? "" : "not ");
    
    // Remove element
    bit_set &= ~(1ULL << 12);
    printf("After removing 12: ");
    for (int i = 0; i < SET_SIZE; i++) {
        if (bit_set & (1ULL << i)) {
            printf("%d ", i);
        }
    }
    printf("\n\n");
    
    // Simple compression example
    printf("Simple Compression Example:\n");
    printf("---------------------------\n");
    
    // Pack 4 values (0-15) into a single byte
    uint8_t packed = 0;
    uint8_t values[4] = {3, 7, 12, 9};
    
    for (int i = 0; i < 4; i++) {
        packed |= (values[i] & 0xF) << (i * 4);
    }
    
    printf("Original values: %d, %d, %d, %d\n", 
           values[0], values[1], values[2], values[3]);
    printf("Packed into byte: ");
    print_binary_8(packed);
    printf(" (0x%02X)\n", packed);
    
    // Unpack values
    printf("Unpacked values: ");
    for (int i = 0; i < 4; i++) {
        uint8_t unpacked = (packed >> (i * 4)) & 0xF;
        printf("%d ", unpacked);
    }
    printf("\n\n");
}

void demonstrate_performance_optimizations(void) {
    printf("5. PERFORMANCE OPTIMIZATIONS\n");
    printf("============================\n\n");
    
    const int iterations = 1000000;
    clock_t start, end;
    
    // Multiplication vs bit shift
    printf("Multiplication vs Bit Shift:\n");
    printf("----------------------------\n");
    
    volatile int result = 0;  // volatile to prevent optimization
    
    // Regular multiplication
    start = clock();
    for (int i = 0; i < iterations; i++) {
        result = i * 8;
    }
    end = clock();
    double mult_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Multiplication by 8: %.6f seconds\n", mult_time);
    
    // Bit shift
    start = clock();
    for (int i = 0; i < iterations; i++) {
        result = i << 3;  // Multiply by 8 (2^3)
    }
    end = clock();
    double shift_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Left shift by 3:    %.6f seconds\n", shift_time);
    
    if (shift_time > 0) {
        printf("Speedup: %.2fx\n\n", mult_time / shift_time);
    } else {
        printf("Both operations optimized to same code\n\n");
    }
    
    // Division vs bit shift
    printf("Division vs Bit Shift:\n");
    printf("----------------------\n");
    
    // Regular division
    start = clock();
    for (int i = 1; i < iterations; i++) {
        result = i / 16;
    }
    end = clock();
    double div_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Division by 16:     %.6f seconds\n", div_time);
    
    // Bit shift
    start = clock();
    for (int i = 1; i < iterations; i++) {
        result = i >> 4;  // Divide by 16 (2^4)
    }
    end = clock();
    double rshift_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Right shift by 4:   %.6f seconds\n", rshift_time);
    
    if (rshift_time > 0) {
        printf("Speedup: %.2fx\n\n", div_time / rshift_time);
    } else {
        printf("Both operations optimized to same code\n\n");
    }
    
    // Bit counting comparison
    printf("Bit Counting Performance:\n");
    printf("------------------------\n");
    
    uint32_t test_values[1000];
    srand(42);
    for (int i = 0; i < 1000; i++) {
        test_values[i] = rand();
    }
    
    // Naive bit counting
    start = clock();
    int total_bits = 0;
    for (int iter = 0; iter < 1000; iter++) {
        for (int i = 0; i < 1000; i++) {
            total_bits += count_set_bits(test_values[i]);
        }
    }
    end = clock();
    double naive_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Naive bit counting:  %.6f seconds\n", naive_time);
    
    // Fast bit counting
    start = clock();
    total_bits = 0;
    for (int iter = 0; iter < 1000; iter++) {
        for (int i = 0; i < 1000; i++) {
            total_bits += count_set_bits_fast(test_values[i]);
        }
    }
    end = clock();
    double fast_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Fast bit counting:   %.6f seconds\n", fast_time);
    
    if (fast_time > 0) {
        printf("Speedup: %.2fx\n", naive_time / fast_time);
    }
    
    printf("Total bits counted: %d\n\n", total_bits);
}

void demonstrate_binary_representation(void) {
    printf("6. BINARY REPRESENTATION AND ENDIANNESS\n");
    printf("========================================\n\n");
    
    // Demonstrate different number representations
    printf("Number Representations:\n");
    printf("----------------------\n");
    
    int32_t signed_value = -42;
    uint32_t unsigned_value = 42;
    
    printf("Signed -42:   ");
    print_binary_32((uint32_t)signed_value);
    printf(" (two's complement)\n");
    
    printf("Unsigned 42:  ");
    print_binary_32(unsigned_value);
    printf("\n\n");
    
    // Demonstrate endianness
    printf("Endianness Demonstration:\n");
    printf("------------------------\n");
    
    union endian_test test;
    test.value = 0x12345678;
    
    printf("32-bit value: 0x%08X\n", test.value);
    printf("Byte layout: ");
    for (int i = 0; i < 4; i++) {
        printf("0x%02X ", test.bytes[i]);
    }
    
    // Determine endianness
    if (test.bytes[0] == 0x78) {
        printf("(Little Endian)\n");
    } else if (test.bytes[0] == 0x12) {
        printf("(Big Endian)\n");
    } else {
        printf("(Unknown Endianness)\n");
    }
    
    printf("\nByte order significance:\n");
    printf("- Network protocols typically use big endian\n");
    printf("- x86/x64 processors use little endian\n");
    printf("- ARM can be configured for either\n");
    printf("- Always consider endianness for file formats and networking\n\n");
    
    // Floating point representation
    printf("Floating Point Representation:\n");
    printf("------------------------------\n");
    
    union {
        float f;
        uint32_t i;
    } float_bits;
    
    float_bits.f = 3.14159f;
    printf("Float value: %f\n", float_bits.f);
    printf("Bit pattern: ");
    print_binary_32(float_bits.i);
    printf("\n");
    printf("Hex pattern: 0x%08X\n", float_bits.i);
    
    // Extract IEEE 754 components
    uint32_t sign = (float_bits.i >> 31) & 1;
    uint32_t exponent = (float_bits.i >> 23) & 0xFF;
    uint32_t mantissa = float_bits.i & 0x7FFFFF;
    
    printf("Sign: %u, Exponent: %u (biased), Mantissa: 0x%06X\n", 
           sign, exponent, mantissa);
    printf("\n");
}

void demonstrate_advanced_techniques(void) {
    printf("7. ADVANCED BIT MANIPULATION TECHNIQUES\n");
    printf("=======================================\n\n");
    
    // Gray code
    printf("Gray Code Conversion:\n");
    printf("--------------------\n");
    
    for (int i = 0; i < 8; i++) {
        uint32_t gray = i ^ (i >> 1);  // Binary to Gray code
        printf("Binary %d: ", i);
        print_binary(i, 3);
        printf(" -> Gray: ");
        print_binary(gray, 3);
        printf(" (%u)\n", gray);
    }
    printf("\n");
    
    // Bit reversal patterns
    printf("Bit Reversal Techniques:\n");
    printf("-----------------------\n");
    
    uint8_t test_byte = 0b10110100;
    printf("Original: ");
    print_binary_8(test_byte);
    printf("\n");
    
    // Simple bit reversal
    uint8_t reversed = 0;
    uint8_t temp = test_byte;
    for (int i = 0; i < 8; i++) {
        reversed = (reversed << 1) | (temp & 1);
        temp >>= 1;
    }
    printf("Reversed: ");
    print_binary_8(reversed);
    printf("\n\n");
    
    // Bit manipulation puzzles
    printf("Bit Manipulation Puzzles:\n");
    printf("------------------------\n");
    
    // Swap two numbers without temporary variable
    int a = 42, b = 17;
    printf("Before swap: a = %d, b = %d\n", a, b);
    a ^= b;
    b ^= a;
    a ^= b;
    printf("After XOR swap: a = %d, b = %d\n", a, b);
    
    // Find the single number in array where all others appear twice
    int array[] = {4, 1, 2, 1, 2, 3, 4};
    int array_size = sizeof(array) / sizeof(array[0]);
    int single = 0;
    
    for (int i = 0; i < array_size; i++) {
        single ^= array[i];
    }
    printf("Single number in array: %d\n", single);
    
    // Check if a number is a palindrome in binary
    uint32_t palindrome_test = 0b10011001;  // 153 in decimal
    uint32_t reversed_bits = reverse_bits(palindrome_test);
    printf("Number %u is %sa binary palindrome\n", palindrome_test,
           (palindrome_test == reversed_bits) ? "" : "not ");
    
    printf("\nAdvanced applications:\n");
    printf("- Cryptographic algorithms\n");
    printf("- Error detection and correction codes\n");
    printf("- Compression algorithms\n");
    printf("- Graphics and image processing\n");
    printf("- Network protocol implementations\n");
    printf("- Embedded systems programming\n\n");
}

// Utility function implementations
void print_binary(uint32_t value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%c", (value & (1U << i)) ? '1' : '0');
    }
}

void print_binary_8(uint8_t value) {
    print_binary(value, 8);
}

void print_binary_16(uint16_t value) {
    print_binary(value, 16);
}

void print_binary_32(uint32_t value) {
    for (int i = 31; i >= 0; i--) {
        printf("%c", (value & (1U << i)) ? '1' : '0');
        if (i % 8 == 0 && i > 0) printf(" ");
    }
}

int count_set_bits(uint32_t value) {
    int count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

int count_set_bits_fast(uint32_t value) {
    // Brian Kernighan's algorithm
    int count = 0;
    while (value) {
        value &= value - 1;  // Clear the lowest set bit
        count++;
    }
    return count;
}

uint32_t reverse_bits(uint32_t value) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (value & 1);
        value >>= 1;
    }
    return result;
}

int find_first_set_bit(uint32_t value) {
    if (value == 0) return -1;
    
    int position = 0;
    while ((value & 1) == 0) {
        value >>= 1;
        position++;
    }
    return position;
}

int is_power_of_two(uint32_t value) {
    return value != 0 && (value & (value - 1)) == 0;
}

uint32_t next_power_of_two(uint32_t value) {
    if (value == 0) return 1;
    
    value--;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value++;
    
    return value;
}