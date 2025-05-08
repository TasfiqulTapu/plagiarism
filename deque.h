/*
    Uisng ifndef because otherwise if there are multiple occurances
    of the declarations, ld screams at you when running gcc
*/
#ifndef DEQUE_H
#define DEQUE_H

typedef struct StringDeque StringDeque;

/**
 * @brief Creates an empty string deque.
 * @return A pointer to the deque, NULL if fails.
 */
StringDeque *create_str_deque();

/**
 * @brief Push a new node to the end of a queue
 * @param deque The deque to insert to
 * @param str The string to insert
 */
void sdq_push(StringDeque *deque, const char *str);

/**
 * @brief Shift the deque by one node
 * @param dequq The deque to shift
 * @returns The string that was shifted out, Null if none exist \
 * The retuerned string must be freed later
 */
char *sdq_shift(StringDeque *deque);

/**
 * @brief Get deque size because vscode doesn't know deque.size exist
 * @param deque The deque to get zise of
 * @returns deque size
 */
int sdq_size(StringDeque *deque);

/**
 * @brief Destroy a deque
 * @param deque THe deque to destroy
 */
void sdq_destroy(StringDeque *deque);


#endif