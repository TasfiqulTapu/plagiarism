#include "stdio.h"
#include "stdlib.h"


// Using a number close to golden ratio as L2 algorithm mentioned 
// at https://www.youtube.com/watch?v=GZPqDvG615k sounds complicated to
// implement for such a simple task
#define GROWTH_FACTOR 1.6
#define INIT_BUFFER 512

/**
 * @brief Normalize text (.lower() and remove punctuation
 * @param f File pointer
 * @returns Normalized string
 */
char *normalize(FILE *f){
    if(f==NULL) return NULL;
    char *buffer = NULL;
    int len = 0;
    int byte;
    int cap_low_diff = 'a'-'A';

    int capacity = INIT_BUFFER;
    buffer = (char*)malloc(INIT_BUFFER);
    if(buffer == NULL){
        perror("Error allocating initial buffer");
        return NULL;
    }

    while((byte = fgetc(f))!=EOF){
        if(len + 1 > capacity){
            int new_capacity = (int) capacity * GROWTH_FACTOR;
            char *new_buffer = (char*)realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                perror("Error reallocating buffer");
                free(buffer); // Free the original buffer
                return NULL; // Reallocation failed
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }

        if(!((byte >= 'A' && byte <= 'Z')||(byte >= 'a' && byte <= 'z')))
         byte = 32;
        // Doing this since we will get rid off spaces in tokenizer anyway
        // byte = fgetc(f);
        // if(byte == EOF) byte = 32; //space
        if(byte >= 'A' && byte <= 'Z') byte+= cap_low_diff;
        buffer[len] = (char)byte;
        len++;
    }
    // Terminate the string
    buffer[len] = '\0';
    return buffer;
}

