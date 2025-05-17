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


#endif