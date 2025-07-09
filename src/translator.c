//
// Created by tomek on 7/8/25.
//


#include "translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *html_val(struct Node *node, char *text) {
    char *og = "";
    switch (node->type) {
        case TEXTNODE:
            return node->value;
        case PARAGRAPH:
            og = "<p>";
            strcat(text, "</p>");
            strcat(og, text);
            return og;
        case HEADER1:
            og = "<h1>";
            strcat(text, "</h1>");
            strcat(og, text);
            return og;
    }
}

char *to_html(struct Node *node) {
    if (node->children == NULL) {
        return html_val(node, "");
    }
    char *result = "\0";
    for (int i = 0; i < node->children->elements; i++) {
        result = to_html(node);
        result = html_val(node, result);
    }
    return result;
}
