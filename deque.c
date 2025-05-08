
/*
This file uses Doxygen commenting formet.
Suggested by a user in SO https://stackoverflow.com/a/10201559
Using it as vscode recognizes them.
*/


#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct DequeNode{
    char *data;
    struct DequeNode *next;
    struct DequeNode *prev;
} DequeNode;

typedef struct StringDeque{
    DequeNode *head;
    DequeNode *tail;
    int size;
} StringDeque;


/**
 * @brief Creates an empty string deque.
 * @return A pointer to the deque, NULL if fails.
 */
StringDeque *create_str_deque(){
    StringDeque *deque = (StringDeque*)malloc(sizeof(StringDeque));
    if(!deque){
        perror("Memory allocation failed");
        return NULL;
    }

    // TODO: check why vscode screams when i use . instead of ->
    // TODO: Also why it autoconverts
    deque->head = NULL;
    deque->tail = NULL;
    deque->size = 0;
    return deque;
}

/**
 * @brief Push a new node to the end of a queue
 * @param deque The deque to insert to
 * @param str The string to insert
 */
void sdq_push(StringDeque *deque, const char *str){
    if(!deque){
        perror("Deque is null");
        return;
    }
    if(!str){
        perror("String is null");
        return;
    }
    DequeNode *newNode = (DequeNode*) malloc(sizeof(DequeNode));
    if(!newNode){
        perror("Node memory allocation failed");
        return;
    } 
    newNode->data = strdup(str);
    newNode->next = NULL;
    newNode->prev = deque->tail;

    if(deque->size==0) deque->head = newNode;
    else deque->tail->next = newNode;

    deque->tail = newNode;
    deque->size++;
}

/**
 * @brief Shift the deque by one node
 * @param dequq The deque to shift
 * @returns The string that was shifted out, Null if none exist \
 * The retuerned string must be freed later
 */
char *sdq_shift(StringDeque *deque){
    if(!deque || deque->size == 0) return NULL;

    DequeNode *removed = deque->head;
    char *data = removed->data;
    deque->head = removed->next;

    if(deque->head == NULL) deque->tail = NULL;
    else deque->head->prev = NULL;

    free(removed);
    deque->size--;
    return data;
}

/**
 * @brief Get deque size because vscode doesn't know deque.size exist
 * @param deque The deque to get zise of
 * @returns deque size
 */
int sdq_size(StringDeque *deque){
    if(!deque) return 0;
    return deque->size;
}

/**
 * @brief Destroy a deque
 * @param deque THe deque to destroy
 */
void sdq_destroy(StringDeque *deque){
    if(!deque){
        perror("Deque is null");
        return;
    }
    DequeNode *c = deque->head;
    while(c != NULL){
        DequeNode *next = c->next;
        free(c->data); // The str we copied with strdup
        free(c); 
        c = next;
    }
    // Destroying the deque after all children are DESTROYED
    free(deque);
}
