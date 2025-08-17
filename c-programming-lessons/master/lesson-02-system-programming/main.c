/*
 * System Programming Lesson
 * Demonstrates system calls and low-level programming concepts
 * 
 * This lesson covers:
 * - Process management and system interaction
 * - File system operations and permissions
 * - Environment variables and command-line arguments
 * - Signal handling and inter-process communication
 * - System information and resource monitoring
 * 
 * Note: This lesson focuses on POSIX-compatible system calls
 * Some features may require additional setup on Windows
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #include <process.h>
    #include <io.h>
    #include <direct.h>
    #define getpid _getpid
    #define sleep(x) Sleep((x) * 1000)
    #define mkdir(path) _mkdir(path)
    #define rmdir(path) _rmdir(path)
    #define chdir(path) _chdir(path)
    #define getcwd(buf, size) _getcwd(buf, size)
    #define access(path, mode) _access(path, mode)
    #define unlink(path) _unlink(path)
#else
    #include <sys/wait.h>
    #include <signal.h>
    #include <pwd.h>
    #include <grp.h>
#endif

// Function prototypes
void demonstrate_process_info(void);
void demonstrate_file_operations(void);
void demonstrate_environment_variables(void);
void demonstrate_command_line_args(int argc, char *argv[]);
void demonstrate_system_calls(void);
void demonstrate_file_permissions(void);
void demonstrate_directory_operations(void);

#ifndef _WIN32
void demonstrate_process_creation(void);
void demonstrate_signal_handling(void);
void signal_handler(int signum);
#endif

// Global variable for signal handling demonstration
volatile int signal_received = 0;

int main(int argc, char *argv[]) {
    printf("=== System Programming Lesson ===\n\n");
    
    printf("This lesson demonstrates low-level system programming concepts\n");
    printf("including process management, file operations, and system calls.\n\n");
    
    // Demonstrate various system programming concepts
    demonstrate_process_info();
    demonstrate_command_line_args(argc, argv);
    demonstrate_environment_variables();
    demonstrate_file_operations();
    demonstrate_file_permissions();
    demonstrate_directory_operations();
    demonstrate_system_calls();
    
#ifndef _WIN32
    // These features are primarily POSIX-specific
    demonstrate_process_creation();
    demonstrate_signal_handling();
#else
    printf("Note: Some advanced features (process creation, signals) are\n");
    printf("demonstrated in POSIX environments. Windows equivalents exist\n");
    printf("but use different APIs (CreateProcess, Windows Events, etc.)\n\n");
#endif
    
    printf("=== System Programming Lesson Complete ===\n");
    return 0;
}

void demonstrate_process_info(void) {
    printf("1. PROCESS INFORMATION\n");
    printf("======================\n\n");
    
    // Get process ID
    pid_t pid = getpid();
    printf("Current Process ID (PID): %d\n", (int)pid);
    
#ifndef _WIN32
    // Get parent process ID
    pid_t ppid = getppid();
    printf("Parent Process ID (PPID): %d\n", (int)ppid);
    
    // Get user and group IDs
    uid_t uid = getuid();
    gid_t gid = getgid();
    printf("User ID (UID): %d\n", (int)uid);
    printf("Group ID (GID): %d\n", (int)gid);
    
    // Get effective user and group IDs
    uid_t euid = geteuid();
    gid_t egid = getegid();
    printf("Effective User ID (EUID): %d\n", (int)euid);
    printf("Effective Group ID (EGID): %d\n", (int)egid);
    
    // Get user information
    struct passwd *pw = getpwuid(uid);
    if (pw != NULL) {
        printf("Username: %s\n", pw->pw_name);
        printf("Home Directory: %s\n", pw->pw_dir);
        printf("Shell: %s\n", pw->pw_shell);
    }
#endif
    
    // Get current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current Working Directory: %s\n", cwd);
    } else {
        perror("getcwd failed");
    }
    
    printf("\n");
}

void demonstrate_command_line_args(int argc, char *argv[]) {
    printf("2. COMMAND LINE ARGUMENTS\n");
    printf("=========================\n\n");
    
    printf("Number of arguments: %d\n", argc);
    printf("Arguments:\n");
    
    for (int i = 0; i < argc; i++) {
        printf("  argv[%d]: \"%s\"\n", i, argv[i]);
    }
    
    printf("\nTip: Run this program with additional arguments to see them here!\n");
    printf("Example: ./system_programming arg1 arg2 \"argument with spaces\"\n\n");
}

void demonstrate_environment_variables(void) {
    printf("3. ENVIRONMENT VARIABLES\n");
    printf("========================\n\n");
    
    // Access common environment variables
    char *path = getenv("PATH");
    char *home = getenv("HOME");
    char *user = getenv("USER");
    
#ifdef _WIN32
    if (home == NULL) home = getenv("USERPROFILE");
    if (user == NULL) user = getenv("USERNAME");
#endif
    
    printf("PATH: %s\n", path ? path : "Not set");
    printf("HOME: %s\n", home ? home : "Not set");
    printf("USER: %s\n", user ? user : "Not set");
    
    // Set a custom environment variable
#ifdef _WIN32
    if (_putenv("CUSTOM_VAR=Hello from C!") == 0) {
        printf("CUSTOM_VAR: %s\n", getenv("CUSTOM_VAR"));
    } else {
        perror("_putenv failed");
    }
    
    // Demonstrate environment variable modification
    printf("\nModifying environment variable...\n");
    if (_putenv("CUSTOM_VAR=Modified value") == 0) {
        printf("CUSTOM_VAR (modified): %s\n", getenv("CUSTOM_VAR"));
    }
    
    // Remove environment variable (Windows style)
    if (_putenv("CUSTOM_VAR=") == 0) {
        printf("CUSTOM_VAR (after unset): %s\n", 
               getenv("CUSTOM_VAR") ? getenv("CUSTOM_VAR") : "Not set");
    }
#else
    if (setenv("CUSTOM_VAR", "Hello from C!", 1) == 0) {
        printf("CUSTOM_VAR: %s\n", getenv("CUSTOM_VAR"));
    } else {
        perror("setenv failed");
    }
    
    // Demonstrate environment variable modification
    printf("\nModifying environment variable...\n");
    if (setenv("CUSTOM_VAR", "Modified value", 1) == 0) {
        printf("CUSTOM_VAR (modified): %s\n", getenv("CUSTOM_VAR"));
    }
    
    // Remove environment variable
    if (unsetenv("CUSTOM_VAR") == 0) {
        printf("CUSTOM_VAR (after unset): %s\n", 
               getenv("CUSTOM_VAR") ? getenv("CUSTOM_VAR") : "Not set");
    }
#endif
    
    printf("\n");
}

void demonstrate_file_operations(void) {
    printf("4. LOW-LEVEL FILE OPERATIONS\n");
    printf("============================\n\n");
    
    const char *filename = "system_test.txt";
    const char *data = "Hello from system programming!\nThis is a test file.\n";
    
    // Create and write to file using system calls
    printf("Creating file: %s\n", filename);
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return;
    }
    
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return;
    }
    
    printf("Wrote %zd bytes to file\n", bytes_written);
    close(fd);
    
    // Read from file using system calls
    printf("Reading file: %s\n", filename);
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        return;
    }
    
    char buffer[256];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read failed");
        close(fd);
        return;
    }
    
    buffer[bytes_read] = '\0'; // Null-terminate
    printf("Read %zd bytes:\n%s", bytes_read, buffer);
    close(fd);
    
    // Get file information
    struct stat file_stat;
    if (stat(filename, &file_stat) == 0) {
        printf("\nFile information:\n");
        printf("  Size: %ld bytes\n", (long)file_stat.st_size);
        printf("  Mode: %o\n", file_stat.st_mode & 0777);
        printf("  Last modified: %s", ctime(&file_stat.st_mtime));
    } else {
        perror("stat failed");
    }
    
    // Clean up
    if (unlink(filename) == 0) {
        printf("File deleted successfully\n");
    } else {
        perror("unlink failed");
    }
    
    printf("\n");
}

void demonstrate_file_permissions(void) {
    printf("5. FILE PERMISSIONS AND ACCESS\n");
    printf("==============================\n\n");
    
    const char *test_file = "permission_test.txt";
    
    // Create a test file
    int fd = open(test_file, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open failed");
        return;
    }
    write(fd, "Permission test\n", 16);
    close(fd);
    
    // Check file access permissions
    printf("Testing file access permissions for: %s\n", test_file);
    
    if (access(test_file, F_OK) == 0) {
        printf("  File exists: YES\n");
    } else {
        printf("  File exists: NO\n");
    }
    
    if (access(test_file, R_OK) == 0) {
        printf("  Readable: YES\n");
    } else {
        printf("  Readable: NO\n");
    }
    
    if (access(test_file, W_OK) == 0) {
        printf("  Writable: YES\n");
    } else {
        printf("  Writable: NO\n");
    }
    
    if (access(test_file, X_OK) == 0) {
        printf("  Executable: YES\n");
    } else {
        printf("  Executable: NO\n");
    }
    
    // Change file permissions
    printf("\nChanging file permissions to read-only...\n");
    if (chmod(test_file, 0444) == 0) {
        printf("Permissions changed successfully\n");
        
        // Test write access after permission change
        if (access(test_file, W_OK) == 0) {
            printf("  Writable after chmod: YES\n");
        } else {
            printf("  Writable after chmod: NO\n");
        }
    } else {
        perror("chmod failed");
    }
    
    // Clean up
    chmod(test_file, 0644); // Restore write permission for deletion
    unlink(test_file);
    
    printf("\n");
}

void demonstrate_directory_operations(void) {
    printf("6. DIRECTORY OPERATIONS\n");
    printf("=======================\n\n");
    
    const char *test_dir = "test_directory";
    
    // Create directory
    printf("Creating directory: %s\n", test_dir);
#ifdef _WIN32
    if (mkdir(test_dir) == 0) {
#else
    if (mkdir(test_dir, 0755) == 0) {
#endif
        printf("Directory created successfully\n");
    } else {
        if (errno == EEXIST) {
            printf("Directory already exists\n");
        } else {
            perror("mkdir failed");
            return;
        }
    }
    
    // Change to the new directory
    char original_cwd[1024];
    if (getcwd(original_cwd, sizeof(original_cwd)) == NULL) {
        perror("getcwd failed");
        return;
    }
    
    printf("Changing to directory: %s\n", test_dir);
    if (chdir(test_dir) == 0) {
        char new_cwd[1024];
        if (getcwd(new_cwd, sizeof(new_cwd)) != NULL) {
            printf("Current directory: %s\n", new_cwd);
        }
        
        // Create a file in the new directory
        int fd = open("test_file.txt", O_CREAT | O_WRONLY, 0644);
        if (fd != -1) {
            write(fd, "File in subdirectory\n", 21);
            close(fd);
            printf("Created file in subdirectory\n");
        }
        
        // Return to original directory
        if (chdir(original_cwd) == 0) {
            printf("Returned to original directory\n");
        }
    } else {
        perror("chdir failed");
    }
    
    // Clean up
    char cleanup_path[1024];
    snprintf(cleanup_path, sizeof(cleanup_path), "%s/test_file.txt", test_dir);
    unlink(cleanup_path);
    
    if (rmdir(test_dir) == 0) {
        printf("Directory removed successfully\n");
    } else {
        perror("rmdir failed");
    }
    
    printf("\n");
}

void demonstrate_system_calls(void) {
    printf("7. SYSTEM CALLS AND COMMANDS\n");
    printf("============================\n\n");
    
    // Execute system commands
    printf("Executing system commands:\n");
    
    // Get current date and time
    printf("Current date and time:\n");
    int result = system("date");
    if (result == -1) {
        printf("  Command failed or not available\n");
    }
    
    // List current directory contents
    printf("\nCurrent directory contents:\n");
#ifdef _WIN32
    result = system("dir");
#else
    result = system("ls -la");
#endif
    if (result == -1) {
        printf("  Command failed\n");
    }
    
    // Demonstrate system() return value
    printf("\nTesting command return values:\n");
    result = system("echo 'Hello from system command'");
    printf("Command return value: %d\n", result);
    
    // Test a command that should fail
    result = system("nonexistent_command_12345");
    printf("Failed command return value: %d\n", result);
    
    printf("\n");
}

#ifndef _WIN32
void demonstrate_process_creation(void) {
    printf("8. PROCESS CREATION (UNIX/Linux)\n");
    printf("================================\n\n");
    
    printf("Creating child process with fork()...\n");
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return;
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d, Parent PID: %d)\n", 
               (int)getpid(), (int)getppid());
        printf("Child process executing 'ps' command:\n");
        execl("/bin/ps", "ps", "-f", NULL);
        // If execl returns, it failed
        perror("execl failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent process (PID: %d, Child PID: %d)\n", 
               (int)getpid(), (int)pid);
        
        int status;
        printf("Parent waiting for child to complete...\n");
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally\n");
        }
    }
    
    printf("\n");
}

void signal_handler(int signum) {
    printf("\nSignal %d received!\n", signum);
    signal_received = signum;
}

void demonstrate_signal_handling(void) {
    printf("9. SIGNAL HANDLING (UNIX/Linux)\n");
    printf("===============================\n\n");
    
    printf("Setting up signal handlers...\n");
    
    // Set up signal handlers
    signal(SIGINT, signal_handler);   // Ctrl+C
    signal(SIGTERM, signal_handler);  // Termination request
    signal(SIGUSR1, signal_handler);  // User-defined signal 1
    
    printf("Signal handlers installed for SIGINT, SIGTERM, and SIGUSR1\n");
    printf("Sending SIGUSR1 signal to self...\n");
    
    // Send signal to self
    kill(getpid(), SIGUSR1);
    
    // Give signal handler time to execute
    sleep(1);
    
    if (signal_received == SIGUSR1) {
        printf("SIGUSR1 signal was successfully handled!\n");
    }
    
    printf("Try pressing Ctrl+C to test SIGINT handler\n");
    printf("Waiting 3 seconds for potential signals...\n");
    
    // Reset signal received flag
    signal_received = 0;
    
    // Wait for potential signals
    for (int i = 3; i > 0; i--) {
        printf("  %d...\n", i);
        sleep(1);
        if (signal_received) {
            printf("Signal %d was caught during wait!\n", signal_received);
            break;
        }
    }
    
    if (!signal_received) {
        printf("No signals received during wait period\n");
    }
    
    // Restore default signal handlers
    signal(SIGINT, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
    signal(SIGUSR1, SIG_DFL);
    
    printf("Signal handlers restored to default\n");
    printf("\n");
}
#endif