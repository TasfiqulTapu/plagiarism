#ifndef NOKOL_H
#define NOKOL_H
#include "stdio.h"

/**
 * @brief Normalize text (.lower() and remove punctuation
 * @param f File pointer
 * @returns Normalized string
 */
char *normalize(FILE *f);


#endif