#include "stdio.h"
#include "stdlib.h"
#include "deque.h"
#include "nokol.h"
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
    if(file_one == NULL || file_two==NULL){
        perror("Couldn't open file");
        return EXIT_FAILURE;
    }
    printf("parsing - %s, %s\n", file_one_name, file_two_name);

    char *s1 = normalize(file_one);
    char *s2 = normalize(file_two);
    // printf("Normalized text:\n%s\n%s\n", s1, s2);


    StringDeque *tokens_1 = tokenize(s1);
    int count_1=0, count_2 = 0;
    StringDeque *tokens_2 = tokenize(s2);

    while(sdq_size(tokens_1) != 0){
        char *str = sdq_shift(tokens_1);
        printf("%s ", str);
        count_1++;
        free(str);
    }
    sdq_destroy(tokens_1);
    while(sdq_size(tokens_2) != 0){
        char *str = sdq_shift(tokens_2);
        printf("%s ", str);
        count_2++;
        free(str);
    }
    sdq_destroy(tokens_2);
    
    printf("After removing stopwords:\n");
    printf("First file word count: \033[;33m%d\033[;0m\n",count_1);
    printf("Second file word count: \033[;33m%d\033[;0m\n",count_2);


    // StringDeque *new_queue = create_str_deque();
    // for(int i=1; i<argc; i++){
    //     sdq_push(new_queue, argv[i]);
    // }
    // while(sdq_size(new_queue) != 0){
    //     char *str = sdq_shift(new_queue);
    //     printf("%s\n", str);
    //     free(str);
    // }
    // sdq_destroy(new_queue);

    return 0;
}