//
// Created by tomek on 7/8/25.
//


#include "translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *html_val(struct Node *node, char *text) {
    char *og = calloc(1, strlen(text) + 100);
    switch (node->type) {
        case TEXTNODE:
            strcpy(og, node->value);
            strcat(text, "");
            strcat(og, text);
            return og;
        case PARAGRAPH:
            strcpy(og, "<p>");
            strcat(text, "</p>");
            strcat(og, text);
            return og;
        case HEADER1:
            strcpy(og, "<h1>");
            strcat(text, "</h1>");
            strcat(og, text);
            return og;
        case EMPHASIS:
            strcpy(og, "<em>");
            strcat(text, "</em>");
            strcat(og, text);
            return og;
        default:
            strcpy(og, "");
            strcat(text, "");
            strcat(og, text);
            return og;
    }
}


// char *to_html(struct Node *node) {
//     char stop = 0;
//     while (!stop) {
//
//         char *result = malloc(1000);
//         char *temp = malloc(1000);
//         for (int i = 0; i < node->children->elements; i++) {
//             strcpy(temp, to_html(&node->children->data[i])); //recurse into
//             result = strcat(result, temp);
//         }
//     }
// }


char *to_html(struct Node *node) {
    if (node->children == NULL) {
        return html_val(node, "");
    }
    // TODO: USE DYNAMIC STRINGS INSTEAD OF THIS
    char *result = calloc(1, 1000);
    // char *temp = malloc(1000);
    for (int i = 0; i < node->children->elements; i++) {
        char *val = to_html(&node->children->data[i]);
        result = strcat(result, val);
        free(val);
    }
    char *val = html_val(node, result);
    strcpy(result, val);
    free(val);
    return result;
}
