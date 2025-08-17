# Lesson 04: Data Structures (Linked Lists, Stacks, Queues)

## Overview

This lesson covers fundamental data structures in C: linked lists, stacks, and queues. These structures are essential building blocks for more complex algorithms and applications. You'll learn both array-based and linked list-based implementations, understanding the trade-offs between different approaches.

## Key Concepts

### Data Structures Fundamentals
- **Abstract Data Types (ADT)**: Logical description of data and operations
- **Implementation**: Physical representation using arrays or linked structures
- **Time Complexity**: Performance characteristics of operations
- **Space Complexity**: Memory usage patterns

### Linear Data Structures
- **Linked Lists**: Dynamic linear collection with pointer-based connections
- **Stacks**: Last-In-First-Out (LIFO) access pattern
- **Queues**: First-In-First-Out (FIFO) access pattern

## Project Structure

This lesson uses multiple files to demonstrate modular programming:

```
lesson-04-data-structures/
├── main.c           # Main program with demonstrations
├── linked_list.h    # Linked list interface
├── linked_list.c    # Linked list implementation
├── stack.h          # Stack interface
├── stack.c          # Stack implementation
├── queue.h          # Queue interface
├── queue.c          # Queue implementation
├── Makefile         # Build configuration
└── README.md        # This documentation
```

## Data Structures Explained

### 1. Linked Lists

**Structure:**
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;
```

**Key Operations:**
- **Insert**: Add elements at beginning, end, or specific position
- **Delete**: Remove elements from beginning, end, or specific position
- **Search**: Find element and return its position
- **Traverse**: Visit all elements in order
- **Reverse**: Change the order of elements

**Advantages:**
- Dynamic size (grows/shrinks at runtime)
- Efficient insertion/deletion at beginning (O(1))
- Memory allocated as needed

**Disadvantages:**
- No random access (must traverse from head)
- Extra memory overhead for pointers
- Poor cache locality

### 2. Stacks

**Array-Based Implementation:**
```c
typedef struct Stack {
    int data[MAX_STACK_SIZE];
    int top;
    int capacity;
} Stack;
```

**Linked List-Based Implementation:**
```c
typedef struct LinkedStack {
    StackNode* top;
    int size;
} LinkedStack;
```

**Key Operations:**
- **Push**: Add element to top of stack
- **Pop**: Remove and return top element
- **Peek/Top**: View top element without removing
- **IsEmpty**: Check if stack is empty
- **IsFull**: Check if stack is full (array-based only)

**Applications:**
- Function call management (call stack)
- Expression evaluation and syntax parsing
- Undo operations in applications
- Backtracking algorithms
- Browser history

### 3. Queues

**Circular Array Implementation:**
```c
typedef struct Queue {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
    int capacity;
} Queue;
```

**Linked List Implementation:**
```c
typedef struct LinkedQueue {
    QueueNode* front;
    QueueNode* rear;
    int size;
} LinkedQueue;
```

**Key Operations:**
- **Enqueue**: Add element to rear of queue
- **Dequeue**: Remove and return front element
- **Front**: View front element without removing
- **Rear**: View rear element without removing
- **IsEmpty**: Check if queue is empty
- **IsFull**: Check if queue is full (array-based only)

**Applications:**
- Process scheduling in operating systems
- Breadth-first search algorithms
- Print job management
- Buffer for data streams
- Handling requests in web servers

## Implementation Details

### Memory Management

**Dynamic Allocation:**
```c
Node* new_node = malloc(sizeof(Node));
if (new_node == NULL) {
    // Handle allocation failure
    return 0;
}
```

**Proper Cleanup:**
```c
void destroy_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
```

### Error Handling

**Boundary Conditions:**
- Empty data structure operations
- Full data structure operations (array-based)
- Invalid position access
- Memory allocation failures

**Defensive Programming:**
```c
if (list == NULL || position < 0) {
    return -1;  // Invalid input
}
```

### Circular Queue Implementation

**Why Circular?**
- Efficient use of array space
- Avoids shifting elements
- Constant time operations

**Index Calculation:**
```c
queue->rear = (queue->rear + 1) % queue->capacity;
queue->front = (queue->front + 1) % queue->capacity;
```

## Time Complexity Analysis

### Linked List Operations
| Operation | Time Complexity | Notes |
|-----------|----------------|-------|
| Insert at beginning | O(1) | Direct head manipulation |
| Insert at end | O(n) | Must traverse to end |
| Insert at position | O(n) | Must traverse to position |
| Delete from beginning | O(1) | Direct head manipulation |
| Delete from end | O(n) | Must traverse to second-last |
| Search | O(n) | Linear search required |
| Access by index | O(n) | No random access |

### Stack Operations
| Operation | Time Complexity | Notes |
|-----------|----------------|-------|
| Push | O(1) | Direct top manipulation |
| Pop | O(1) | Direct top manipulation |
| Peek | O(1) | Direct top access |
| IsEmpty | O(1) | Simple condition check |

### Queue Operations
| Operation | Time Complexity | Notes |
|-----------|----------------|-------|
| Enqueue | O(1) | Direct rear manipulation |
| Dequeue | O(1) | Direct front manipulation |
| Front/Rear access | O(1) | Direct index access |
| IsEmpty | O(1) | Simple condition check |

## Space Complexity

### Array-Based Structures
- **Fixed Size**: O(n) where n is maximum capacity
- **Memory Efficient**: No pointer overhead
- **Contiguous Memory**: Better cache performance

### Linked Structures
- **Dynamic Size**: O(n) where n is current number of elements
- **Pointer Overhead**: Extra memory for next pointers
- **Fragmented Memory**: Potential cache misses

## Best Practices

### 1. Choose Appropriate Implementation
```c
// Use array-based for:
// - Known maximum size
// - Memory-constrained environments
// - Better cache performance

// Use linked-based for:
// - Unknown or highly variable size
// - Frequent insertions/deletions
// - Memory flexibility
```

### 2. Always Check for NULL
```c
if (list == NULL || list->head == NULL) {
    printf("Invalid operation on empty list\n");
    return -1;
}
```

### 3. Maintain Size Information
```c
// Keep track of size for O(1) size queries
typedef struct LinkedList {
    Node* head;
    int size;  // Maintain this field
} LinkedList;
```

### 4. Implement Proper Cleanup
```c
// Always provide destroy functions
void destroy_stack(Stack* stack) {
    if (stack != NULL) {
        free(stack);
    }
}
```

## Common Pitfalls

1. **Memory Leaks**: Not freeing allocated nodes
2. **Dangling Pointers**: Using freed memory
3. **Boundary Errors**: Not checking empty/full conditions
4. **Integer Overflow**: In circular queue index calculations
5. **Null Pointer Dereference**: Not checking for NULL before access

## Practical Applications

### Stack Applications
- **Expression Evaluation**: Converting infix to postfix
- **Function Calls**: Managing activation records
- **Undo Operations**: Storing previous states
- **Syntax Checking**: Matching parentheses, brackets

### Queue Applications
- **Process Scheduling**: Round-robin scheduling
- **Buffer Management**: Producer-consumer problems
- **Graph Algorithms**: Breadth-first search
- **Print Spooling**: Managing print jobs

### Linked List Applications
- **Dynamic Arrays**: Resizable collections
- **Implementation Base**: For stacks and queues
- **Memory Management**: Free block lists
- **Music Playlists**: Sequential access with insertions

## Compilation and Execution

```bash
make          # Compile all modules
make run      # Compile and run
make clean    # Remove compiled files
make debug    # Compile with debugging symbols
make test     # Run with test cases
```

## Expected Output

The program demonstrates:
- Complete linked list operations with insertions, deletions, and searches
- Both array-based and linked list-based stack implementations
- Both circular array and linked list-based queue implementations
- Practical applications showing real-world usage scenarios
- Time complexity analysis and performance characteristics

## Advanced Topics

### Variations
- **Doubly Linked Lists**: Bidirectional traversal
- **Circular Linked Lists**: Last node points to first
- **Priority Queues**: Elements with priorities
- **Deques**: Double-ended queues

### Optimizations
- **Tail Pointer**: O(1) insertion at end for linked lists
- **Memory Pools**: Reduce allocation overhead
- **Template/Generic**: Support multiple data types

## Next Steps

After mastering these basic data structures, you'll be ready to:
- Learn function pointers and callbacks (Lesson 05)
- Implement more complex data structures (trees, hash tables)
- Study advanced algorithms (sorting, searching)
- Build multi-file projects with modular design

## Key Takeaways

- Data structures provide organized ways to store and access data
- Choose implementation based on usage patterns and requirements
- Array-based structures offer better cache performance but fixed size
- Linked structures provide flexibility but with pointer overhead
- Always implement proper error handling and memory management
- Understanding time complexity helps in choosing the right structure for specific use cases