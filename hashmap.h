#ifndef HASHMAP_H
#define HASHMAP_H

/*
Modified hash table implementation from https://www.youtube.com/watch?v=wg8hZxMRwcw
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 10000 // Worstcase scenario we have 10k individual words

typedef struct HashNode {
    char *key;    
    double value; // Using double if we need it for tf-idf later
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    HashNode **entries;
    int size;
} HashTable;

/**
 * @brief a simple hash function
 * @param key key to hash
 * @returns hashed value
 */
unsigned int hash(const char *key){
    long long PRIME = 31;
    unsigned long int value = 0;
    unsigned int key_len = strlen(key);
    for(int i=0; i<key_len; i++) value = value * PRIME + key[i];
    return value % TABLE_SIZE;
}

HashTable *create_hashtable(){
    // allocate table
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) {
        perror("Error allocating memory for hash table");
        return NULL;
    }
    // allocate table entries
    table->entries = malloc(sizeof(HashNode*) * TABLE_SIZE);
    if (!table->entries) {
        perror("Error allocating memory for hash table nodes");
        free(table); // Memory safety 💅
        return NULL;
    }
    // Intialize all table contents to NULL
    table->size = 0;
    for(int i=0; i<TABLE_SIZE; i++){
        table->entries[i] = NULL;
    }
    return table;
}

void ht_set(HashTable *ht, const char *key, int value){
    // Get hash of key
    unsigned int slot = hash(key);

    // Check if hash-collision occurs
    HashNode *entry = ht->entries[slot];
    // IF no collision then return early after insertion
    if(entry == NULL){
        HashNode *new_node = (HashNode*)malloc(sizeof(HashNode));
        if(new_node==NULL){
            perror("Error allocating newnode");
            return;
        }
        new_node->key = malloc(strlen(key));
        if(new_node==NULL){
            perror("Error allocating newnode key");
            return;
        }

        strcpy(new_node->key, key);
        new_node->value = value;
        ht->entries[slot] = new_node;
        ht->size = ht->size + 1;
        return;
    }

    // If collision does occur
    // Already exists
    HashNode *prev;
    while (entry != NULL) {
        // check key
        if (strcmp(entry->key, key) == 0) {
            // match found, replace value
            entry->value = value;
            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;
    }

    // If doesn't exist already
    HashNode *new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->key = malloc(strlen(key));

    strcpy(new_node->key, key);
    new_node->value = value;
    prev->next = new_node;
    ht->size = ht->size + 1;
    return;
}

double ht_get(HashTable *ht, const char *key){
    unsigned int slot = hash(key);
    HashNode *entry = ht->entries[slot];

    // Case 1: Empty slot
    if(entry==NULL) return 0.0;

    // Case 2: Something exists
    // We walk
    while(entry != NULL){
        if(strcmp(entry->key, key)==0){
            return entry->value;
        }
        entry = entry->next;
    }
    return 0.0; // If we can't find anything after our walk
}

int ht_size(HashTable* ht){
    if (ht == NULL) {
        perror("Hahtable doesn't exist");
        return 0;
    }
    return ht->size;
}

/**
 * @brief Retrieves all keys currently stored in the hash table.
 * @param ht A pointer to the HashTable.
 * @returns A dynamically allocated array of strings (char**).
 */
char **ht_keys(const HashTable *ht){
    if (!ht) {
        fprintf(stderr, "Error: Invalid input to ht_keys function (NULL HashTable).\n");
        return NULL;
    }

    if (ht->size == 0) {
        // If the hash table is empty, return NULL
        return NULL;
    }

    // Allocate memory for the array of key strings
    char** key_list = (char**)malloc(ht->size * sizeof(char*));
    if (!key_list) {
        perror("Error allocating memory for key list");
        return NULL;
    }

    int key_count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) { // Use TABLE_SIZE as capacity is fixed
        // Traverse the linked list in the current bucket
        HashNode* current = ht->entries[i];
        while (current) {
            // Duplicate the key string and add it to the key_list
            key_list[key_count] = strdup(current->key);
            if (!key_list[key_count]) {
                 perror("Error duplicating key string for key list");
                 // Clean up already duplicated keys if allocation fails
                 for(int j = 0; j < key_count; j++) {
                     free(key_list[j]);
                 }
                 free(key_list);
                 return NULL;
            }
            key_count++;
            current = current->next;
        }
    }

    return key_list;
}

/**
 * @brief Frees all dynamically allocated memory associated with the hash table.
 * @param ht A pointer to the HashTable to be freed.
 */
void ht_free(HashTable *ht){
    if (!ht) {
        return; // Nothing to free if the table pointer is NULL
    }

    // Iterate through each node
    for (int i = 0; i < TABLE_SIZE; i++) { // Use TABLE_SIZE as capacity is fixed
        HashNode* current = ht->entries[i];
        // free each node
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp->key);   // Free the duplicated key string
            free(temp);        // Free the node structure itself
        }
    }

    free(ht->entries); // Free the array of buckets (entries)
    free(ht);          // Free the hash table structure itself
}

#endif // HASHMAP_H
