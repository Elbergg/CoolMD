#include "tokenizer.h"
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "merge.h"

// struct Token *blockerize(char *text) {
//     char *block = strtok(text, "\n\n");
//     while (block != NULL) {
//         struct Token *tokens = tokenize(block);
//     }
// }

// struct Token *fragmentize(char *block) {
//     char *fragment = strtok(block, "\n");
//     while (fragment != NULL) {
//         struct Token *tokens = tokenize(fragment);
//     }
// }


struct ptarrayInfo *createPreTokenArray(int capacity) {
    struct preToken *tokens = malloc(sizeof(struct preToken) * capacity);
    struct ptarrayInfo *info = malloc(sizeof(struct ptarrayInfo));
    info->capacity = capacity;
    info->elements = 0;
    info->data = tokens;
    return info;
}


struct tarrayInfo *createTokenArray(int capacity) {
    struct Token *tokens = malloc(sizeof(struct Token) * capacity);
    struct tarrayInfo *info = malloc(sizeof(struct tarrayInfo));
    info->capacity = capacity;
    info->elements = 0;
    info->data = tokens;
    return info;
}

void addToTokenArray(struct tarrayInfo *info, struct Token *token) {
    if (info->capacity - info->elements < 1) {
        info->capacity *= 2;

        info->data = realloc(info->data, info->capacity * sizeof(struct Token));
    }
    info->data[info->elements] = *token;
    info->elements++;
}


void addToPreTokenArray(struct ptarrayInfo *info, struct preToken *token) {
    if (info->capacity - info->elements < 1) {
        info->capacity *= 2;

        info->data = realloc(info->data, info->capacity * sizeof(struct preToken));
    }
    info->data[info->elements] = *token;
    info->elements++;
}

struct ptarrayInfo *extract_text_tokens(struct ptarrayInfo **prev_matches, int types_num, char *text) {
    char *bitmask = calloc(strlen(text), sizeof(char));
    for (int i = 0; i < types_num; i++) {
        int k = 0;
        while (k < prev_matches[i]->elements) {
            int j = 0;
            int pos = prev_matches[i]->data[k].start;
            while (prev_matches[i]->data[k].end - j++ != prev_matches[i]->data[k].start) {
                bitmask[pos] = 1;
                pos++;
            }
            k++;
        }
    }
    int start = 0;
    char token = 0;
    char *value = 0;
    struct ptarrayInfo *array = createPreTokenArray(10);
    for (int i = 0; i < strlen(text); i++) {
        if (!bitmask[i] && !token) {
            token = 1;
            start = i;
        } else if (!bitmask[i] && token) {
        } else if (bitmask[i] && token) {
            token = 0;
            value = malloc(i - start + 1);
            strncpy(value, &text[start], i - start);
            value[i - start] = '\0';
            struct preToken pt = {start, i, {TEXT, value}};
            addToPreTokenArray(array, &pt);
        }
    }
    if (token) {
        token = 0;
        value = malloc(strlen(text) - start + 1);
        strncpy(value, &text[start], strlen(text) - start);
        value[strlen(text) - start] = '\0';
        struct preToken pt = {start, strlen(text), {TEXT, value}};
        addToPreTokenArray(array, &pt);
    }
    free(bitmask);
    return array;
}

struct ptarrayInfo *find_matches(char *pattern, char *text, enum tokenType type) {
    regex_t regex;
    int val = regcomp(&regex, pattern, 0);
    regmatch_t *matches = malloc(strlen(text) * sizeof(regmatch_t));
    struct ptarrayInfo *ptokens = createPreTokenArray(10);
    int i = 0;
    char *start = text;
    int pos = 0;
    while (!regexec(&regex, start, 1, &matches[i], 0)) {
        pos = matches[i].rm_eo + pos;
        matches[i].rm_so = pos - 1;
        matches[i].rm_eo = pos;
        struct preToken pt = {matches[i].rm_so, matches[i].rm_eo, {type, strdup("")}};
        addToPreTokenArray(ptokens, &pt);
        i++;
        start = &text[pos];
    }
    free(matches);
    return ptokens;
}


struct tarrayInfo *sort_tokens(struct ptarrayInfo **pretokens, int n) {
    int size = 0;
    for (int i = 0; i < n; i++) {
        size += pretokens[i]->elements;
    }
    struct preToken *res = malloc(sizeof(struct preToken) * size);
    int i = 0;
    int cur = 0;
    do {
        memcpy(res + cur, pretokens[i]->data, pretokens[i]->elements * sizeof(struct preToken));
        cur += pretokens[i]->elements;
        i++;
    } while (i < n);
    mergeSort(res, 0, size - 1);
    struct tarrayInfo *res_tokens = createTokenArray(10);
    for (int i = 0; i < size; i++) {
        res[i].token.parsed = 0;
        addToTokenArray(res_tokens, &res[i].token);
    }
    free(res);
    return res_tokens;
}


void free_ptarray(struct ptarrayInfo *ptokens) {
    // for (int i = 0; i < ptokens->elements; i++) {
    //     free(ptokens->data[i]);
    // }
    free(ptokens->data);
    free(ptokens);
}

void free_tarray(struct tarrayInfo *tokens) {
    for (int i = 0; i < tokens->elements; i++) {
        free(tokens->data[i].value);
    }
    free(tokens->data);
    free(tokens);
}

struct tarrayInfo *tokenize(char *text) {
    // TODO: FIX MEMORY LEAKS
    struct Token *tokens;
    int array_size = 0;
    int array_index = 0;
    struct ptarrayInfo *underscore_matches = find_matches("[_]", text, UNDERSCORE);
    struct ptarrayInfo *star_matches = find_matches("[*]", text, STAR);
    struct ptarrayInfo *newlines = find_matches("[\n]", text, NEWLINE);
    struct ptarrayInfo *hashtags = find_matches("[#]", text, HASH);
    struct ptarrayInfo *spaces = find_matches("[ ]", text, SPACE);
    struct ptarrayInfo **previous_matches = malloc(5 * sizeof(struct ptarrayInfo *));
    previous_matches[0] = underscore_matches;
    previous_matches[1] = star_matches;
    previous_matches[2] = newlines;
    previous_matches[3] = hashtags;
    previous_matches[4] = spaces;
    struct ptarrayInfo *text_matches = extract_text_tokens(previous_matches, 5, text);
    struct ptarrayInfo **all_matches = malloc(6 * sizeof(struct ptarrayInfo *));
    all_matches[0] = underscore_matches;
    all_matches[1] = star_matches;
    all_matches[2] = text_matches;
    all_matches[3] = newlines;
    all_matches[4] = hashtags;
    all_matches[5] = spaces;
    struct tarrayInfo *sorted_tokens = sort_tokens(all_matches, 6);
    free_ptarray(underscore_matches);
    free_ptarray(star_matches);
    free_ptarray(newlines);
    free_ptarray(text_matches);
    free_ptarray(spaces);
    free_ptarray(hashtags);
    free(previous_matches);
    free(all_matches);


    return sorted_tokens;
}
