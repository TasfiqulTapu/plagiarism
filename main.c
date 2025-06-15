#include "stdio.h"
#include "stdlib.h"
#include "deque.h"
#include "hashmap.h"
#include "preprocessor.h"
#include "detection.h"
#include "argparse.h"
#include "ui.h"

// SET 0 when you need only probability
// without excess logging
#define LOGGING 0

int main(int argc, char **argv)
{
    greet(LOGGING);

    char *file_one_name = get_filename(argc, argv, 0);
    char *file_two_name = get_filename(argc, argv, 1);

    if (file_one_name == NULL || file_two_name == NULL || file_one_name[0] == '\0' || file_two_name[0] == '\0')
    {
        file_name_not_found(LOGGING);
        return EXIT_FAILURE;
    }
    show_filenames(file_one_name, file_two_name, LOGGING);
    
    FILE *file_one = fopen(file_one_name, "rb");
    FILE *file_two = fopen(file_two_name, "rb");
    
    if (file_one == NULL || file_two == NULL)
    {
        b_perror("Error opening file");
        return EXIT_FAILURE;
    }

    update("Normalizing text...\n", LOGGING);
    char *s1 = normalize(file_one);
    char *s2 = normalize(file_two);

    fclose(file_one);
    fclose(file_two);

    update("Tokenizing text.", LOGGING);
    StringDeque *tokens_1 = tokenize(s1);
    free(s1);
    update(".", LOGGING); // FIXME: I'm fuming at windows rn. It will prematurely end the program if these are missing
    StringDeque *tokens_2 = tokenize(s2);
    free(s2);
    update(".\n", LOGGING);

    update("Vectorizing text.", LOGGING);
    HashTable *vec1 = vectorize(tokens_1);
    update(".", LOGGING);
    HashTable *vec2 = vectorize(tokens_2);
    update(".\n", LOGGING);

    double similarity = cosine_similarity(vec1, vec2);
    StringDeque *common = common_words(vec1, vec2);
    if(LOGGING){
        if(similarity > 0.55){
            likely_plagiarised(similarity);
        }else{
            likely_original(similarity);
        }
        print_table_header(file_one_name, "word", file_two_name);
        print_common(common,vec1, vec2, LOGGING);
    }else{
        printf("%lf",similarity);
    }

    ht_free(vec1);
    ht_free(vec2);
    return 0;
}