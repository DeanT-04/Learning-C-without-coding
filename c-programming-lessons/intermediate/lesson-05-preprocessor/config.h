#ifndef CONFIG_H
#define CONFIG_H

// Configuration constants
#define VERSION_MAJOR 2
#define VERSION_MINOR 1
#define VERSION_PATCH 0

#define MAX_BUFFER_SIZE 1024
#define DEFAULT_TIMEOUT 30

// Feature flags
#define ENABLE_DEBUG 1
#define ENABLE_LOGGING 1
#define ENABLE_ADVANCED_FEATURES 0

// Platform-specific definitions
#ifdef _WIN32
    #define PLATFORM "Windows"
    #define PATH_SEPARATOR '\\'
#elif defined(__linux__)
    #define PLATFORM "Linux"
    #define PATH_SEPARATOR '/'
#elif defined(__APPLE__)
    #define PLATFORM "macOS"
    #define PATH_SEPARATOR '/'
#else
    #define PLATFORM "Unknown"
    #define PATH_SEPARATOR '/'
#endif

// Utility macros
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define VERSION_STRING TOSTRING(VERSION_MAJOR) "." TOSTRING(VERSION_MINOR) "." TOSTRING(VERSION_PATCH)

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))

// Conditional compilation helpers
#if ENABLE_DEBUG
    #define DEBUG_PRINT(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) // Empty macro when debug is disabled
#endif

#if ENABLE_LOGGING
    #define LOG_INFO(msg) printf("[INFO] %s\n", msg)
    #define LOG_ERROR(msg) printf("[ERROR] %s\n", msg)
#else
    #define LOG_INFO(msg)
    #define LOG_ERROR(msg)
#endif

#endif // CONFIG_H