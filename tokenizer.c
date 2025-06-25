#include "tokenizer.h"
#include <regex.h>
#include <stdint.h>
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


struct preToken {
    int start;
    int end;
    struct Token token;
};


struct ptarrayInfo {
    int capacity;
    int elements;
    struct preToken *data;
};

struct ptarrayInfo *createPreTokenArray(int capacity) {
    struct preToken *tokens = malloc(sizeof(struct preToken) * capacity);
    struct ptarrayInfo *info = malloc(sizeof(struct ptarrayInfo));
    info->capacity = capacity;
    info->elements = 0;
    info->data = tokens;
    return info;
}


void addToPreTokenArray(struct ptarrayInfo *info, struct preToken *token) {
    if (info->capacity - info->elements < 1) {
        info->capacity *= 2;
        realloc(info->data, info->capacity * sizeof(struct preToken));
    } else {
        info->data[info->elements] = *token;
    }
}

struct ptarrayInfo *extract_text_tokens(regmatch_t **prev_matches, int types_num, char *text) {
    char *bitmask = calloc(strlen(text), sizeof(char));
    int pos = 0;
    for (int i = 0; i < types_num; i++) {
        int k = 0;
        while (prev_matches[i][k].rm_so != -1) {
            int j = 0;
            while (prev_matches[i][k].rm_eo - j++ != prev_matches[i][k].rm_so) {
                bitmask[pos] = 1;
                pos++;
            }
        }
    }
    int start = 0;
    char token = 0;
    struct ptarrayInfo *array = createPreTokenArray(10);
    for (int i = 0; i < strlen(text); i++) {
        if (!bitmask[i] && !token) {
            token = 1;
            start = i;
            i++;
        } else if (!bitmask[i] && token) {
            i++;
        } else if (bitmask[i] && token) {
            i++;
            char *value = malloc(i - start + 1);
            strncpy(value, &text[start], i - start);
            value[i - start] = '\0';
            struct preToken pt = {start, i, {TEXT, value}};
            addToPreTokenArray(array, &pt);
        }
    }

    return array;
}

struct preToken *find_matches(char *pattern, char *text) {
    regex_t regex;
    int val = regcomp(&regex, pattern, 0);
    regmatch_t *matches = malloc(strlen(text) * sizeof(regmatch_t));
    struct
    preToken *ptokens = cre
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
    struct preToken *underscore_matches = find_matches("[_]", text);
    struct preToken *star_matches = find_matches("[*]", text);
    struct preToken **previous_matches = malloc(2);
    struct preToken *text_matches = extract_text_tokens(previous_matches, 2, text);
    return 0;
}
