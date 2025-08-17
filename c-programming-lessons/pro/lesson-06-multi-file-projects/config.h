#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

// Project configuration constants
#define PROJECT_VERSION "1.0.0"
#define BUILD_DATE __DATE__ " " __TIME__

// Debug configuration
#ifdef DEBUG
    #define DEBUG_MODE 1
    #define DEBUG_PRINT(fmt, ...) \
        do { \
            printf("[DEBUG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        } while(0)
#else
    #define DEBUG_MODE 0
    #define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif

// Application constants
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100
#define MIN_GPA 0.0
#define MAX_GPA 4.0

// File paths
#define DEFAULT_STUDENT_FILE "students.txt"
#define LOG_FILE "application.log"

// Error codes
#define SUCCESS 0
#define ERROR_MEMORY_ALLOCATION -1
#define ERROR_FILE_NOT_FOUND -2
#define ERROR_INVALID_INPUT -3
#define ERROR_STUDENT_NOT_FOUND -4
#define ERROR_STUDENT_EXISTS -5

#endif // CONFIG_H