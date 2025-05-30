#include "stdio.h"
#include "stdlib.h"
#include "deque.h"
#include "hashmap.h"
#include "preprocessor.h"
#include "detection.h"
#include "argparse.h"


int main(int argc, char **argv){

    char *file_one_name = get_filename(argc, argv, 0);
    char *file_two_name = get_filename(argc, argv, 1);

    if(file_one_name == NULL || file_two_name == NULL){
        printf("Couldn't read file.");
        return EXIT_FAILURE;
    }

    FILE *file_one = fopen(file_one_name, "rb");
    FILE *file_two = fopen(file_two_name, "rb");
    printf("parsing files: %s, %s\n", file_one_name, file_two_name);
    if(file_one == NULL || file_two==NULL){
        perror("Couldn't open file");
        return EXIT_FAILURE;
    }



    printf("Normalizing text...");
    char *s1 = normalize(file_one);
    char *s2 = normalize(file_two);


    printf("\rTokenizing text.");
    StringDeque *tokens_1 = tokenize(s1);
    free(s1);
    printf("."); // FIXME: I'm fuming at windows rn. It will prematurely end the program if these are missing
    StringDeque *tokens_2 = tokenize(s2);
    free(s2);
    printf(".");


    printf("\rVectorizing text.");
    HashTable *vec1 = vectorize(tokens_1);
    printf(".");
    HashTable *vec2 = vectorize(tokens_2);
    printf(".");


    double similarity = cosine_similarity(vec1, vec2);
    ht_free(vec1); ht_free(vec2);
    printf("\rCosine Similarity between the two documents: \033[;33m");
    printf("%lf", similarity);
    printf("\033[;0m\n");


    return 0;
}