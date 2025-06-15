#ifndef NOKOL_H
#define NOKOL_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "deque.h"

// Using a number close to golden ratio as mentioned
// at (Ideal array growth factor) https://www.youtube.com/watch?v=GZPqDvG615k
#define GROWTH_FACTOR 1.6
#define INIT_BUFFER 512

/**
 * @brief Normalize text (lower() and remove punctuation)
 * @param f File pointer
 * @returns Normalized string
 */
char *normalize(FILE *f)
{
    if (f == NULL)
        return NULL;
    char *buffer = NULL;
    int len = 0;
    int byte;
    int cap_low_diff = 'a' - 'A';

    int capacity = INIT_BUFFER;
    buffer = (char *)malloc(INIT_BUFFER);
    if (buffer == NULL)
    {
        perror("Error allocating initial buffer");
        return NULL;
    }

    while ((byte = fgetc(f)) != EOF)
    {
        if (len + 2 > capacity)
        {
            int new_capacity = (int)capacity * GROWTH_FACTOR;
            char *new_buffer = (char *)realloc(buffer, new_capacity);

            if (new_buffer == NULL)
            {
                perror("Error reallocating buffer");
                free(buffer); // Free the original buffer
                return NULL;  // Reallocation failed
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }

        // Only accept /[a-zA-Z0-9_]/
        if (!((byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z') || (byte >= '0' && byte <= '9')) && byte != '_')
            byte = 32;
        // ^ Doing this since we will get rid off spaces in tokenizer anyway
        // byte = fgetc(f);
        // if(byte == EOF) byte = 32; //space
        if (byte >= 'A' && byte <= 'Z')
            byte += cap_low_diff;
        buffer[len] = (char)byte;
        len++;
    }
    // Terminate the string
    buffer[len] = '\0';
    return buffer;
}

// StopWords to remove because they hold little to no value.
// Further reading at https://en.wikipedia.org/wiki/Stop_word
// Stopwords list collected from: https://gist.github.com/sebleier/554280
char *STOP_WORDS[] = {
    "a", "about", "above", "after", "again", "against", "all", "am", "an", "and",
    "any", "are", "as", "at", "be", "because", "been", "being", "below", "between",
    "both", "but", "by", "can", "could", "did", "do", "does", "doing", "don",
    "down", "during", "each", "few", "for", "from", "further", "had", "has", "have",
    "having", "he", "her", "here", "hers", "herself", "him", "himself", "his", "how",
    "i", "if", "in", "into", "is", "it", "its", "itself", "just", "me", "more", "most",
    "my", "myself", "no", "nor", "not", "now", "of", "off", "on", "once", "only",
    "or", "other", "our", "ours", "ourselves", "out", "over", "own", "same", "she",
    "should", "so", "some", "such", "s", "t", "than", "that", "the", "their", "theirs",
    "them", "themselves", "then", "there", "these", "they", "this", "those", "through",
    "to", "too", "under", "until", "up", "very", "was", "we", "were", "what", "when",
    "where", "which", "while", "who", "whom", "why", "will", "with", "would", "you",
    "your", "yours", "yourself", "yourselves",
    NULL};

/**
 * @brief Check wether a word is a stopword or not
 * @param word Word to check
 * @returns 0 if false, 1 if true
 */
// TODO: Futher optimize?
int is_stop_word(char *word)
{
    if (word == NULL)
    {
        return 0;
    }
    for (int i = 0; STOP_WORDS[i] != NULL; ++i)
    {
        if (strcmp(word, STOP_WORDS[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Tokenize text into individual words and remove stopwords
 * @param str An array of normalized characters
 * @returns StringDeque of tokens(words)
 */
StringDeque *tokenize(char *str)
{
    if (str == NULL)
    {
        perror("Tokenizer received NULL sting");
        return NULL;
    }

    StringDeque *tokens = create_str_deque();
    if (tokens == NULL)
    {
        perror("Failed to init Tokenizer deque");
        return NULL;
    }

    // Pointer to the start of the str, we increment this to get next
    const char *current = str;
    const char *words_start_loc = NULL;

    while (*current != '\0')
    {

        // Skip forward until we find non-empty chars
        while (*current != '\0' && *current == ' ')
            current++;
        if (*current == '\0')
            break;

        words_start_loc = current;
        // Skip forward until we find empty chars
        while (*current != '\0' && *current != ' ')
            current++;

        // Size_t is more suitable for this task instead of int
        size_t word_len = current - words_start_loc;

        if (word_len > 0)
        {
            // Allocate temporary buffer for the word + terminator
            char *word = (char *)malloc(word_len + 1);
            if (!word)
            {
                perror("Failed to allocate memory for word");
                // Clean up already allocated deque memory before returning NULL
                // For memory safety
                sdq_destroy(tokens);
                return NULL;
            }

            // Copy the word characters into word buffer
            strncpy(word, words_start_loc, word_len);
            word[word_len] = '\0';

            // Check if it's a stop word
            if (!is_stop_word(word))
            {
                sdq_push(tokens, word);
            }
            // Freeeeeeedom for the temporary buffer (mem safety)
            free(word);
        }
    }
    return tokens;
}

#endif