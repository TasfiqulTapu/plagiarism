#include "hashmap.h"
#include "deque.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

HashTable *vectorize(StringDeque *tokens){
    HashTable *vec = create_hashtable();
    if (tokens == NULL) {
        perror("Failed to init Hashtable");
        return NULL;
    }

    while(sdq_size(tokens) != 0){
        char *str = sdq_shift(tokens);
        double count = ht_get(vec, str);
        count += 1.0;
        ht_set(vec, str, count);
        free(str);
    }
    sdq_destroy(tokens);
    return vec;
}

double vec_abs(HashTable *ht){
    char **keys = ht_keys(ht);
    int len = ht_size(ht);
    double sqr_sum = 0.0;
    for(int i=0; i<len; i++){
        sqr_sum += pow(ht_get(ht, keys[i]),2);
    }
    double abs = sqrt(sqr_sum);
    return abs;
}
double vec_dot(HashTable *vec1, HashTable *vec2){
    char **keys = ht_keys(vec1);
    int len = ht_size(vec1);
    double dot_prod = 0.0;
    for(int i=0; i<len; i++){
        dot_prod += ht_get(vec1, keys[i]) * ht_get(vec2, keys[i]);
    }
    return dot_prod;
}

/**
 * @brief get cosine similarity of two vectors(hashmap)
 * @param vec1
 * @param vec2
 * @returns a double within 0-1.
 * 0 == low similarity
 * 1 == high similarity
 */
double cosine_similarity(HashTable *vec1, HashTable *vec2){
    double dot = vec_dot(vec1, vec2);
    double v1 = vec_abs(vec1);
    double v2 = vec_abs(vec2);
    return dot / v1 / v2;
}