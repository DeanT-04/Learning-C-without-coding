#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

LinkedList* create_list(void) {
    LinkedList* list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("Memory allocation failed for list\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void destroy_list(LinkedList* list) {
    if (list == NULL) return;
    
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

void insert_at_beginning(LinkedList* list, int data) {
    if (list == NULL) return;
    
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed for new node\n");
        return;
    }
    
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void insert_at_end(LinkedList* list, int data) {
    if (list == NULL) return;
    
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed for new node\n");
        return;
    }
    
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

void insert_at_position(LinkedList* list, int data, int position) {
    if (list == NULL || position < 0) return;
    
    if (position == 0) {
        insert_at_beginning(list, data);
        return;
    }
    
    if (position >= list->size) {
        insert_at_end(list, data);
        return;
    }
    
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed for new node\n");
        return;
    }
    
    new_node->data = data;
    
    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}

int delete_from_beginning(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    
    Node* temp = list->head;
    int data = temp->data;
    list->head = list->head->next;
    free(temp);
    list->size--;
    return data;
}

int delete_from_end(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    
    if (list->head->next == NULL) {
        int data = list->head->data;
        free(list->head);
        list->head = NULL;
        list->size--;
        return data;
    }
    
    Node* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    int data = current->next->data;
    free(current->next);
    current->next = NULL;
    list->size--;
    return data;
}

int delete_from_position(LinkedList* list, int position) {
    if (list == NULL || list->head == NULL || position < 0 || position >= list->size) {
        printf("Invalid position or empty list\n");
        return -1;
    }
    
    if (position == 0) {
        return delete_from_beginning(list);
    }
    
    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    Node* temp = current->next;
    int data = temp->data;
    current->next = temp->next;
    free(temp);
    list->size--;
    return data;
}

int search(LinkedList* list, int data) {
    if (list == NULL || list->head == NULL) return -1;
    
    Node* current = list->head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == data) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;
}

void display_list(LinkedList* list) {
    if (list == NULL || list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    printf("List: ");
    Node* current = list->head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" (size: %d)\n", list->size);
}

void reverse_list(LinkedList* list) {
    if (list == NULL || list->head == NULL) return;
    
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    list->head = prev;
}

int get_size(LinkedList* list) {
    return (list != NULL) ? list->size : 0;
}

int is_empty(LinkedList* list) {
    return (list == NULL || list->head == NULL);
}