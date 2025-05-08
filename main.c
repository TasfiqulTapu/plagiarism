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

    printf("Normalized text:\n%s\n%s", normalize(file_one), normalize(file_two));


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