//
// Created by tomek on 7/24/25.
//
#include "coolmd.h"

char *compile(char *text) {
    struct tarrayInfo *tarray = tokenize(text);
    struct narrayInfo *narray = parse(tarray->data, 0, tarray->elements);
    char *result = to_html(narray->data[0]);
    free_tarray(tarray);
    free_narray(narray);
    return result;
}
