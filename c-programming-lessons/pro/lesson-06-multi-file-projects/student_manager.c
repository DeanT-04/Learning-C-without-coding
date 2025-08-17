#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_manager.h"
#include "config.h"

// Student manager implementation
struct StudentManager {
    Student students[MAX_STUDENTS];
    int count;
    int capacity;
};

// Constructor and destructor
StudentManager* create_student_manager(void) {
    DEBUG_PRINT("Creating student manager");
    StudentManager* manager = malloc(sizeof(StudentManager));
    if (manager == NULL) {
        DEBUG_PRINT("Failed to allocate memory for student manager");
        return NULL;
    }
    
    manager->count = 0;
    manager->capacity = MAX_STUDENTS;
    
    DEBUG_PRINT("Student manager created successfully");
    return manager;
}

void destroy_student_manager(StudentManager* manager) {
    DEBUG_PRINT("Destroying student manager");
    if (manager != NULL) {
        free(manager);
        DEBUG_PRINT("Student manager destroyed");
    }
}

// Student management functions
int add_student(StudentManager* manager, int id, const char* name, double gpa) {
    DEBUG_PRINT("Adding student: ID=%d, Name=%s, GPA=%.2f", id, name, gpa);
    
    if (manager == NULL || name == NULL) {
        DEBUG_PRINT("Invalid parameters for add_student");
        return ERROR_INVALID_INPUT;
    }
    
    if (manager->count >= manager->capacity) {
        DEBUG_PRINT("Student manager is full");
        return ERROR_MEMORY_ALLOCATION;
    }
    
    if (!is_valid_student_id(id)) {
        DEBUG_PRINT("Invalid student ID: %d", id);
        return ERROR_INVALID_INPUT;
    }
    
    if (!is_valid_gpa(gpa)) {
        DEBUG_PRINT("Invalid GPA: %.2f", gpa);
        return ERROR_INVALID_INPUT;
    }
    
    // Check if student already exists
    if (find_student(manager, id) != NULL) {
        DEBUG_PRINT("Student with ID %d already exists", id);
        return ERROR_STUDENT_EXISTS;
    }
    
    // Add new student
    Student* new_student = &manager->students[manager->count];
    new_student->id = id;
    strncpy(new_student->name, name, MAX_NAME_LENGTH - 1);
    new_student->name[MAX_NAME_LENGTH - 1] = '\0';  // Ensure null termination
    new_student->gpa = gpa;
    
    manager->count++;
    DEBUG_PRINT("Student added successfully. Total students: %d", manager->count);
    return SUCCESS;
}

int remove_student(StudentManager* manager, int id) {
    DEBUG_PRINT("Removing student with ID: %d", id);
    
    if (manager == NULL) {
        DEBUG_PRINT("Invalid manager parameter");
        return ERROR_INVALID_INPUT;
    }
    
    // Find student index
    int index = -1;
    for (int i = 0; i < manager->count; i++) {
        if (manager->students[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        DEBUG_PRINT("Student with ID %d not found", id);
        return ERROR_STUDENT_NOT_FOUND;
    }
    
    // Shift remaining students
    for (int i = index; i < manager->count - 1; i++) {
        manager->students[i] = manager->students[i + 1];
    }
    
    manager->count--;
    DEBUG_PRINT("Student removed successfully. Total students: %d", manager->count);
    return SUCCESS;
}

Student* find_student(StudentManager* manager, int id) {
    DEBUG_PRINT("Finding student with ID: %d", id);
    
    if (manager == NULL) {
        DEBUG_PRINT("Invalid manager parameter");
        return NULL;
    }
    
    for (int i = 0; i < manager->count; i++) {
        if (manager->students[i].id == id) {
            DEBUG_PRINT("Student found at index %d", i);
            return &manager->students[i];
        }
    }
    
    DEBUG_PRINT("Student with ID %d not found", id);
    return NULL;
}

int update_student_gpa(StudentManager* manager, int id, double new_gpa) {
    DEBUG_PRINT("Updating GPA for student ID %d to %.2f", id, new_gpa);
    
    if (manager == NULL) {
        DEBUG_PRINT("Invalid manager parameter");
        return ERROR_INVALID_INPUT;
    }
    
    if (!is_valid_gpa(new_gpa)) {
        DEBUG_PRINT("Invalid GPA: %.2f", new_gpa);
        return ERROR_INVALID_INPUT;
    }
    
    Student* student = find_student(manager, id);
    if (student == NULL) {
        DEBUG_PRINT("Student with ID %d not found", id);
        return ERROR_STUDENT_NOT_FOUND;
    }
    
    student->gpa = new_gpa;
    DEBUG_PRINT("GPA updated to %.2f", new_gpa);
    return SUCCESS;
}

int get_student_count(StudentManager* manager) {
    if (manager == NULL) {
        DEBUG_PRINT("Invalid manager parameter");
        return 0;
    }
    
    return manager->count;
}

// Display functions
void display_student(const Student* student) {
    if (student == NULL) {
        printf("Invalid student\n");
        return;
    }
    
    printf("ID: %d, Name: %-20s, GPA: %.2f\n", 
           student->id, student->name, student->gpa);
}

void display_all_students(StudentManager* manager) {
    DEBUG_PRINT("Displaying all students");
    
    if (manager == NULL) {
        printf("Invalid student manager\n");
        return;
    }
    
    if (manager->count == 0) {
        printf("No students in the system\n");
        return;
    }
    
    printf("%-5s %-20s %-5s\n", "ID", "Name", "GPA");
    printf("%-5s %-20s %-5s\n", "---", "--------------------", "-----");
    
    for (int i = 0; i < manager->count; i++) {
        display_student(&manager->students[i]);
    }
}

// Statistics functions
double calculate_average_gpa(StudentManager* manager) {
    DEBUG_PRINT("Calculating average GPA");
    
    if (manager == NULL || manager->count == 0) {
        DEBUG_PRINT("No students for GPA calculation");
        return 0.0;
    }
    
    double total = 0.0;
    for (int i = 0; i < manager->count; i++) {
        total += manager->students[i].gpa;
    }
    
    double average = total / manager->count;
    DEBUG_PRINT("Average GPA: %.2f", average);
    return average;
}

double calculate_highest_gpa(StudentManager* manager) {
    DEBUG_PRINT("Finding highest GPA");
    
    if (manager == NULL || manager->count == 0) {
        DEBUG_PRINT("No students for highest GPA calculation");
        return 0.0;
    }
    
    double highest = manager->students[0].gpa;
    for (int i = 1; i < manager->count; i++) {
        if (manager->students[i].gpa > highest) {
            highest = manager->students[i].gpa;
        }
    }
    
    DEBUG_PRINT("Highest GPA: %.2f", highest);
    return highest;
}

double calculate_lowest_gpa(StudentManager* manager) {
    DEBUG_PRINT("Finding lowest GPA");
    
    if (manager == NULL || manager->count == 0) {
        DEBUG_PRINT("No students for lowest GPA calculation");
        return 0.0;
    }
    
    double lowest = manager->students[0].gpa;
    for (int i = 1; i < manager->count; i++) {
        if (manager->students[i].gpa < lowest) {
            lowest = manager->students[i].gpa;
        }
    }
    
    DEBUG_PRINT("Lowest GPA: %.2f", lowest);
    return lowest;
}

Student* find_student_with_highest_gpa(StudentManager* manager) {
    DEBUG_PRINT("Finding student with highest GPA");
    
    if (manager == NULL || manager->count == 0) {
        DEBUG_PRINT("No students available");
        return NULL;
    }
    
    Student* highest_student = &manager->students[0];
    for (int i = 1; i < manager->count; i++) {
        if (manager->students[i].gpa > highest_student->gpa) {
            highest_student = &manager->students[i];
        }
    }
    
    DEBUG_PRINT("Student with highest GPA: %s (%.2f)", 
                highest_student->name, highest_student->gpa);
    return highest_student;
}

Student* find_student_with_lowest_gpa(StudentManager* manager) {
    DEBUG_PRINT("Finding student with lowest GPA");
    
    if (manager == NULL || manager->count == 0) {
        DEBUG_PRINT("No students available");
        return NULL;
    }
    
    Student* lowest_student = &manager->students[0];
    for (int i = 1; i < manager->count; i++) {
        if (manager->students[i].gpa < lowest_student->gpa) {
            lowest_student = &manager->students[i];
        }
    }
    
    DEBUG_PRINT("Student with lowest GPA: %s (%.2f)", 
                lowest_student->name, lowest_student->gpa);
    return lowest_student;
}

// Comparison functions for sorting
static int compare_by_id(const void* a, const void* b) {
    const Student* student_a = (const Student*)a;
    const Student* student_b = (const Student*)b;
    return student_a->id - student_b->id;
}

static int compare_by_name(const void* a, const void* b) {
    const Student* student_a = (const Student*)a;
    const Student* student_b = (const Student*)b;
    return strcmp(student_a->name, student_b->name);
}

static int compare_by_gpa_desc(const void* a, const void* b) {
    const Student* student_a = (const Student*)a;
    const Student* student_b = (const Student*)b;
    
    if (student_a->gpa > student_b->gpa) return -1;
    if (student_a->gpa < student_b->gpa) return 1;
    return 0;
}

// Sorting functions
void sort_students_by_id(StudentManager* manager) {
    DEBUG_PRINT("Sorting students by ID");
    
    if (manager == NULL || manager->count <= 1) {
        DEBUG_PRINT("No sorting needed");
        return;
    }
    
    qsort(manager->students, manager->count, sizeof(Student), compare_by_id);
    DEBUG_PRINT("Students sorted by ID");
}

void sort_students_by_name(StudentManager* manager) {
    DEBUG_PRINT("Sorting students by name");
    
    if (manager == NULL || manager->count <= 1) {
        DEBUG_PRINT("No sorting needed");
        return;
    }
    
    qsort(manager->students, manager->count, sizeof(Student), compare_by_name);
    DEBUG_PRINT("Students sorted by name");
}

void sort_students_by_gpa(StudentManager* manager) {
    DEBUG_PRINT("Sorting students by GPA (descending)");
    
    if (manager == NULL || manager->count <= 1) {
        DEBUG_PRINT("No sorting needed");
        return;
    }
    
    qsort(manager->students, manager->count, sizeof(Student), compare_by_gpa_desc);
    DEBUG_PRINT("Students sorted by GPA");
}

// File I/O functions
int save_students_to_file(StudentManager* manager, const char* filename) {
    DEBUG_PRINT("Saving students to file: %s", filename);
    
    if (manager == NULL || filename == NULL) {
        DEBUG_PRINT("Invalid parameters for save_students_to_file");
        return ERROR_INVALID_INPUT;
    }
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        DEBUG_PRINT("Failed to open file for writing: %s", filename);
        return ERROR_FILE_NOT_FOUND;
    }
    
    // Write header
    fprintf(file, "# Student Data File\n");
    fprintf(file, "# Format: ID,Name,GPA\n");
    fprintf(file, "%d\n", manager->count);  // Number of students
    
    // Write student data
    for (int i = 0; i < manager->count; i++) {
        fprintf(file, "%d,%s,%.2f\n", 
                manager->students[i].id,
                manager->students[i].name,
                manager->students[i].gpa);
    }
    
    fclose(file);
    DEBUG_PRINT("Successfully saved %d students to file", manager->count);
    return SUCCESS;
}

int load_students_from_file(StudentManager* manager, const char* filename) {
    DEBUG_PRINT("Loading students from file: %s", filename);
    
    if (manager == NULL || filename == NULL) {
        DEBUG_PRINT("Invalid parameters for load_students_from_file");
        return ERROR_INVALID_INPUT;
    }
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        DEBUG_PRINT("Failed to open file for reading: %s", filename);
        return ERROR_FILE_NOT_FOUND;
    }
    
    char line[256];
    
    // Skip header lines
    fgets(line, sizeof(line), file);  // Skip comment line 1
    fgets(line, sizeof(line), file);  // Skip comment line 2
    
    // Read number of students
    int count;
    if (fscanf(file, "%d", &count) != 1) {
        DEBUG_PRINT("Failed to read student count from file");
        fclose(file);
        return ERROR_INVALID_INPUT;
    }
    
    DEBUG_PRINT("Loading %d students from file", count);
    
    // Clear existing students
    manager->count = 0;
    
    // Read student data
    for (int i = 0; i < count && i < MAX_STUDENTS; i++) {
        int id;
        char name[MAX_NAME_LENGTH];
        double gpa;
        
        if (fscanf(file, "%d,%49[^,],%lf", &id, name, &gpa) == 3) {
            if (add_student(manager, id, name, gpa) != SUCCESS) {
                DEBUG_PRINT("Failed to add student during file loading");
            }
        } else {
            DEBUG_PRINT("Failed to parse student data at line %d", i + 4);
        }
    }
    
    fclose(file);
    DEBUG_PRINT("Successfully loaded %d students from file", manager->count);
    return SUCCESS;
}

// Utility functions
void clear_all_students(StudentManager* manager) {
    DEBUG_PRINT("Clearing all students");
    
    if (manager != NULL) {
        manager->count = 0;
        DEBUG_PRINT("All students cleared");
    }
}

int is_valid_gpa(double gpa) {
    return (gpa >= MIN_GPA && gpa <= MAX_GPA);
}

int is_valid_student_id(int id) {
    return (id > 0 && id <= 999999);  // Reasonable range for student IDs
}