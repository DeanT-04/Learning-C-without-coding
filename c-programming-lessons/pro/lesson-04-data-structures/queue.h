#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 100

// Queue structure using array (circular queue)
typedef struct Queue {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Queue node for linked list implementation
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

// Queue structure using linked list
typedef struct LinkedQueue {
    QueueNode* front;
    QueueNode* rear;
    int size;
} LinkedQueue;

// Array-based queue functions
Queue* create_queue(void);
void destroy_queue(Queue* queue);
int enqueue(Queue* queue, int data);
int dequeue(Queue* queue);
int front_element(Queue* queue);
int rear_element(Queue* queue);
int is_queue_empty(Queue* queue);
int is_queue_full(Queue* queue);
int queue_size(Queue* queue);
void display_queue(Queue* queue);

// Linked list-based queue functions
LinkedQueue* create_linked_queue(void);
void destroy_linked_queue(LinkedQueue* queue);
int enqueue_linked(LinkedQueue* queue, int data);
int dequeue_linked(LinkedQueue* queue);
int front_element_linked(LinkedQueue* queue);
int rear_element_linked(LinkedQueue* queue);
int is_linked_queue_empty(LinkedQueue* queue);
int linked_queue_size(LinkedQueue* queue);
void display_linked_queue(LinkedQueue* queue);

#endif // QUEUE_H