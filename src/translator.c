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


void html_val(struct Node *node, struct dstringArrayInfo *prefixes, struct dstringArrayInfo *suffixes) {
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
    add_to_dstring_array(prefixes, prefix);
    add_to_dstring_array(suffixes, suffix);
}


struct dstring *to_html(struct Node *node) {
    struct narrayInfo *queue = createNodeArray(10);
    struct dstringArrayInfo *result_queue = create_dstring_array(10);
    int i = 0;
    struct narrayInfo *candidates = node->children;
    struct dstring *result = create_dstring("");
    struct narrayInfo *parent_stack = createNodeArray(10);
    addToNodeArray(parent_stack, node);
    while (parent_stack->elements != 0) {
        if (i == candidates->elements) {
            candidates = get_back_na(parent_stack);
            parent_stack->elements--;
            continue;
        }
        if (candidates->data[i]->children == NULL) {
            html_val(candidates->data[i], result_queue, result_queue);
            i++;
        } else {
            addToNodeArray(parent_stack, candidates->data[i]);
            candidates = candidates->data[i]->children;
            i = 0;
            continue;
        }
        if (i == candidates->elements) {
            while (result_queue->elements > 0) {
                concat_dstrings(get_back_da(result_queue), result);
                result = get_back_da(result_queue);
                result_queue->elements--;
                concat_dstrings(result, get_back_da(result_queue));
                result_queue->elements--;
            }
            html_val(get_back_na(parent_stack), result_queue, result_queue);
            concat_dstrings(get_back_da(result_queue), result);
            result = get_back_da(result_queue);
            result_queue->elements--;
            concat_dstrings(result, get_back_da(result_queue));
            result_queue->elements--;
            add_to_dstring_array(result_queue, result);
            candidates = get_back_na(parent_stack)->children;
            parent_stack->elements--;
            continue;
            if (queue->elements > 0) {
                html_val(get_back_na(queue), result_queue, result_queue);
                candidates = get_back_na(queue)->children;
                queue->elements--;
                i = 0;
                continue;
            }


            //  TODO ADD ONE QUEUE FOR ALL THE ADDED STRINGS
            if (queue->elements == 0) {
                return result;
            }
        }
    }

    // if (candidates->data[i]->children == NULL) {
    //     html_val(candidates->data[i], prefix_queue, suffix_queue);
    //     ps++;
    //     concat_dstrings(prefix_queue->data[ps], result_queue->data[rs]);
    //     result = prefix_queue->data[ps];
    //     concat_dstrings(result, suffix_queue->data[ps]);
    //     ps--;
    //     prefix_queue->elements--;
    //     suffix_queue->elements--;
    //     i++;
    // } else {
    //     if (i != candidates->elements - 1) {
    //         addToNodeArray(queue, candidates->data[i + 1]);
    //         q++;
    //     }
    //     html_val(candidates->data[i], prefix_queue, suffix_queue);
    //     ps++;
    //     candidates = candidates->data[i]->children;
    //     i = 0;
    // }
    // if (i == candidates->elements) {
    //     while (queue->data[q]->children == NULL) {
    //         html_val(queue->data[q], prefix_queue, suffix_queue);
    //         ps++;
    //         q--;
    //         queue->elements -= 1;
    //         concat_dstrings(prefix_queue->data[ps], result);
    //         result = prefix_queue->data[ps];
    //         concat_dstrings(result, suffix_queue->data[ps]);
    //         ps--;
    //         i++;
    //         prefix_queue->elements--;
    //         suffix_queue->elements--;
    //     }
    //     while (ps > -1) {
    //         concat_dstrings(prefix_queue->data[ps], result);
    //         result = prefix_queue->data[ps];
    //         concat_dstrings(result, suffix_queue->data[ps]);
    //         ps--;
    //         prefix_queue->elements--;
    //         suffix_queue->elements--;
    //     }
    //     html_val(queue->data[q], prefix_queue, suffix_queue);
    //     candidates = queue->data[q]->children;
    //     i = 0;
    //     q--;
    //     queue->elements--;
    // }
    // if (node->children == NULL) {
    //     return html_val(node, "");
    // }
    // // TODO: USE DYNAMIC STRINGS INSTEAD OF THIS
    // struct dstring *result = create_dstring("");
    // // char *temp = malloc(1000);
    // for (int i = 0; i < node->children->elements; i++) {
    //     struct dstring *val = to_html(node->children->data[i]);
    //     concat_dstrings(result, val);
    // }
    // struct dstring *val = html_val(node, result);
    // return val;
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
