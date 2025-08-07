//
// Created by tomek on 8/7/25.
//


#include <string.h>
#include <ctype.h>
#include "preprocessor.h"

#include <stdlib.h>


char *preprocess(char *text) {
    char *new_text = malloc(strlen(text) + 1);
    new_text[0] = '\0';
    char *fragment = strsep(&text, "\n");
    while (text != NULL) {
        strcat(new_text, trimwhitespace(fragment));
        strcat(new_text, "\n");
        fragment = strsep(&text, "\n");
    }
    return new_text;
}

// shamelessly stolen from stackoverflow
char *trimwhitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char) *str)) str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}
