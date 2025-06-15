#ifndef UI_H
#define UI_H

#include "stdio.h"

void greet(int q)
{
    if (!q) return;
    printf("\n\033[;36m(\033[4m     \\/\033[24m");
    printf("    \033[33mPlagiarism checker\033[36m\n");
    printf("(\033[4m     ``o\033[24m");
    printf("   \033[33mv0-alpha\033[36m\n");
    printf(" \033[4m// \033[24m \033[4m // \033[24m\033[;0m\n");
}

void file_name_not_found(int q)
{
    fprintf(stderr, "\033[31mError: Couldn't read file.\033[0m\n");
}

void b_perror(const char *s)
{
    fprintf(stderr, "\033[31m");
    perror(s);
    fprintf(stderr, "\033[0m");
}

void update(const char *s, int q){
    if(!q) return;
    printf("\033[30m");
    fprintf(stdout,"%s", s);
    printf("\033[0m");
}

void show_filenames(char *s1, char *s2, int q){
    if(!q) return;
    printf("\033[32mParsing files:\033[0m\n");
    printf("\t%s,\t%s\n", s1, s2);
}


void likely_plagiarised(double sim){
    printf("\033[31mThe file is likey plagiarised.\033[0m\n");
    printf("Similarity: \033[33m%lf\033[0m\n",sim);
}

void likely_original(double sim){
    printf("\033[32mThe file is likey original.\033[0m\n");
    printf("Similarity: \033[33m%lf\033[0m\n",sim);
}

void print_common(StringDeque *c,HashTable *vec1, HashTable *vec2, int q){
    if(!q) return;
    while (sdq_size(c) != 0)
    {
        char *str = sdq_shift(c);
        double count1 = ht_get(vec1, str);
        double count2 = ht_get(vec2, str);
        printf("%s, ",  str);
        free(str);
    }
    printf("\b\b\n");
    sdq_destroy(c);
}
void print_table_header(char* p, char*q, char*r)
{
    printf("\033[36mCommon words:\033[0m\n");
    // printf("\033[36m%s\t%s\t%s\033[0m\n", p,q,r);
}

#endif