#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    printf("=== C Arrays and Strings Lesson ===\n\n");
    
    // 1. Array Declaration and Initialization
    printf("1. Array Declaration and Initialization:\n");
    
    // Different ways to declare and initialize arrays
    int numbers[5] = {10, 20, 30, 40, 50};
    int values[] = {1, 2, 3, 4, 5, 6};  // Size determined by initializer
    int zeros[3] = {0};  // First element 0, rest automatically 0
    int empty[4];  // Uninitialized (contains garbage values)
    (void)empty;   // Suppress unused variable warning
    
    printf("   numbers array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("   values array: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    
    printf("   zeros array: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", zeros[i]);
    }
    printf("\n\n");
    
    // 2. Array Indexing and Manipulation
    printf("2. Array Indexing and Manipulation:\n");
    int data[5] = {100, 200, 300, 400, 500};
    
    printf("   Original array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // Modify elements
    data[0] = 999;
    data[2] = 777;
    data[4] = 555;
    
    printf("   After modification: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // Array bounds (be careful!)
    printf("   Array size: %zu elements\n", sizeof(data) / sizeof(data[0]));
    printf("   First element (index 0): %d\n", data[0]);
    printf("   Last element (index 4): %d\n\n", data[4]);
    
    // 3. Multi-dimensional Arrays
    printf("3. Multi-dimensional Arrays:\n");
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("   3x4 Matrix:\n");
    for (int row = 0; row < 3; row++) {
        printf("   ");
        for (int col = 0; col < 4; col++) {
            printf("%3d ", matrix[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    
    // 4. Arrays and Pointers Relationship
    printf("4. Arrays and Pointers Relationship:\n");
    int arr[4] = {11, 22, 33, 44};
    int *ptr = arr;  // Array name is address of first element
    
    printf("   Array name as pointer: %p\n", (void*)arr);
    printf("   Address of first element: %p\n", (void*)&arr[0]);
    printf("   Pointer value: %p\n", (void*)ptr);
    
    printf("   Accessing elements:\n");
    for (int i = 0; i < 4; i++) {
        printf("   arr[%d] = %d, *(ptr + %d) = %d, ptr[%d] = %d\n", 
               i, arr[i], i, *(ptr + i), i, ptr[i]);
    }
    printf("\n");
    
    // 5. Character Arrays and Strings
    printf("5. Character Arrays and Strings:\n");
    
    // Different ways to create strings
    char str1[20] = "Hello";  // Character array with explicit size
    char str2[] = "World";    // Size determined by string length
    char str3[10];            // Uninitialized character array
    char *str4 = "C Programming";  // String literal (read-only)
    
    printf("   str1: \"%s\" (length: %zu)\n", str1, strlen(str1));
    printf("   str2: \"%s\" (length: %zu)\n", str2, strlen(str2));
    printf("   str4: \"%s\" (length: %zu)\n", str4, strlen(str4));
    
    // Manual string creation
    strcpy(str3, "Manual");
    printf("   str3 (after strcpy): \"%s\"\n\n", str3);
    
    // 6. String Manipulation Functions
    printf("6. String Manipulation Functions:\n");
    char source[50] = "Programming";
    char destination[50];
    char buffer[100];
    
    // String copy
    strcpy(destination, source);
    printf("   After strcpy: destination = \"%s\"\n", destination);
    
    // String concatenation
    strcpy(buffer, "C ");
    strcat(buffer, source);
    printf("   After strcat: buffer = \"%s\"\n", buffer);
    
    // String comparison
    int cmp_result = strcmp("Apple", "Banana");
    printf("   strcmp(\"Apple\", \"Banana\") = %d\n", cmp_result);
    
    cmp_result = strcmp("Hello", "Hello");
    printf("   strcmp(\"Hello\", \"Hello\") = %d\n", cmp_result);
    
    // String length
    printf("   strlen(\"%s\") = %zu\n\n", buffer, strlen(buffer));
    
    // 7. Character Array Manipulation
    printf("7. Character Array Manipulation:\n");
    char text[] = "Hello World";
    printf("   Original: \"%s\"\n", text);
    
    // Access individual characters
    printf("   Individual characters: ");
    for (int i = 0; text[i] != '\0'; i++) {
        printf("'%c' ", text[i]);
    }
    printf("\n");
    
    // Modify characters
    text[6] = 'w';  // Change 'W' to 'w'
    printf("   After modification: \"%s\"\n", text);
    
    // Convert to uppercase
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = text[i] - 'a' + 'A';
        }
    }
    printf("   Uppercase: \"%s\"\n\n", text);
    
    // 8. String Input and Output
    printf("8. String Input and Output:\n");
    char user_input[100];
    
    printf("   Enter a word (no spaces): ");
    if (scanf("%99s", user_input) == 1) {  // Limit input to prevent overflow
        printf("   You entered: \"%s\"\n", user_input);
        printf("   Length: %zu characters\n", strlen(user_input));
    }
    
    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("   Enter a line (with spaces): ");
    if (fgets(user_input, sizeof(user_input), stdin) != NULL) {
        // Remove newline if present
        size_t len = strlen(user_input);
        if (len > 0 && user_input[len - 1] == '\n') {
            user_input[len - 1] = '\0';
        }
        printf("   You entered: \"%s\"\n", user_input);
        printf("   Length: %zu characters\n\n", strlen(user_input));
    }
    
    // 9. Dynamic String Arrays
    printf("9. Dynamic String Arrays:\n");
    char *languages[] = {
        "C",
        "Python", 
        "Java",
        "JavaScript",
        "Go"
    };
    
    int num_languages = sizeof(languages) / sizeof(languages[0]);
    printf("   Programming languages:\n");
    for (int i = 0; i < num_languages; i++) {
        printf("   %d. %s\n", i + 1, languages[i]);
    }
    printf("\n");
    
    // 10. Common String Operations
    printf("10. Common String Operations:\n");
    char sample[] = "  C Programming  ";
    printf("   Original: \"%s\"\n", sample);
    
    // Find character
    char *found = strchr(sample, 'P');
    if (found != NULL) {
        printf("   Found 'P' at position: %td\n", found - sample);
    }
    
    // Find substring
    char *substring = strstr(sample, "Program");
    if (substring != NULL) {
        printf("   Found \"Program\" at position: %td\n", substring - sample);
    }
    
    // Manual trim (remove leading/trailing spaces)
    char trimmed[50];
    strcpy(trimmed, sample);
    
    // Remove leading spaces
    int start = 0;
    while (trimmed[start] == ' ') start++;
    
    // Remove trailing spaces
    int end = strlen(trimmed) - 1;
    while (end >= 0 && trimmed[end] == ' ') end--;
    
    // Create trimmed string
    int j = 0;
    for (int i = start; i <= end; i++) {
        trimmed[j++] = trimmed[i];
    }
    trimmed[j] = '\0';
    
    printf("   Trimmed: \"%s\"\n", trimmed);
    
    printf("\n=== End of Arrays and Strings Lesson ===\n");
    return 0;
}