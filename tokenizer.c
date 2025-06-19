#include "tokenizer.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Token *blockerize(char *text) {
    char *block = strtok(text, "\n\n");
    while (block != NULL) {
        struct Token *tokens = fragmentize(block);
    }
}

struct Token *fragmentize(char *block) {
    char *fragment = strtok(block, "\n");
    while (fragment != NULL) {
        struct Token *tokens = tokenize(fragment);
    }
}


struct Token *tokenize(char *text) {
    struct Token *tokens;
    int array_size = 0;
    regex_t regex;
    int underscore = regcomp(&regex, "[_]", 0);
    regmatch_t *matches = malloc(strlen(text));
    if (regexec(&regex, text, 2, matches, 0)) {
        printf("regexec failed\n");
    } else {
        realloc(tokens, array_size + sizeof(struct Token) *);
    }
    return 0;
}
