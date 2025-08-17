#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void demonstrate_basic_file_operations(void);
void demonstrate_text_file_reading(void);
void demonstrate_text_file_writing(void);
void demonstrate_file_append(void);
void demonstrate_binary_file_operations(void);
void demonstrate_file_positioning(void);
void demonstrate_error_handling(void);
void create_sample_files(void);

int main() {
    printf("=== Basic File I/O in C ===\n\n");
    
    // Create sample files for demonstration
    create_sample_files();
    
    // 1. Basic file operations
    printf("1. Basic File Operations:\n");
    demonstrate_basic_file_operations();
    printf("\n");
    
    // 2. Text file reading
    printf("2. Text File Reading:\n");
    demonstrate_text_file_reading();
    printf("\n");
    
    // 3. Text file writing
    printf("3. Text File Writing:\n");
    demonstrate_text_file_writing();
    printf("\n");
    
    // 4. File append operations
    printf("4. File Append Operations:\n");
    demonstrate_file_append();
    printf("\n");
    
    // 5. Binary file operations
    printf("5. Binary File Operations:\n");
    demonstrate_binary_file_operations();
    printf("\n");
    
    // 6. File positioning
    printf("6. File Positioning:\n");
    demonstrate_file_positioning();
    printf("\n");
    
    // 7. Error handling
    printf("7. Error Handling:\n");
    demonstrate_error_handling();
    printf("\n");
    
    printf("=== End of Basic File I/O Lesson ===\n");
    return 0;
}

void create_sample_files(void) {
    // Create a sample text file
    FILE *file = fopen("sample.txt", "w");
    if (file != NULL) {
        fprintf(file, "This is line 1\n");
        fprintf(file, "This is line 2\n");
        fprintf(file, "This is line 3\n");
        fprintf(file, "Numbers: 42 3.14 100\n");
        fprintf(file, "End of sample file\n");
        fclose(file);
    }
    
    // Create a sample data file with numbers
    file = fopen("numbers.txt", "w");
    if (file != NULL) {
        for (int i = 1; i <= 10; i++) {
            fprintf(file, "%d\n", i * i);
        }
        fclose(file);
    }
}

void demonstrate_basic_file_operations(void) {
    FILE *file;
    
    // Opening a file for reading
    file = fopen("sample.txt", "r");
    if (file == NULL) {
        printf("   Error: Could not open sample.txt for reading\n");
        return;
    }
    
    printf("   File opened successfully for reading\n");
    printf("   File pointer address: %p\n", (void*)file);
    
    // Check if we're at end of file
    if (feof(file)) {
        printf("   At end of file: Yes\n");
    } else {
        printf("   At end of file: No\n");
    }
    
    // Close the file
    int close_result = fclose(file);
    if (close_result == 0) {
        printf("   File closed successfully\n");
    } else {
        printf("   Error closing file\n");
    }
}

void demonstrate_text_file_reading(void) {
    FILE *file = fopen("sample.txt", "r");
    if (file == NULL) {
        printf("   Error: Could not open sample.txt\n");
        return;
    }
    
    printf("   Reading file character by character:\n");
    int ch;
    int char_count = 0;
    while ((ch = fgetc(file)) != EOF && char_count < 50) {  // Limit output
        if (ch == '\n') {
            printf("\\n");
        } else if (ch == '\t') {
            printf("\\t");
        } else {
            printf("%c", ch);
        }
        char_count++;
    }
    printf("...\n");
    
    // Reset file pointer to beginning
    rewind(file);
    
    printf("   Reading file line by line:\n");
    char line[256];
    int line_number = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("   Line %d: %s", line_number, line);
        line_number++;
    }
    
    // Reset and read formatted data
    rewind(file);
    printf("   Skipping to numbers line and reading formatted data:\n");
    char buffer[100];
    int number;
    float decimal;
    int integer;
    
    // Skip first three lines
    for (int i = 0; i < 3; i++) {
        fgets(buffer, sizeof(buffer), file);
    }
    
    // Read formatted data from the numbers line
    if (fscanf(file, "Numbers: %d %f %d", &number, &decimal, &integer) == 3) {
        printf("   Read numbers: %d, %.2f, %d\n", number, decimal, integer);
    }
    
    fclose(file);
}

void demonstrate_text_file_writing(void) {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("   Error: Could not create output.txt\n");
        return;
    }
    
    printf("   Writing to output.txt...\n");
    
    // Write using fprintf
    fprintf(file, "File I/O Demonstration\n");
    fprintf(file, "======================\n");
    fprintf(file, "Integer: %d\n", 42);
    fprintf(file, "Float: %.2f\n", 3.14159);
    fprintf(file, "String: %s\n", "Hello, File!");
    
    // Write using fputs
    fputs("This line written with fputs\n", file);
    
    // Write using fputc
    fputs("Characters: ", file);
    for (char c = 'A'; c <= 'E'; c++) {
        fputc(c, file);
        fputc(' ', file);
    }
    fputc('\n', file);
    
    fclose(file);
    
    // Read back and display what we wrote
    printf("   Contents of output.txt:\n");
    file = fopen("output.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("   %s", line);
        }
        fclose(file);
    }
}

void demonstrate_file_append(void) {
    // First, create a base file
    FILE *file = fopen("append_demo.txt", "w");
    if (file != NULL) {
        fprintf(file, "Original content\n");
        fclose(file);
    }
    
    printf("   Original file content:\n");
    file = fopen("append_demo.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("   %s", line);
        }
        fclose(file);
    }
    
    // Now append to the file
    file = fopen("append_demo.txt", "a");
    if (file != NULL) {
        fprintf(file, "Appended line 1\n");
        fprintf(file, "Appended line 2\n");
        fprintf(file, "Final appended line\n");
        fclose(file);
    }
    
    printf("   After appending:\n");
    file = fopen("append_demo.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("   %s", line);
        }
        fclose(file);
    }
}

void demonstrate_binary_file_operations(void) {
    // Structure for binary data
    struct Student {
        int id;
        char name[50];
        float grade;
    };
    
    struct Student students[] = {
        {1, "Alice Johnson", 95.5},
        {2, "Bob Smith", 87.2},
        {3, "Carol Davis", 92.8}
    };
    
    int num_students = sizeof(students) / sizeof(students[0]);
    
    // Write binary data
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("   Error: Could not create binary file\n");
        return;
    }
    
    printf("   Writing binary data to students.dat...\n");
    size_t written = fwrite(students, sizeof(struct Student), num_students, file);
    printf("   Wrote %zu student records\n", written);
    fclose(file);
    
    // Read binary data back
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("   Error: Could not open binary file for reading\n");
        return;
    }
    
    printf("   Reading binary data from students.dat:\n");
    struct Student read_student;
    int record_num = 1;
    
    while (fread(&read_student, sizeof(struct Student), 1, file) == 1) {
        printf("   Record %d: ID=%d, Name=%s, Grade=%.1f\n", 
               record_num, read_student.id, read_student.name, read_student.grade);
        record_num++;
    }
    
    fclose(file);
}

void demonstrate_file_positioning(void) {
    FILE *file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("   Error: Could not open numbers.txt\n");
        return;
    }
    
    printf("   Demonstrating file positioning with numbers.txt:\n");
    
    // Get current position
    long pos = ftell(file);
    printf("   Initial position: %ld\n", pos);
    
    // Read first number
    int number;
    fscanf(file, "%d", &number);
    printf("   First number: %d\n", number);
    
    // Get position after reading
    pos = ftell(file);
    printf("   Position after reading first number: %ld\n", pos);
    
    // Seek to middle of file
    fseek(file, 0, SEEK_END);  // Go to end
    long file_size = ftell(file);
    printf("   File size: %ld bytes\n", file_size);
    
    fseek(file, file_size / 2, SEEK_SET);  // Go to middle
    pos = ftell(file);
    printf("   Position at middle: %ld\n", pos);
    
    // Read from middle
    if (fscanf(file, "%d", &number) == 1) {
        printf("   Number from middle: %d\n", number);
    }
    
    // Go back to beginning
    rewind(file);
    pos = ftell(file);
    printf("   Position after rewind: %ld\n", pos);
    
    // Read first few numbers
    printf("   First 5 numbers: ");
    for (int i = 0; i < 5; i++) {
        if (fscanf(file, "%d", &number) == 1) {
            printf("%d ", number);
        }
    }
    printf("\n");
    
    fclose(file);
}

void demonstrate_error_handling(void) {
    FILE *file;
    
    printf("   Testing error conditions:\n");
    
    // Try to open non-existent file for reading
    file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        perror("   Opening nonexistent.txt");
    } else {
        fclose(file);
    }
    
    // Try to open file in non-existent directory
    file = fopen("nonexistent_dir/test.txt", "w");
    if (file == NULL) {
        perror("   Creating file in nonexistent directory");
    } else {
        fclose(file);
    }
    
    // Demonstrate proper error checking
    printf("   Proper error handling example:\n");
    file = fopen("test_write.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "   Error: Could not create test_write.txt\n");
        return;
    }
    
    // Write some data
    int write_result = fprintf(file, "Test data: %d\n", 123);
    if (write_result < 0) {
        fprintf(stderr, "   Error: Could not write to file\n");
        fclose(file);
        return;
    }
    
    // Check for write errors before closing
    if (ferror(file)) {
        fprintf(stderr, "   Error: Write error detected\n");
    } else {
        printf("   File written successfully\n");
    }
    
    if (fclose(file) != 0) {
        fprintf(stderr, "   Error: Could not close file properly\n");
    } else {
        printf("   File closed successfully\n");
    }
    
    // Clean up - remove test file
    if (remove("test_write.txt") == 0) {
        printf("   Test file removed successfully\n");
    } else {
        printf("   Could not remove test file\n");
    }
}