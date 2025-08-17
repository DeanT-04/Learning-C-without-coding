#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "stack.h"
#include "queue.h"

// Function prototypes
void demonstrate_linked_list(void);
void demonstrate_stack(void);
void demonstrate_queue(void);
void demonstrate_practical_applications(void);

int main(void) {
    printf("=== Data Structures in C ===\n\n");
    
    demonstrate_linked_list();
    demonstrate_stack();
    demonstrate_queue();
    demonstrate_practical_applications();
    
    return 0;
}

void demonstrate_linked_list(void) {
    printf("1. Linked List Operations:\n");
    printf("--------------------------\n");
    
    // Create a new linked list
    LinkedList* list = create_list();
    if (list == NULL) {
        printf("Failed to create linked list\n");
        return;
    }
    
    printf("Created empty linked list\n");
    display_list(list);
    
    // Insert elements at the beginning
    printf("\nInserting at beginning: 10, 20, 30\n");
    insert_at_beginning(list, 10);
    insert_at_beginning(list, 20);
    insert_at_beginning(list, 30);
    display_list(list);
    
    // Insert elements at the end
    printf("\nInserting at end: 40, 50\n");
    insert_at_end(list, 40);
    insert_at_end(list, 50);
    display_list(list);
    
    // Insert at specific position
    printf("\nInserting 25 at position 2\n");
    insert_at_position(list, 25, 2);
    display_list(list);
    
    // Search for elements
    printf("\nSearching for elements:\n");
    int pos = search(list, 25);
    if (pos != -1) {
        printf("Found 25 at position %d\n", pos);
    }
    pos = search(list, 100);
    if (pos == -1) {
        printf("Element 100 not found\n");
    }
    
    // Delete operations
    printf("\nDeleting from beginning:\n");
    int deleted = delete_from_beginning(list);
    printf("Deleted: %d\n", deleted);
    display_list(list);
    
    printf("\nDeleting from end:\n");
    deleted = delete_from_end(list);
    printf("Deleted: %d\n", deleted);
    display_list(list);
    
    printf("\nDeleting from position 1:\n");
    deleted = delete_from_position(list, 1);
    printf("Deleted: %d\n", deleted);
    display_list(list);
    
    // Reverse the list
    printf("\nReversing the list:\n");
    reverse_list(list);
    display_list(list);
    
    // Clean up
    destroy_list(list);
    printf("Linked list destroyed\n\n");
}

void demonstrate_stack(void) {
    printf("2. Stack Operations:\n");
    printf("--------------------\n");
    
    // Array-based stack
    printf("Array-based Stack:\n");
    Stack* stack = create_stack();
    if (stack == NULL) {
        printf("Failed to create stack\n");
        return;
    }
    
    printf("Created empty stack\n");
    display_stack(stack);
    
    // Push elements
    printf("\nPushing elements: 10, 20, 30, 40, 50\n");
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    push(stack, 40);
    push(stack, 50);
    display_stack(stack);
    
    // Peek at top element
    printf("\nTop element (peek): %d\n", peek(stack));
    
    // Pop elements
    printf("\nPopping elements:\n");
    while (!is_stack_empty(stack)) {
        int popped = pop(stack);
        printf("Popped: %d, ", popped);
        display_stack(stack);
    }
    
    destroy_stack(stack);
    
    // Linked list-based stack
    printf("\nLinked List-based Stack:\n");
    LinkedStack* linked_stack = create_linked_stack();
    if (linked_stack == NULL) {
        printf("Failed to create linked stack\n");
        return;
    }
    
    printf("Created empty linked stack\n");
    display_linked_stack(linked_stack);
    
    // Push elements
    printf("\nPushing elements: 100, 200, 300\n");
    push_linked(linked_stack, 100);
    push_linked(linked_stack, 200);
    push_linked(linked_stack, 300);
    display_linked_stack(linked_stack);
    
    // Pop elements
    printf("\nPopping all elements:\n");
    while (!is_linked_stack_empty(linked_stack)) {
        int popped = pop_linked(linked_stack);
        printf("Popped: %d, ", popped);
        display_linked_stack(linked_stack);
    }
    
    destroy_linked_stack(linked_stack);
    printf("Stacks destroyed\n\n");
}

void demonstrate_queue(void) {
    printf("3. Queue Operations:\n");
    printf("--------------------\n");
    
    // Array-based queue (circular)
    printf("Array-based Circular Queue:\n");
    Queue* queue = create_queue();
    if (queue == NULL) {
        printf("Failed to create queue\n");
        return;
    }
    
    printf("Created empty queue\n");
    display_queue(queue);
    
    // Enqueue elements
    printf("\nEnqueuing elements: 10, 20, 30, 40, 50\n");
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);
    display_queue(queue);
    
    // Check front and rear elements
    printf("\nFront element: %d\n", front_element(queue));
    printf("Rear element: %d\n", rear_element(queue));
    
    // Dequeue some elements
    printf("\nDequeuing 2 elements:\n");
    for (int i = 0; i < 2; i++) {
        int dequeued = dequeue(queue);
        printf("Dequeued: %d, ", dequeued);
        display_queue(queue);
    }
    
    // Enqueue more elements to show circular nature
    printf("\nEnqueuing more elements: 60, 70\n");
    enqueue(queue, 60);
    enqueue(queue, 70);
    display_queue(queue);
    
    // Dequeue all remaining elements
    printf("\nDequeuing all remaining elements:\n");
    while (!is_queue_empty(queue)) {
        int dequeued = dequeue(queue);
        printf("Dequeued: %d, ", dequeued);
        display_queue(queue);
    }
    
    destroy_queue(queue);
    
    // Linked list-based queue
    printf("\nLinked List-based Queue:\n");
    LinkedQueue* linked_queue = create_linked_queue();
    if (linked_queue == NULL) {
        printf("Failed to create linked queue\n");
        return;
    }
    
    printf("Created empty linked queue\n");
    display_linked_queue(linked_queue);
    
    // Enqueue elements
    printf("\nEnqueuing elements: 100, 200, 300, 400\n");
    enqueue_linked(linked_queue, 100);
    enqueue_linked(linked_queue, 200);
    enqueue_linked(linked_queue, 300);
    enqueue_linked(linked_queue, 400);
    display_linked_queue(linked_queue);
    
    // Dequeue all elements
    printf("\nDequeuing all elements:\n");
    while (!is_linked_queue_empty(linked_queue)) {
        int dequeued = dequeue_linked(linked_queue);
        printf("Dequeued: %d, ", dequeued);
        display_linked_queue(linked_queue);
    }
    
    destroy_linked_queue(linked_queue);
    printf("Queues destroyed\n\n");
}

void demonstrate_practical_applications(void) {
    printf("4. Practical Applications:\n");
    printf("--------------------------\n");
    
    // Stack application: Parentheses matching
    printf("Stack Application - Parentheses Matching:\n");
    Stack* paren_stack = create_stack();
    char expression[] = "((()))";
    int balanced = 1;
    
    printf("Checking expression: %s\n", expression);
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(') {
            push(paren_stack, 1);
        } else if (expression[i] == ')') {
            if (is_stack_empty(paren_stack)) {
                balanced = 0;
                break;
            }
            pop(paren_stack);
        }
    }
    
    if (!is_stack_empty(paren_stack)) {
        balanced = 0;
    }
    
    printf("Expression is %s\n", balanced ? "balanced" : "not balanced");
    destroy_stack(paren_stack);
    
    // Queue application: Process scheduling simulation
    printf("\nQueue Application - Process Scheduling:\n");
    LinkedQueue* process_queue = create_linked_queue();
    
    printf("Adding processes to queue: P1(1), P2(2), P3(3), P4(4)\n");
    enqueue_linked(process_queue, 1);
    enqueue_linked(process_queue, 2);
    enqueue_linked(process_queue, 3);
    enqueue_linked(process_queue, 4);
    
    printf("Processing in FIFO order:\n");
    while (!is_linked_queue_empty(process_queue)) {
        int process = dequeue_linked(process_queue);
        printf("Processing P%d... ", process);
        display_linked_queue(process_queue);
    }
    
    destroy_linked_queue(process_queue);
    
    // Linked list application: Simple database
    printf("\nLinked List Application - Simple Student Database:\n");
    LinkedList* student_db = create_list();
    
    printf("Adding student IDs: 101, 102, 103, 104\n");
    insert_at_end(student_db, 101);
    insert_at_end(student_db, 102);
    insert_at_end(student_db, 103);
    insert_at_end(student_db, 104);
    display_list(student_db);
    
    printf("\nSearching for student 103:\n");
    int pos = search(student_db, 103);
    if (pos != -1) {
        printf("Student 103 found at position %d\n", pos);
    }
    
    printf("\nRemoving student 102 (position 1):\n");
    delete_from_position(student_db, 1);
    display_list(student_db);
    
    destroy_list(student_db);
    
    printf("\nTime Complexity Summary:\n");
    printf("------------------------\n");
    printf("Linked List:\n");
    printf("  - Insert at beginning: O(1)\n");
    printf("  - Insert at end: O(n)\n");
    printf("  - Search: O(n)\n");
    printf("  - Delete: O(n) for arbitrary position\n");
    printf("\nStack:\n");
    printf("  - Push: O(1)\n");
    printf("  - Pop: O(1)\n");
    printf("  - Peek: O(1)\n");
    printf("\nQueue:\n");
    printf("  - Enqueue: O(1)\n");
    printf("  - Dequeue: O(1)\n");
    printf("  - Front/Rear access: O(1)\n");
}