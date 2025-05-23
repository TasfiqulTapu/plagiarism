#ifndef HASHMAP_H
#define HASHMAP_H

// Define the structure for a single node in the linked list (for separate chaining)
typedef struct HashNode {
    char *key;
    double value; // Using double if we need it for tf-idf later
    struct HashNode *next;
} HashNode;

// Define the structure for the hash table itself
typedef struct HashTable {
    HashNode **entries;
    int size; // Tracks the number of key-value pairs stored
} HashTable;

/**
 * @brief a simple hash function
 * @param key key to hash
 * @returns hashed value
 */
unsigned int hash(char *key);

/**
 * @brief Creates and initializes a new hash table.
 * @returns A pointer to the newly created HashTable, or NULL if memory allocation fails.
 */
HashTable *create_hashtable();

/**
 * @brief Inserts a key-value pair into the hash table.
 * If the key already exists, its value is updated.
 * @param ht A pointer to the HashTable.
 * @param key The string key to insert or update.
 * @param value The integer value associated with the key.
 */
void ht_set(HashTable *ht, const char *key, int value);

/**
 * @brief Get the value associated with a given key from the hash table.
 * @param ht A pointer to the HashTable.
 * @param key The string key to search for.
 * @returns The integer value if the key is found, or -1 if the key is not found or on error.
 */
double ht_get(HashTable *ht, const char *key);


int ht_size(HashTable* ht);


/**
 * @brief Retrieves all keys currently stored in the hash table.
 * @param ht A pointer to the HashTable.
 * @returns A dynamically allocated array of strings (char**).
 */
char **ht_keys(const HashTable *ht);

/**
 * @brief Frees all memory associated with the hash table.
 * @param ht A pointer to the HashTable to be freed.
 */
void ht_free(HashTable *ht);

#endif // HASHMAP_H
