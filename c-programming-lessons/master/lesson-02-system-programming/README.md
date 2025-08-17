# System Programming Lesson

## Overview

This lesson explores system programming concepts, demonstrating how C programs interact with the operating system through system calls and low-level APIs. You'll learn to manage processes, handle files at the system level, work with environment variables, and understand inter-process communication.

## Learning Objectives

- Understand system calls and their role in operating system interaction
- Learn process management and creation techniques
- Master low-level file operations and permissions
- Work with environment variables and command-line arguments
- Implement signal handling and inter-process communication
- Explore system information and resource monitoring

## Concepts Covered

### 1. Process Management

#### Process Information
Every running program is a process with unique characteristics:
- **Process ID (PID)**: Unique identifier for each process
- **Parent Process ID (PPID)**: ID of the process that created this process
- **User ID (UID)**: Owner of the process
- **Group ID (GID)**: Group ownership of the process
- **Effective IDs**: IDs used for permission checking

#### Process Creation (UNIX/Linux)
- **fork()**: Creates an exact copy of the current process
- **exec() family**: Replaces current process image with new program
- **wait()**: Parent process waits for child completion
- **exit()**: Terminates process with status code

### 2. System Calls vs Library Functions

#### System Calls
Direct interface to kernel services:
- **open()**, **read()**, **write()**, **close()**: File operations
- **fork()**, **exec()**, **wait()**: Process management
- **kill()**, **signal()**: Signal handling
- **mkdir()**, **rmdir()**, **chdir()**: Directory operations

#### Library Functions
Higher-level wrappers around system calls:
- **fopen()**, **fread()**, **fwrite()**, **fclose()**: Buffered I/O
- **printf()**, **scanf()**: Formatted I/O
- **malloc()**, **free()**: Memory management
- **system()**: Execute shell commands

### 3. File System Operations

#### Low-Level File I/O
System calls provide direct access to files:
- **File Descriptors**: Integer handles representing open files
- **Unbuffered I/O**: Direct kernel interaction without buffering
- **Atomic Operations**: Guaranteed to complete without interruption
- **Error Handling**: Direct errno setting for error reporting

#### File Permissions and Access
UNIX-style permission system:
- **Owner, Group, Other**: Three permission categories
- **Read, Write, Execute**: Three permission types
- **Octal Notation**: Numeric representation (e.g., 0755)
- **Access Testing**: Check permissions before operations

### 4. Environment and Arguments

#### Command-Line Arguments
- **argc**: Argument count including program name
- **argv[]**: Array of argument strings
- **argv[0]**: Program name (by convention)
- **Argument Parsing**: Processing command-line options

#### Environment Variables
- **getenv()**: Retrieve environment variable value
- **setenv()**: Set environment variable
- **unsetenv()**: Remove environment variable
- **environ**: Global array of all environment variables

### 5. Signal Handling

#### Signal Concepts
Signals are software interrupts for process communication:
- **SIGINT**: Interrupt signal (Ctrl+C)
- **SIGTERM**: Termination request
- **SIGUSR1/SIGUSR2**: User-defined signals
- **SIGKILL**: Uncatchable termination signal

#### Signal Handling Strategies
- **Default Action**: System-defined behavior
- **Ignore Signal**: SIG_IGN handler
- **Custom Handler**: User-defined function
- **Signal Masks**: Block/unblock signals

### 6. Inter-Process Communication (IPC)

#### Basic IPC Methods
- **Signals**: Simple notification mechanism
- **Pipes**: Unidirectional data flow between processes
- **Named Pipes (FIFOs)**: Persistent pipes with filesystem names
- **Shared Memory**: Direct memory sharing between processes
- **Message Queues**: Structured message passing

## Code Structure

### Main Components

1. **Process Information**: Demonstrates process identification and user context
2. **Command-Line Processing**: Shows argument handling and parsing
3. **Environment Management**: Environment variable manipulation
4. **File Operations**: Low-level file I/O and permission management
5. **Directory Operations**: Directory creation, navigation, and cleanup
6. **System Commands**: Executing external programs
7. **Process Creation**: Fork/exec pattern for new processes
8. **Signal Handling**: Asynchronous event handling

### Key System Calls Demonstrated

```c
// Process management
pid_t getpid(void);                    // Get process ID
pid_t fork(void);                      // Create child process
int execl(const char *path, ...);      // Execute program
int wait(int *status);                 // Wait for child

// File operations
int open(const char *path, int flags); // Open file
ssize_t read(int fd, void *buf, size_t count);  // Read from file
ssize_t write(int fd, const void *buf, size_t count); // Write to file
int close(int fd);                     // Close file

// Directory operations
int mkdir(const char *path, mode_t mode); // Create directory
int chdir(const char *path);           // Change directory
int rmdir(const char *path);           // Remove directory

// Signal handling
void (*signal(int sig, void (*func)(int)))(int); // Set signal handler
int kill(pid_t pid, int sig);          // Send signal to process
```

## Platform Considerations

### POSIX Compatibility
This lesson focuses on POSIX-compliant system calls that work on:
- **Linux**: Full POSIX support
- **macOS**: POSIX-compliant with some extensions
- **Unix variants**: Generally compatible
- **Windows**: Limited support, requires POSIX layer or WSL

### Windows Alternatives
Windows provides equivalent functionality through different APIs:
- **CreateProcess()** instead of fork()/exec()
- **Windows Events** instead of signals
- **Windows API file functions** instead of POSIX file operations
- **Registry** instead of environment variables (partially)

## Compilation and Execution

```bash
# Standard compilation
make

# Run the program
make run

# Run with command-line arguments
./system_programming arg1 arg2 "argument with spaces"

# Debug version
make debug

# Clean compiled files
make clean
```

## Expected Output

The program demonstrates:

1. **Process Information**: Current PID, PPID, user/group IDs, working directory
2. **Command-Line Arguments**: Display all arguments passed to program
3. **Environment Variables**: Show and modify environment variables
4. **File Operations**: Create, write, read, and delete files using system calls
5. **File Permissions**: Test and modify file access permissions
6. **Directory Operations**: Create, navigate, and remove directories
7. **System Commands**: Execute external commands and capture results
8. **Process Creation**: Fork child processes and execute new programs (UNIX/Linux)
9. **Signal Handling**: Install signal handlers and demonstrate signal processing

## Advanced Topics

### Process Groups and Sessions
- **Process Groups**: Related processes grouped together
- **Session Leaders**: Processes that control terminal sessions
- **Job Control**: Background/foreground process management
- **Daemon Processes**: Background services without controlling terminal

### Advanced IPC Mechanisms
- **System V IPC**: Message queues, semaphores, shared memory
- **POSIX IPC**: Modern alternatives to System V IPC
- **Sockets**: Network and local inter-process communication
- **Memory-Mapped Files**: Map files directly into process memory

### System Programming Best Practices
- **Error Checking**: Always check system call return values
- **Resource Cleanup**: Close file descriptors, free memory
- **Signal Safety**: Use async-signal-safe functions in handlers
- **Race Condition Prevention**: Proper synchronization techniques

## Security Considerations

### Privilege Management
- **Principle of Least Privilege**: Run with minimum required permissions
- **setuid/setgid Programs**: Special permission handling
- **Capability Systems**: Fine-grained permission control
- **Sandboxing**: Restrict process capabilities

### Input Validation
- **Command Injection**: Sanitize system() arguments
- **Path Traversal**: Validate file paths
- **Buffer Overflows**: Check buffer boundaries
- **Format String Attacks**: Validate format strings

## Common Pitfalls

1. **Forgetting Error Checking**: Always check system call return values
2. **Resource Leaks**: Close file descriptors and free allocated memory
3. **Race Conditions**: Proper synchronization in multi-process programs
4. **Signal Handler Safety**: Use only async-signal-safe functions
5. **Zombie Processes**: Always wait() for child processes
6. **Path Assumptions**: Don't assume specific file system layouts
7. **Endianness Issues**: Consider byte order in network communication

## Debugging System Programs

### Tools and Techniques
- **strace/truss**: Trace system calls
- **gdb**: Debug with system call awareness
- **valgrind**: Memory error detection
- **lsof**: List open files and processes
- **ps/top**: Process monitoring
- **netstat**: Network connection monitoring

### Common Debugging Scenarios
- **File Descriptor Leaks**: Too many open files
- **Permission Denied**: Incorrect file permissions
- **Process Hangs**: Deadlocks or infinite waits
- **Signal Issues**: Unexpected signal behavior
- **Memory Corruption**: Invalid pointer access

## Further Reading

- "Advanced Programming in the UNIX Environment" by W. Richard Stevens
- "The Linux Programming Interface" by Michael Kerrisk
- "Systems Programming in C" by Adam Hoover
- POSIX.1-2008 Standard documentation
- Linux man pages (man 2 syscall_name)

## Exercises

1. **Process Tree**: Write a program that displays the process hierarchy
2. **File Monitor**: Create a program that monitors file changes
3. **Simple Shell**: Implement a basic command-line interpreter
4. **Signal Logger**: Log all received signals with timestamps
5. **Directory Walker**: Recursively traverse directory structures
6. **Process Communication**: Implement parent-child communication using pipes