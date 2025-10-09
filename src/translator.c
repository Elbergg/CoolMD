//
// Created by tomek on 7/8/25.
//


#include "translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// char *html_val(struct Node *node, char *text) {
//     char *og = calloc(1, strlen(text) + 100);
//     switch (node->type) {
//         case TEXTNODE:
//             strcpy(og, node->value);
//             strcat(text, "");
//             strcat(og, text);
//             return og;
//         case PARAGRAPH:
//             strcpy(og, "<p>");
//             strcat(text, "</p>");
//             strcat(og, text);
//             return og;
//         case HEADER1:
//             strcpy(og, "<h1>");
//             strcat(text, "</h1>");
//             strcat(og, text);
//             return og;
//         case HEADER2:
//             strcpy(og, "<h2>");
//             strcat(text, "</h2>");
//             strcat(og, text);
//             return og;
//         case HEADER3:
//             strcpy(og, "<h3>");
//             strcat(text, "</h3>");
//             strcat(og, text);
//             return og;
//         case HEADER4:
//             strcpy(og, "<h4>");
//             strcat(text, "</h4>");
//             strcat(og, text);
//             return og;
//         case HEADER5:
//             strcpy(og, "<h5>");
//             strcat(text, "</h5>");
//             strcat(og, text);
//             return og;
//         case HEADER6:
//             strcpy(og, "<h6>");
//             strcat(text, "</h6>");
//             strcat(og, text);
//             return og;
//         case EMPHASIS:
//             strcpy(og, "<em>");
//             strcat(text, "</em>");
//             strcat(og, text);
//             return og;
//         case BOLD:
//             strcpy(og, "<strong>");
//             strcat(text, "</strong>");
//             strcat(og, text);
//             return og;
//         case BLOCKQUOTE:
//             strcpy(og, "<blockquote>");
//             strcat(text, "</blockquote>");
//             strcat(og, text);
//             return og;
//         default:
//             strcpy(og, "");
//             strcat(text, "");
//             strcat(og, text);
//             return og;
//     }
// }

struct dstring *html_val(struct Node *node, struct dstring *result) {
    struct dstring *prefix;
    struct dstring *suffix;
    switch (node->type) {
        case TEXTNODE:
            prefix = create_dstring("");
            suffix = create_dstring(node->value);
            break;
        case PARAGRAPH:
            prefix = create_dstring("<p>");
            suffix = create_dstring("</p>");
            break;
        case HEADER1:
            prefix = create_dstring("<h1>");
            suffix = create_dstring("</h1>");
            break;
        case HEADER2:
            prefix = create_dstring("<h2>");
            suffix = create_dstring("</h2>");
            break;
        case HEADER3:
            prefix = create_dstring("<h3>");
            suffix = create_dstring("</h3>");
            break;
        case HEADER4:
            prefix = create_dstring("<h4>");
            suffix = create_dstring("</h4>");
            break;
        case HEADER5:
            prefix = create_dstring("<h5>");
            suffix = create_dstring("</h5>");
            break;
        case HEADER6:
            prefix = create_dstring("<h6>");
            suffix = create_dstring("</h6>");
            break;
        case EMPHASIS:
            prefix = create_dstring("<em>");
            suffix = create_dstring("</em>");
            break;
        case BOLD:
            prefix = create_dstring("<strong>");
            suffix = create_dstring("</strong>");
            break;
        case BLOCKQUOTE:
            prefix = create_dstring("<blockquote>");
            suffix = create_dstring("</blockquote>");
            break;
        default:
            prefix = create_dstring("");
            suffix = create_dstring("");
            break;
    }
    concat_dstrings(prefix, result);
    result = prefix;
    concat_dstrings(result, suffix);
    return result;
}


struct dstring *to_html(struct Node *node) {
    struct narrayInfo *queue = createNodeArray(10);
    struct dstringArrayInfo *result_stack = create_dstring_array(10);
    int i = 0;
    struct narrayInfo *candidates;
    struct dstring *result = create_dstring("");
    struct narrayInfo *parent_stack = createNodeArray(10);
    intarray *index_stack = create_intarray(10);
    struct Node *parent = node;
    struct dstring *temp_result;
    add_to_dstring_array(result_stack, result);
    result = create_dstring("");
    while (node != NULL) {
        candidates = parent->children;
        if (i < candidates->elements) {
            if (candidates->data[i]->children == NULL) {
                result = html_val(candidates->data[i], result);
                i++;
            } else {
                addToNodeArray(parent_stack, parent);
                add_to_dstring_array(result_stack, result);
                parent = candidates->data[i];
                result = create_dstring("");
                add_to_intarray(index_stack, i + 1);
                i = 0;
                continue;
            }
        }
        if (i >= candidates->elements) {
            if (parent_stack->elements > 0) {
                result = html_val(parent, result);
                concat_dstrings(get_back_da(result_stack), result);
                result = get_back_da(result_stack);
                result_stack->elements--;
                if (parent_stack->elements > 0) {
                    i = get_back_ia(index_stack);
                    index_stack->elements--;
                    parent = get_back_na(parent_stack);
                    parent_stack->elements--;
                    continue;
                }
            }
            return result;
        }
    }
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
