#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 100

// Stack structure using array
typedef struct Stack {
    int data[MAX_STACK_SIZE];
    int top;
    int capacity;
} Stack;

// Stack node for linked list implementation
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

// Stack structure using linked list
typedef struct LinkedStack {
    StackNode* top;
    int size;
} LinkedStack;

// Array-based stack functions
Stack* create_stack(void);
void destroy_stack(Stack* stack);
int push(Stack* stack, int data);
int pop(Stack* stack);
int peek(Stack* stack);
int is_stack_empty(Stack* stack);
int is_stack_full(Stack* stack);
int stack_size(Stack* stack);
void display_stack(Stack* stack);

// Linked list-based stack functions
LinkedStack* create_linked_stack(void);
void destroy_linked_stack(LinkedStack* stack);
int push_linked(LinkedStack* stack, int data);
int pop_linked(LinkedStack* stack);
int peek_linked(LinkedStack* stack);
int is_linked_stack_empty(LinkedStack* stack);
int linked_stack_size(LinkedStack* stack);
void display_linked_stack(LinkedStack* stack);

#endif // STACK_H