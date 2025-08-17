#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "config.h"

// Student structure
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    double gpa;
} Student;

// Student manager structure (opaque)
typedef struct StudentManager StudentManager;

// Constructor and destructor
StudentManager* create_student_manager(void);
void destroy_student_manager(StudentManager* manager);

// Student management functions
int add_student(StudentManager* manager, int id, const char* name, double gpa);
int remove_student(StudentManager* manager, int id);
Student* find_student(StudentManager* manager, int id);
int update_student_gpa(StudentManager* manager, int id, double new_gpa);
int get_student_count(StudentManager* manager);

// Display functions
void display_student(const Student* student);
void display_all_students(StudentManager* manager);

// Statistics functions
double calculate_average_gpa(StudentManager* manager);
double calculate_highest_gpa(StudentManager* manager);
double calculate_lowest_gpa(StudentManager* manager);
Student* find_student_with_highest_gpa(StudentManager* manager);
Student* find_student_with_lowest_gpa(StudentManager* manager);

// Sorting functions
void sort_students_by_id(StudentManager* manager);
void sort_students_by_name(StudentManager* manager);
void sort_students_by_gpa(StudentManager* manager);

// File I/O functions
int save_students_to_file(StudentManager* manager, const char* filename);
int load_students_from_file(StudentManager* manager, const char* filename);

// Utility functions
void clear_all_students(StudentManager* manager);
int is_valid_gpa(double gpa);
int is_valid_student_id(int id);

#endif // STUDENT_MANAGER_H