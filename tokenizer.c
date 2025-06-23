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


regmatch_t *find_matches(char *pattern, char *text) {
    regex_t regex;
    int val = regcomp(&regex, pattern, 0);
    regmatch_t *matches = malloc(strlen(text) * sizeof(regmatch_t));
    int i = 0;
    char *start = text;
    int pos = 0;
    while (!regexec(&regex, start, 1, &matches[i], 0)) {
        pos = matches[i].rm_eo + pos;
        matches[i].rm_so = pos - 1;
        matches[i].rm_eo = pos;
        i++;
        start = &text[pos];
    }
    return matches;
}


struct Token *tokenize(char *text) {
    struct Token *tokens;
    int array_size = 0;
    int array_index = 0;
    regmatch_t *underscore_matches = find_matches("[_]", text);
    regmatch_t *star_matches = find_matches("[*]", text);
    regmatch_t *text_matches = find_matches("[^_*]+", text);
    return 0;
}
