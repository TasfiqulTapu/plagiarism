#ifndef ARGPARSE_H
#define ARGPARSE_H

/**
 * @brief Get n-th filename in command line input
 * @param argc main argc
 * @param argv main argv
 * @param index n-th file 
 * @returns n-th element that is not -'ed
 */
char *get_filename(int argc, char **argv, int index);

/**
 * @brief Get certain settings from cli
 * @param argc main argc
 * @param argv main argv
 * @param key settings key
 * @returns setting value
 */
char *get_setting(int argc, char **argv, char *key);

#endif