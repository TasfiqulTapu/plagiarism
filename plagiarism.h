#ifndef NOKOL_H
#define NOKOL_H
#include "stdio.h"


/**
 * @brief Normalize text (.lower() and remove punctuation
 * @param f File pointer
 * @returns Normalized string
 */
char *normalize(FILE *f);
/**
 * @brief Tokenize text into individual words and remove stopwords
 * @param str An array of normalized characters
 * @returns StringDeque of tokens(words)
 */
StringDeque* tokenize(char *str);

HashTable* vectorize(StringDeque *tokens);

/**
 * @brief get cosine similarity of two vectors(hashmap)
 * @param vec1
 * @param vec2
 * @returns a double within 0-1.
 * 0 == low similarity
 * 1 == high similarity
 */
double cosine_similarity(HashTable *vec1, HashTable *vec2);

#endif