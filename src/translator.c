//
// Created by tomek on 7/8/25.
//


#include "translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct dstring *html_val(struct Node *node, struct dstring *result) {
    struct dstring *prefix;
    struct dstring *suffix;
    switch (node->type) {
        case TEXTNODE:
            append_to_dstring(result, node->value);
            return result;
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
    struct dstringArrayInfo *result_stack = create_dstring_array(10);
    int i = 0;
    struct narrayInfo *candidates;
    struct dstring *result = create_dstring("");
    struct narrayInfo *parent_stack = createNodeArray(10);
    intarray *index_stack = create_intarray(10);
    struct Node *parent = node;
    add_to_dstring_array(result_stack, result);
    while (node != NULL) {
        candidates = parent->children;
        if (i < candidates->elements && candidates->data[i] != NULL) {
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
            free(parent_stack->data);
            free(parent_stack);
            free(index_stack->data);
            free(index_stack);
            struct dstring *final = create_dstring("");
            append_to_dstring(final, result->data);
            free_darray(result_stack);
            return final;
        }
    }
}

struct dstring *raw_val(struct Node *node, struct dstring *result) {
    struct dstring *prefix = create_dstring("");
    struct dstring *suffix;
    if (node->value) {
        suffix = create_dstring("");
    } else {
        suffix = create_dstring("");
    }
    concat_dstrings(prefix, result);
    result = prefix;
    concat_dstrings(result, suffix);
    return result;
}


struct dstring *to_raw(struct Node *node) {
    struct dstringArrayInfo *result_stack = create_dstring_array(10);
    int i = 0;
    struct narrayInfo *candidates;
    struct dstring *result = create_dstring("");
    struct narrayInfo *parent_stack = createNodeArray(10);
    intarray *index_stack = create_intarray(10);
    struct Node *parent = node;
    add_to_dstring_array(result_stack, result);
    while (node != NULL) {
        candidates = parent->children;
        if (i < candidates->elements && candidates->data[i] != NULL) {
            if (candidates->data[i]->children == NULL) {
                result = raw_val(candidates->data[i], result);
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
                result = raw_val(parent, result);
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
            free(parent_stack->data);
            free(parent_stack);
            free(index_stack->data);
            free(index_stack);
            struct dstring *final = create_dstring("");
            append_to_dstring(final, result->data);
            free_darray(result_stack);
            return final;
        }
    }
}

// struct dstring *to_raw(struct Node *node) {
//     // TODO: USE ITERATION INSTEAD OF RECURSION
//     if (node->children == NULL) {
//         return strdup(node->value);
//     }
//     // TODO: USE DYNAMIC STRINGS INSTEAD OF THIS
//     char *result = calloc(1, 1000);
//     for (int i = 0; i < node->children->elements; i++) {
//         char *val = to_raw(node->children->data[i]);
//         result = strcat(result, val);
//         free(val);
//     }
//     char *val = raw_val(node, result);
//     strcpy(result, val);
//     free(val);
//     return result;
// }
