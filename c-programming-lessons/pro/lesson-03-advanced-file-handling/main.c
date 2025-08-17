#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Structure for binary file operations
struct Record {
    int id;
    char name[50];
    float salary;
    int age;
};

// Function prototypes
void demonstrate_binary_files(void);
void demonstrate_file_positioning(void);
void demonstrate_file_operations(void);
void demonstrate_error_handling(void);
void demonstrate_buffering(void);
void demonstrate_file_copying(void);
void demonstrate_csv_processing(void);
void cleanup_test_files(void);

int main(void) {
    printf("=== Advanced File Handling in C ===\n\n");
    
    demonstrate_binary_files();
    demonstrate_file_positioning();
    demonstrate_file_operations();
    demonstrate_error_handling();
    demonstrate_buffering();
    demonstrate_file_copying();
    demonstrate_csv_processing();
    cleanup_test_files();
    
    return 0;
}

void demonstrate_binary_files(void) {
    printf("1. Binary File Operations:\n");
    printf("--------------------------\n");
    
    // Create sample records
    struct Record employees[] = {
        {101, "Alice Johnson", 75000.50, 28},
        {102, "Bob Smith", 82000.75, 32},
        {103, "Carol Davis", 68000.00, 26},
        {104, "David Wilson", 91000.25, 35}
    };
    
    int num_employees = sizeof(employees) / sizeof(employees[0]);
    
    // Write binary data
    FILE *bin_file = fopen("employees.dat", "wb");
    if (bin_file == NULL) {
        printf("Error creating binary file: %s\n", strerror(errno));
        return;
    }
    
    // Write number of records first
    fwrite(&num_employees, sizeof(int), 1, bin_file);
    
    // Write all records
    size_t written = fwrite(employees, sizeof(struct Record), num_employees, bin_file);
    printf("Written %zu records to binary file\n", written);
    
    fclose(bin_file);
    
    // Read binary data
    bin_file = fopen("employees.dat", "rb");
    if (bin_file == NULL) {
        printf("Error opening binary file: %s\n", strerror(errno));
        return;
    }
    
    // Read number of records
    int count;
    fread(&count, sizeof(int), 1, bin_file);
    printf("Reading %d records from binary file:\n", count);
    
    // Read and display records
    struct Record temp_record;
    for (int i = 0; i < count; i++) {
        if (fread(&temp_record, sizeof(struct Record), 1, bin_file) == 1) {
            printf("ID: %d, Name: %s, Salary: $%.2f, Age: %d\n",
                   temp_record.id, temp_record.name, temp_record.salary, temp_record.age);
        }
    }
    
    fclose(bin_file);
    printf("\n");
}

void demonstrate_file_positioning(void) {
    printf("2. File Positioning and Seeking:\n");
    printf("--------------------------------\n");
    
    // Create a test file with numbered lines
    FILE *file = fopen("positions.txt", "w");
    if (file == NULL) {
        printf("Error creating position test file\n");
        return;
    }
    
    for (int i = 1; i <= 10; i++) {
        fprintf(file, "Line %02d: This is line number %d\n", i, i);
    }
    fclose(file);
    
    // Demonstrate positioning
    file = fopen("positions.txt", "r");
    if (file == NULL) {
        printf("Error opening position test file\n");
        return;
    }
    
    char buffer[100];
    
    // Read first line
    fgets(buffer, sizeof(buffer), file);
    printf("First line: %s", buffer);
    
    // Get current position
    long pos = ftell(file);
    printf("Current position: %ld bytes\n", pos);
    
    // Seek to end and get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    printf("File size: %ld bytes\n", file_size);
    
    // Seek to middle of file
    fseek(file, file_size / 2, SEEK_SET);
    printf("Seeking to middle (position %ld):\n", file_size / 2);
    fgets(buffer, sizeof(buffer), file);
    printf("Line at middle: %s", buffer);
    
    // Seek backward from current position
    fseek(file, -50, SEEK_CUR);
    printf("Seeking backward 50 bytes:\n");
    fgets(buffer, sizeof(buffer), file);
    printf("Line after backward seek: %s", buffer);
    
    // Rewind to beginning
    rewind(file);
    fgets(buffer, sizeof(buffer), file);
    printf("After rewind: %s", buffer);
    
    fclose(file);
    printf("\n");
}

void demonstrate_file_operations(void) {
    printf("3. Advanced File Operations:\n");
    printf("----------------------------\n");
    
    // Create a temporary file
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        printf("Error creating temporary file\n");
        return;
    }
    
    // Write to temporary file
    fprintf(temp_file, "This is a temporary file\n");
    fprintf(temp_file, "It will be automatically deleted\n");
    
    // Read from temporary file
    rewind(temp_file);
    char buffer[100];
    printf("Temporary file contents:\n");
    while (fgets(buffer, sizeof(buffer), temp_file) != NULL) {
        printf("  %s", buffer);
    }
    
    fclose(temp_file);  // Automatically deleted
    
    // File renaming
    FILE *rename_test = fopen("old_name.txt", "w");
    if (rename_test != NULL) {
        fprintf(rename_test, "This file will be renamed\n");
        fclose(rename_test);
        
        if (rename("old_name.txt", "new_name.txt") == 0) {
            printf("File successfully renamed from old_name.txt to new_name.txt\n");
        } else {
            printf("Error renaming file: %s\n", strerror(errno));
        }
    }
    
    // File removal
    if (remove("new_name.txt") == 0) {
        printf("File new_name.txt successfully deleted\n");
    } else {
        printf("Error deleting file: %s\n", strerror(errno));
    }
    
    printf("\n");
}

void demonstrate_error_handling(void) {
    printf("4. File Error Handling:\n");
    printf("-----------------------\n");
    
    // Attempt to open non-existent file
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        printf("Expected error opening nonexistent.txt: %s\n", strerror(errno));
    }
    
    // Create a file and demonstrate error checking
    file = fopen("error_test.txt", "w");
    if (file == NULL) {
        printf("Error creating error_test.txt: %s\n", strerror(errno));
        return;
    }
    
    // Write some data
    int items_written = fprintf(file, "Testing error handling\n");
    if (items_written < 0) {
        printf("Error writing to file\n");
    } else {
        printf("Successfully wrote %d characters\n", items_written);
    }
    
    // Check for write errors
    if (ferror(file)) {
        printf("Write error detected\n");
        clearerr(file);  // Clear error flag
    }
    
    fclose(file);
    
    // Test reading from write-only file (should fail)
    file = fopen("error_test.txt", "w");  // Open for writing only
    if (file != NULL) {
        char buffer[50];
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            if (ferror(file)) {
                printf("Expected read error from write-only file\n");
                clearerr(file);
            }
        }
        fclose(file);
    }
    
    // Clean up
    remove("error_test.txt");
    printf("\n");
}

void demonstrate_buffering(void) {
    printf("5. File Buffering Control:\n");
    printf("--------------------------\n");
    
    FILE *file = fopen("buffer_test.txt", "w");
    if (file == NULL) {
        printf("Error creating buffer test file\n");
        return;
    }
    
    // Demonstrate different buffering modes
    printf("Testing different buffer modes:\n");
    
    // Full buffering (default for files)
    setvbuf(file, NULL, _IOFBF, BUFSIZ);
    fprintf(file, "Line 1: Full buffering\n");
    printf("  Written with full buffering (may not appear in file yet)\n");
    
    // Force flush
    fflush(file);
    printf("  Forced flush - data now written to file\n");
    
    // Line buffering
    setvbuf(file, NULL, _IOLBF, BUFSIZ);
    fprintf(file, "Line 2: Line buffering\n");
    printf("  Written with line buffering (should flush automatically)\n");
    
    // No buffering
    setvbuf(file, NULL, _IONBF, 0);
    fprintf(file, "Line 3: No buffering\n");
    printf("  Written with no buffering (immediate write)\n");
    
    fclose(file);
    
    // Read and display the file
    file = fopen("buffer_test.txt", "r");
    if (file != NULL) {
        char buffer[100];
        printf("File contents:\n");
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("  %s", buffer);
        }
        fclose(file);
    }
    
    remove("buffer_test.txt");
    printf("\n");
}

void demonstrate_file_copying(void) {
    printf("6. File Copying Operations:\n");
    printf("---------------------------\n");
    
    // Create source file
    FILE *source = fopen("source.txt", "w");
    if (source == NULL) {
        printf("Error creating source file\n");
        return;
    }
    
    fprintf(source, "This is the source file content.\n");
    fprintf(source, "It contains multiple lines.\n");
    fprintf(source, "We will copy this to another file.\n");
    fclose(source);
    
    // Copy file character by character
    source = fopen("source.txt", "r");
    FILE *dest1 = fopen("copy1.txt", "w");
    
    if (source != NULL && dest1 != NULL) {
        int ch;
        int char_count = 0;
        while ((ch = fgetc(source)) != EOF) {
            fputc(ch, dest1);
            char_count++;
        }
        printf("Character-by-character copy: %d characters copied\n", char_count);
    }
    
    if (source) fclose(source);
    if (dest1) fclose(dest1);
    
    // Copy file line by line
    source = fopen("source.txt", "r");
    FILE *dest2 = fopen("copy2.txt", "w");
    
    if (source != NULL && dest2 != NULL) {
        char buffer[256];
        int line_count = 0;
        while (fgets(buffer, sizeof(buffer), source) != NULL) {
            fputs(buffer, dest2);
            line_count++;
        }
        printf("Line-by-line copy: %d lines copied\n", line_count);
    }
    
    if (source) fclose(source);
    if (dest2) fclose(dest2);
    
    // Copy file in blocks (most efficient)
    source = fopen("source.txt", "rb");
    FILE *dest3 = fopen("copy3.txt", "wb");
    
    if (source != NULL && dest3 != NULL) {
        char buffer[1024];
        size_t bytes_read, total_bytes = 0;
        
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
            fwrite(buffer, 1, bytes_read, dest3);
            total_bytes += bytes_read;
        }
        printf("Block copy: %zu bytes copied\n", total_bytes);
    }
    
    if (source) fclose(source);
    if (dest3) fclose(dest3);
    
    printf("\n");
}

void demonstrate_csv_processing(void) {
    printf("7. CSV File Processing:\n");
    printf("-----------------------\n");
    
    // Create a CSV file
    FILE *csv_file = fopen("employees.csv", "w");
    if (csv_file == NULL) {
        printf("Error creating CSV file\n");
        return;
    }
    
    // Write CSV header and data
    fprintf(csv_file, "ID,Name,Department,Salary\n");
    fprintf(csv_file, "101,\"Alice Johnson\",Engineering,75000.50\n");
    fprintf(csv_file, "102,\"Bob Smith\",Marketing,65000.00\n");
    fprintf(csv_file, "103,\"Carol Davis\",HR,58000.75\n");
    fprintf(csv_file, "104,\"David Wilson\",Engineering,82000.00\n");
    fclose(csv_file);
    
    // Read and parse CSV file
    csv_file = fopen("employees.csv", "r");
    if (csv_file == NULL) {
        printf("Error opening CSV file\n");
        return;
    }
    
    char line[256];
    int line_number = 0;
    double total_salary = 0.0;
    int employee_count = 0;
    
    printf("CSV File Contents:\n");
    while (fgets(line, sizeof(line), csv_file) != NULL) {
        line_number++;
        
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        if (line_number == 1) {
            printf("Header: %s\n", line);
            continue;
        }
        
        // Simple CSV parsing (assumes no commas in quoted fields for this example)
        char *token;
        char *line_copy = strdup(line);
        int field = 0;
        int id = 0;
        char name[50] = {0}, department[50] = {0};
        double salary = 0.0;
        
        token = strtok(line_copy, ",");
        while (token != NULL) {
            switch (field) {
                case 0: id = atoi(token); break;
                case 1: 
                    // Remove quotes if present
                    if (token[0] == '"') {
                        strcpy(name, token + 1);
                        if (name[strlen(name) - 1] == '"') {
                            name[strlen(name) - 1] = '\0';
                        }
                    } else {
                        strcpy(name, token);
                    }
                    break;
                case 2: 
                    if (token[0] == '"') {
                        strcpy(department, token + 1);
                        if (department[strlen(department) - 1] == '"') {
                            department[strlen(department) - 1] = '\0';
                        }
                    } else {
                        strcpy(department, token);
                    }
                    break;
                case 3: salary = atof(token); break;
            }
            field++;
            token = strtok(NULL, ",");
        }
        
        printf("Employee %d: ID=%d, Name=%s, Dept=%s, Salary=$%.2f\n",
               employee_count + 1, id, name, department, salary);
        
        total_salary += salary;
        employee_count++;
        free(line_copy);
    }
    
    fclose(csv_file);
    
    printf("Summary: %d employees, Average salary: $%.2f\n", 
           employee_count, total_salary / employee_count);
    printf("\n");
}

void cleanup_test_files(void) {
    printf("8. Cleaning up test files:\n");
    printf("--------------------------\n");
    
    const char *files_to_remove[] = {
        "employees.dat",
        "positions.txt", 
        "source.txt",
        "copy1.txt",
        "copy2.txt", 
        "copy3.txt",
        "employees.csv"
    };
    
    int num_files = sizeof(files_to_remove) / sizeof(files_to_remove[0]);
    int removed_count = 0;
    
    for (int i = 0; i < num_files; i++) {
        if (remove(files_to_remove[i]) == 0) {
            printf("Removed: %s\n", files_to_remove[i]);
            removed_count++;
        } else {
            printf("Could not remove: %s (may not exist)\n", files_to_remove[i]);
        }
    }
    
    printf("Cleanup complete: %d files removed\n", removed_count);
}