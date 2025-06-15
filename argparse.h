#ifndef ARGPARSE_H
#define ARGPARSE_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**
 * @brief Get n-th filename in command line input
 * @param argc main argc
 * @param argv main argv
 * @param index n-th file 
 * @returns n-th element that is not -'ed
 */
char *get_filename(int argc, char **argv, int index){
    int count = 0;
    for(int i=1; i<argc; i++){
        if(argv[i][0] == '-') i++;
        else {
            if(count == index) return argv[i];
            count++;
        }
    }
    #define MAX_FILENAME_LEN 256
    char buffer[MAX_FILENAME_LEN];

    printf("Please enter path of file %d: ", index+1);

    // Fallback for when cli arguments aren't passed
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Error reading filename from stdin.\n");
            return NULL; // Return NULL if there's an error reading input
        }
    // Replace newlines to null terminators
    for(int i=0; i<MAX_FILENAME_LEN; i++){
        if(buffer[i]==' ' || buffer[i]=='\n') {
            buffer[i] = '\0';
            break;
        }
        if(buffer[i]=='\0') break;
    }
    char *filename = malloc(strlen(buffer) + 1);
    if(filename == NULL){
        perror("Filename memory alloc failed");
        return NULL;
    }
    strcpy(filename, buffer);
    return filename;
}

/**
 * @brief Get certain settings from cli
 * @deprecated We might not need it. Wasted time 🤷
 * @param argc main argc
 * @param argv main argv
 * @param key settings key
 * @returns setting value
 */
char *get_setting(int argc, char **argv, char *key){
    int len = strlen(key);
    for(int i=1; i<argc; i++){
        if(argv[i][0] == '-'){
            if(strcmp(argv[i],key)==0 && i+1<argc && argv[i+1][0]!='-')
            return argv[i+1];
        }
    }
    return NULL;
}

#endif