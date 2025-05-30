#ifndef ARGPARSE_H
#define ARGPARSE_H

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
    return NULL;
}

/**
 * @brief Get certain settings from cli
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

/**
 * @brief Get wether -q is set
 * @param argc main argc
 * @param argv main argv
 * @returns true or false
 */
int get_quiet(int argc, char **argv){
    for(int i=1; i<argc; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1]=='q') return 1;
        }
    }
    return 0;
}



#endif