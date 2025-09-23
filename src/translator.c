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
        case HEADER2:
            strcpy(og, "<h2>");
            strcat(text, "</h2>");
            strcat(og, text);
            return og;
        case HEADER3:
            strcpy(og, "<h3>");
            strcat(text, "</h3>");
            strcat(og, text);
            return og;
        case HEADER4:
            strcpy(og, "<h4>");
            strcat(text, "</h4>");
            strcat(og, text);
            return og;
        case HEADER5:
            strcpy(og, "<h5>");
            strcat(text, "</h5>");
            strcat(og, text);
            return og;
        case HEADER6:
            strcpy(og, "<h6>");
            strcat(text, "</h6>");
            strcat(og, text);
            return og;
        case EMPHASIS:
            strcpy(og, "<em>");
            strcat(text, "</em>");
            strcat(og, text);
            return og;
        case BOLD:
            strcpy(og, "<strong>");
            strcat(text, "</strong>");
            strcat(og, text);
            return og;
        case BLOCKQUOTE:
            strcpy(og, "<blockquote>");
            strcat(text, "</blockquote>");
            strcat(og, text);
            return og;
        default:
            strcpy(og, "");
            strcat(text, "");
            strcat(og, text);
            return og;
    }
}


char *to_html(struct Node *node) {
    // TODO: USE ITERATION INSTEAD OF RECURSION
    if (node->children == NULL) {
        return html_val(node, "");
    }
    // TODO: USE DYNAMIC STRINGS INSTEAD OF THIS
    char *result = calloc(1, 1000);
    // char *temp = malloc(1000);
    for (int i = 0; i < node->children->elements; i++) {
        char *val = to_html(node->children->data[i]);
        result = strcat(result, val);
        free(val);
    }
    char *val = html_val(node, result);
    strcpy(result, val);
    free(val);
    return result;
}


char *raw_val(struct Node *node, char *text) {
    char *og = calloc(1, strlen(text) + 100);
    switch (node->type) {
        default:
            strcpy(og, "");
            strcat(text, "");
            strcat(og, text);
            return og;
    }
}


char *to_raw(struct Node *node) {
    // TODO: USE ITERATION INSTEAD OF RECURSION
    if (node->children == NULL) {
        return strdup(node->value);
    }
    // TODO: USE DYNAMIC STRINGS INSTEAD OF THIS
    char *result = calloc(1, 1000);
    for (int i = 0; i < node->children->elements; i++) {
        char *val = to_raw(node->children->data[i]);
        result = strcat(result, val);
        free(val);
    }
    char *val = raw_val(node, result);
    strcpy(result, val);
    free(val);
    return result;
}
