#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Basic structure definition
struct Student {
    int id;
    char name[50];
    float gpa;
    int age;
};

// Structure with nested structure
struct Address {
    char street[100];
    char city[50];
    char state[20];
    int zip_code;
};

struct Person {
    char name[50];
    int age;
    struct Address address;  // Nested structure
};

// Union definition
union Data {
    int integer;
    float floating;
    char character;
    char string[20];
};

// Structure with union member
struct Record {
    int type;  // 1=int, 2=float, 3=char, 4=string
    union Data data;
};

// Function prototypes
void demonstrate_basic_structures(void);
void demonstrate_nested_structures(void);
void demonstrate_structure_pointers(void);
void demonstrate_unions(void);
void demonstrate_structure_with_union(void);
void print_memory_layout(void);

int main(void) {
    printf("=== C Structures and Unions Demonstration ===\n\n");
    
    demonstrate_basic_structures();
    demonstrate_nested_structures();
    demonstrate_structure_pointers();
    demonstrate_unions();
    demonstrate_structure_with_union();
    print_memory_layout();
    
    return 0;
}

void demonstrate_basic_structures(void) {
    printf("1. Basic Structure Operations:\n");
    printf("------------------------------\n");
    
    // Structure declaration and initialization
    struct Student student1 = {101, "Alice Johnson", 3.85, 20};
    
    // Alternative initialization
    struct Student student2;
    student2.id = 102;
    strcpy(student2.name, "Bob Smith");
    student2.gpa = 3.92;
    student2.age = 21;
    
    // Display structure members
    printf("Student 1: ID=%d, Name=%s, GPA=%.2f, Age=%d\n", 
           student1.id, student1.name, student1.gpa, student1.age);
    printf("Student 2: ID=%d, Name=%s, GPA=%.2f, Age=%d\n", 
           student2.id, student2.name, student2.gpa, student2.age);
    
    // Structure assignment
    struct Student student3 = student1;  // Copy all members
    printf("Student 3 (copy of Student 1): ID=%d, Name=%s\n", 
           student3.id, student3.name);
    
    printf("\n");
}

void demonstrate_nested_structures(void) {
    printf("2. Nested Structures:\n");
    printf("---------------------\n");
    
    struct Person person = {
        "John Doe",
        30,
        {"123 Main St", "Springfield", "IL", 62701}
    };
    
    printf("Person: %s, Age: %d\n", person.name, person.age);
    printf("Address: %s, %s, %s %d\n", 
           person.address.street, person.address.city, 
           person.address.state, person.address.zip_code);
    
    // Modifying nested structure members
    strcpy(person.address.city, "Chicago");
    person.address.zip_code = 60601;
    printf("Updated Address: %s, %s, %s %d\n", 
           person.address.street, person.address.city, 
           person.address.state, person.address.zip_code);
    
    printf("\n");
}

void demonstrate_structure_pointers(void) {
    printf("3. Structure Pointers:\n");
    printf("----------------------\n");
    
    struct Student student = {103, "Carol Davis", 3.78, 19};
    struct Student *ptr = &student;
    
    // Accessing members through pointer (two methods)
    printf("Using (*ptr).member syntax:\n");
    printf("ID: %d, Name: %s\n", (*ptr).id, (*ptr).name);
    
    printf("Using ptr->member syntax (preferred):\n");
    printf("ID: %d, Name: %s, GPA: %.2f\n", ptr->id, ptr->name, ptr->gpa);
    
    // Modifying through pointer
    ptr->age = 20;
    strcpy(ptr->name, "Carol Johnson");
    printf("After modification: Name=%s, Age=%d\n", ptr->name, ptr->age);
    
    // Dynamic allocation
    struct Student *dynamic_student = malloc(sizeof(struct Student));
    if (dynamic_student != NULL) {
        dynamic_student->id = 104;
        strcpy(dynamic_student->name, "David Wilson");
        dynamic_student->gpa = 3.65;
        dynamic_student->age = 22;
        
        printf("Dynamic student: ID=%d, Name=%s\n", 
               dynamic_student->id, dynamic_student->name);
        
        free(dynamic_student);  // Don't forget to free memory
    }
    
    printf("\n");
}

void demonstrate_unions(void) {
    printf("4. Union Operations:\n");
    printf("--------------------\n");
    
    union Data data;
    
    // Store integer
    data.integer = 42;
    printf("Stored integer: %d\n", data.integer);
    printf("Union size: %zu bytes\n", sizeof(data));
    
    // Store float (overwrites integer)
    data.floating = 3.14159;
    printf("Stored float: %.5f\n", data.floating);
    printf("Integer value now (garbage): %d\n", data.integer);
    
    // Store character
    data.character = 'A';
    printf("Stored character: %c\n", data.character);
    
    // Store string
    strcpy(data.string, "Hello");
    printf("Stored string: %s\n", data.string);
    
    printf("Note: Only the last stored value is valid!\n\n");
}

void demonstrate_structure_with_union(void) {
    printf("5. Structure with Union (Tagged Union):\n");
    printf("---------------------------------------\n");
    
    struct Record records[4];
    
    // Integer record
    records[0].type = 1;
    records[0].data.integer = 100;
    
    // Float record
    records[1].type = 2;
    records[1].data.floating = 99.99;
    
    // Character record
    records[2].type = 3;
    records[2].data.character = 'X';
    
    // String record
    records[3].type = 4;
    strcpy(records[3].data.string, "Sample");
    
    // Display records based on type
    for (int i = 0; i < 4; i++) {
        printf("Record %d: ", i + 1);
        switch (records[i].type) {
            case 1:
                printf("Integer = %d\n", records[i].data.integer);
                break;
            case 2:
                printf("Float = %.2f\n", records[i].data.floating);
                break;
            case 3:
                printf("Character = %c\n", records[i].data.character);
                break;
            case 4:
                printf("String = %s\n", records[i].data.string);
                break;
            default:
                printf("Unknown type\n");
        }
    }
    
    printf("\n");
}

void print_memory_layout(void) {
    printf("6. Memory Layout Information:\n");
    printf("-----------------------------\n");
    
    struct Student student;
    union Data data;
    
    printf("Structure sizes:\n");
    printf("sizeof(struct Student) = %zu bytes\n", sizeof(struct Student));
    printf("sizeof(struct Person) = %zu bytes\n", sizeof(struct Person));
    printf("sizeof(struct Address) = %zu bytes\n", sizeof(struct Address));
    
    printf("\nUnion sizes:\n");
    printf("sizeof(union Data) = %zu bytes\n", sizeof(union Data));
    printf("sizeof(struct Record) = %zu bytes\n", sizeof(struct Record));
    
    printf("\nMember offsets in struct Student:\n");
    printf("id offset: %zu\n", (size_t)&student.id - (size_t)&student);
    printf("name offset: %zu\n", (size_t)&student.name - (size_t)&student);
    printf("gpa offset: %zu\n", (size_t)&student.gpa - (size_t)&student);
    printf("age offset: %zu\n", (size_t)&student.age - (size_t)&student);
    
    printf("\nUnion member addresses (all same):\n");
    printf("integer address: %p\n", (void*)&data.integer);
    printf("floating address: %p\n", (void*)&data.floating);
    printf("character address: %p\n", (void*)&data.character);
    printf("string address: %p\n", (void*)&data.string);
}