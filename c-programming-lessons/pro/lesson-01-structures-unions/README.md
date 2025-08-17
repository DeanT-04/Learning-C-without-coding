# Lesson 01: Structures and Unions

## Overview

This lesson covers C structures and unions, which are fundamental user-defined data types that allow you to group related data together. Structures store multiple values simultaneously, while unions store different data types in the same memory location.

## Key Concepts

### Structures
- **Definition**: A structure is a collection of variables of different data types grouped under a single name
- **Memory**: Each member has its own memory location
- **Usage**: Perfect for representing real-world entities with multiple attributes

### Unions
- **Definition**: A union allows storing different data types in the same memory location
- **Memory**: All members share the same memory space
- **Usage**: Useful for memory-efficient storage when only one member is used at a time

## Code Examples Explained

### 1. Basic Structure Operations

```c
struct Student {
    int id;
    char name[50];
    float gpa;
    int age;
};
```

- Defines a structure template with four members
- Each member has its own memory space
- Structure size is the sum of all member sizes (plus padding)

**Initialization Methods:**
```c
// Method 1: Initialize during declaration
struct Student student1 = {101, "Alice Johnson", 3.85, 20};

// Method 2: Assign values after declaration
struct Student student2;
student2.id = 102;
strcpy(student2.name, "Bob Smith");
```

### 2. Nested Structures

```c
struct Person {
    char name[50];
    int age;
    struct Address address;  // Nested structure
};
```

- Structures can contain other structures as members
- Access nested members using dot notation: `person.address.city`
- Useful for modeling complex relationships

### 3. Structure Pointers

```c
struct Student *ptr = &student;
```

**Two ways to access members through pointers:**
- `(*ptr).member` - Dereference first, then access
- `ptr->member` - Arrow operator (preferred method)

**Dynamic Allocation:**
```c
struct Student *dynamic_student = malloc(sizeof(struct Student));
// Remember to free(dynamic_student) when done
```

### 4. Union Operations

```c
union Data {
    int integer;
    float floating;
    char character;
    char string[20];
};
```

- All members share the same memory location
- Only one member can hold a valid value at any time
- Union size equals the size of its largest member
- Useful for memory conservation

### 5. Tagged Unions

```c
struct Record {
    int type;  // Tag to identify which union member is valid
    union Data data;
};
```

- Combines structure and union for type-safe usage
- Tag field indicates which union member contains valid data
- Prevents accessing wrong union member

## Memory Layout

### Structure Memory Layout
- Members are stored sequentially in memory
- Compiler may add padding for alignment
- Total size ≥ sum of member sizes

### Union Memory Layout
- All members start at the same memory address
- Size equals the largest member size
- Only one member is valid at any time

## Best Practices

1. **Structure Design**
   - Group related data logically
   - Use meaningful member names
   - Consider memory alignment for performance

2. **Union Usage**
   - Always use tagged unions for type safety
   - Never access a union member that wasn't the last one set
   - Document which member is currently valid

3. **Pointer Safety**
   - Check for NULL before dereferencing
   - Free dynamically allocated structures
   - Use arrow operator (->) for pointer member access

4. **Initialization**
   - Initialize all structure members
   - Use designated initializers for clarity when needed
   - Be careful with string members (use strcpy, not assignment)

## Common Pitfalls

1. **Uninitialized Members**: Always initialize structure members to avoid garbage values
2. **String Assignment**: Use `strcpy()` for string members, not direct assignment
3. **Union Misuse**: Accessing wrong union member leads to undefined behavior
4. **Memory Leaks**: Free dynamically allocated structures
5. **Padding Issues**: Structure size may be larger than expected due to alignment

## Compilation and Execution

```bash
make          # Compile the program
make run      # Compile and run
make clean    # Remove compiled files
make debug    # Compile with debugging symbols
```

## Expected Output

The program demonstrates:
- Basic structure operations and member access
- Nested structure usage
- Structure pointer operations
- Union behavior and memory sharing
- Tagged union implementation
- Memory layout information

## Next Steps

After mastering structures and unions, you'll be ready to:
- Learn dynamic memory allocation (Lesson 02)
- Implement complex data structures
- Work with file I/O using structures
- Understand advanced pointer techniques

## Key Takeaways

- Structures group related data with separate memory for each member
- Unions share memory among members for space efficiency
- Use tagged unions for type-safe union operations
- Structure pointers enable dynamic allocation and efficient parameter passing
- Understanding memory layout helps optimize performance and debug issues