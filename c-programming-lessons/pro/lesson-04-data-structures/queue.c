#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Array-based queue implementation (circular queue)
Queue* create_queue(void) {
    Queue* queue = malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed for queue\n");
        return NULL;
    }
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = MAX_QUEUE_SIZE;
    return queue;
}

void destroy_queue(Queue* queue) {
    if (queue != NULL) {
        free(queue);
    }
}

int enqueue(Queue* queue, int data) {
    if (queue == NULL) return 0;
    
    if (is_queue_full(queue)) {
        printf("Queue overflow! Cannot enqueue %d\n", data);
        return 0;
    }
    
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = data;
    queue->size++;
    return 1;
}

int dequeue(Queue* queue) {
    if (queue == NULL || is_queue_empty(queue)) {
        printf("Queue underflow! Cannot dequeue from empty queue\n");
        return -1;
    }
    
    int data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}

int front_element(Queue* queue) {
    if (queue == NULL || is_queue_empty(queue)) {
        printf("Queue is empty! Cannot get front element\n");
        return -1;
    }
    
    return queue->data[queue->front];
}

int rear_element(Queue* queue) {
    if (queue == NULL || is_queue_empty(queue)) {
        printf("Queue is empty! Cannot get rear element\n");
        return -1;
    }
    
    return queue->data[queue->rear];
}

int is_queue_empty(Queue* queue) {
    return (queue == NULL || queue->size == 0);
}

int is_queue_full(Queue* queue) {
    return (queue != NULL && queue->size == queue->capacity);
}

int queue_size(Queue* queue) {
    return (queue != NULL) ? queue->size : 0;
}

void display_queue(Queue* queue) {
    if (queue == NULL || is_queue_empty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    
    printf("Queue (front to rear): ");
    int index = queue->front;
    for (int i = 0; i < queue->size; i++) {
        printf("%d ", queue->data[index]);
        index = (index + 1) % queue->capacity;
    }
    printf("(size: %d)\n", queue->size);
}

// Linked list-based queue implementation
LinkedQueue* create_linked_queue(void) {
    LinkedQueue* queue = malloc(sizeof(LinkedQueue));
    if (queue == NULL) {
        printf("Memory allocation failed for linked queue\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void destroy_linked_queue(LinkedQueue* queue) {
    if (queue == NULL) return;
    
    while (!is_linked_queue_empty(queue)) {
        dequeue_linked(queue);
    }
    free(queue);
}

int enqueue_linked(LinkedQueue* queue, int data) {
    if (queue == NULL) return 0;
    
    QueueNode* new_node = malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        printf("Memory allocation failed for new queue node\n");
        return 0;
    }
    
    new_node->data = data;
    new_node->next = NULL;
    
    if (is_linked_queue_empty(queue)) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    
    queue->size++;
    return 1;
}

int dequeue_linked(LinkedQueue* queue) {
    if (queue == NULL || is_linked_queue_empty(queue)) {
        printf("Queue underflow! Cannot dequeue from empty queue\n");
        return -1;
    }
    
    QueueNode* temp = queue->front;
    int data = temp->data;
    
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    queue->size--;
    return data;
}

int front_element_linked(LinkedQueue* queue) {
    if (queue == NULL || is_linked_queue_empty(queue)) {
        printf("Queue is empty! Cannot get front element\n");
        return -1;
    }
    
    return queue->front->data;
}

int rear_element_linked(LinkedQueue* queue) {
    if (queue == NULL || is_linked_queue_empty(queue)) {
        printf("Queue is empty! Cannot get rear element\n");
        return -1;
    }
    
    return queue->rear->data;
}

int is_linked_queue_empty(LinkedQueue* queue) {
    return (queue == NULL || queue->front == NULL);
}

int linked_queue_size(LinkedQueue* queue) {
    return (queue != NULL) ? queue->size : 0;
}

void display_linked_queue(LinkedQueue* queue) {
    if (queue == NULL || is_linked_queue_empty(queue)) {
        printf("Linked queue is empty\n");
        return;
    }
    
    printf("Linked queue (front to rear): ");
    QueueNode* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("(size: %d)\n", queue->size);
}