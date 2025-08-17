#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Array-based stack implementation
Stack* create_stack(void) {
    Stack* stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed for stack\n");
        return NULL;
    }
    stack->top = -1;
    stack->capacity = MAX_STACK_SIZE;
    return stack;
}

void destroy_stack(Stack* stack) {
    if (stack != NULL) {
        free(stack);
    }
}

int push(Stack* stack, int data) {
    if (stack == NULL) return 0;
    
    if (is_stack_full(stack)) {
        printf("Stack overflow! Cannot push %d\n", data);
        return 0;
    }
    
    stack->data[++stack->top] = data;
    return 1;
}

int pop(Stack* stack) {
    if (stack == NULL || is_stack_empty(stack)) {
        printf("Stack underflow! Cannot pop from empty stack\n");
        return -1;
    }
    
    return stack->data[stack->top--];
}

int peek(Stack* stack) {
    if (stack == NULL || is_stack_empty(stack)) {
        printf("Stack is empty! Cannot peek\n");
        return -1;
    }
    
    return stack->data[stack->top];
}

int is_stack_empty(Stack* stack) {
    return (stack == NULL || stack->top == -1);
}

int is_stack_full(Stack* stack) {
    return (stack != NULL && stack->top == stack->capacity - 1);
}

int stack_size(Stack* stack) {
    return (stack != NULL) ? stack->top + 1 : 0;
}

void display_stack(Stack* stack) {
    if (stack == NULL || is_stack_empty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    
    printf("Stack (top to bottom): ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->data[i]);
    }
    printf("(size: %d)\n", stack_size(stack));
}

// Linked list-based stack implementation
LinkedStack* create_linked_stack(void) {
    LinkedStack* stack = malloc(sizeof(LinkedStack));
    if (stack == NULL) {
        printf("Memory allocation failed for linked stack\n");
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void destroy_linked_stack(LinkedStack* stack) {
    if (stack == NULL) return;
    
    while (!is_linked_stack_empty(stack)) {
        pop_linked(stack);
    }
    free(stack);
}

int push_linked(LinkedStack* stack, int data) {
    if (stack == NULL) return 0;
    
    StackNode* new_node = malloc(sizeof(StackNode));
    if (new_node == NULL) {
        printf("Memory allocation failed for new stack node\n");
        return 0;
    }
    
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
    return 1;
}

int pop_linked(LinkedStack* stack) {
    if (stack == NULL || is_linked_stack_empty(stack)) {
        printf("Stack underflow! Cannot pop from empty stack\n");
        return -1;
    }
    
    StackNode* temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return data;
}

int peek_linked(LinkedStack* stack) {
    if (stack == NULL || is_linked_stack_empty(stack)) {
        printf("Stack is empty! Cannot peek\n");
        return -1;
    }
    
    return stack->top->data;
}

int is_linked_stack_empty(LinkedStack* stack) {
    return (stack == NULL || stack->top == NULL);
}

int linked_stack_size(LinkedStack* stack) {
    return (stack != NULL) ? stack->size : 0;
}

void display_linked_stack(LinkedStack* stack) {
    if (stack == NULL || is_linked_stack_empty(stack)) {
        printf("Linked stack is empty\n");
        return;
    }
    
    printf("Linked stack (top to bottom): ");
    StackNode* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("(size: %d)\n", stack->size);
}