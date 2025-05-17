#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 10000 // Worstcase scenario we have 10k individual words

typedef struct HashNode {
    char *key;
    int value;
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
unsigned int hash(char *key){
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
}

int ht_get(HashTable *ht, const char *key){
    unsigned int slot = hash(key);
    HashNode *entry = ht->entries[slot];

    // Case 1: Empty slot
    if(entry==NULL) return NULL;

    // Case 2: Something exists
    // We walk
    while(entry != NULL){
        if(strcmp(entry->key, key)==0){
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL; // If we can't find anything after our walk
}

char **ht_keys(const HashTable *ht){}

void free_table(HashTable *ht){}