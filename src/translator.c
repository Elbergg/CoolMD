//
// Created by tomek on 7/8/25.
//


#include "translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *html_val(struct Node *node, char *text) {
    char *og = malloc(strlen(text) + 100);
    switch (node->type) {
        case TEXTNODE:
            return node->value;
        case PARAGRAPH:
            strcpy(og, "<p>");
            strcat(text, "</p>");
            strcat(og, text);
            return og;
        case HEADER1:
            strcpy(og,"<h1>");
            strcat(text, "</h1>");
            strcat(og, text);
            return og;
        default:
            return text;
    }
}

char *to_html(struct Node *node) {
    if (node->children == NULL) {
        return html_val(node, "");
    }
    char *result = malloc(1000);
    char* temp  = malloc(1000);
    for (int i = 0; i < node->children->elements; i++) {
        temp = to_html(&node->children->data[i]);
        temp = html_val(node, temp);
        result = strcat(result, temp);
    }
    return result;
}
