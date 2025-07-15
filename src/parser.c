//
// Created by tomek on 6/29/25.
//
#include "parser.h"

#include <string.h>

void parse_terminals(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
    for (int i = index; i < length; i++) {
        switch (tokens[i].type) {
            case UNDERSCORE:
                i = parse_underscores(tokens, i, length, nodes);
                break;
            case TEXT:
                i = parse_text(tokens, i, length, nodes);
                break;
            case NEWLINE:
                i = parse_newline(tokens, i, length, nodes);
                break;
            case HASH:
                i = parse_hashtags(tokens, i, length, nodes);
            case HASHSPACE:
                i = parse_one_hashtag(tokens, i, length, nodes);
            default: ;
        }
    }
}

int parse_hashtags(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
    // TODO: MAKE #Hello parse as two textnodes also implement parsing h2 and h3
    if (index + 1 < length && tokens[index + 1].type == HASH && index + 2 < length && tokens[index + 2].type ==
        HASHSPACE) {
        return parse_three_hashtags(tokens, index, length, nodes);
    }
    if (index + 1 < length && tokens[index + 1].type == HASHSPACE) {
        return parse_two_hashtags(tokens, index, length, nodes);
    }
}


int parse_three_hashtags(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
}

int parse_two_hashtags(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
}

int parse_one_hashtag(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
    struct Node *node = calloc(1, sizeof(struct Node));
    node->type = HASHSPACENODE;
    node->value = strdup("# ");
    addToNodeArray(nodes, node);
    // free_node(node);
    return index;
}

int parse_newline(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
    if (index + 1 <= length && tokens[index + 1].type == NEWLINE) {
        struct Node *node = calloc(1, sizeof(struct Node));
        node->type = DNL;
        node->value = strdup("\n\n");
        addToNodeArray(nodes, node);
        // free_node(node);
        return index + 1;
    } else {
        struct Node *node = calloc(1, sizeof(struct Node));
        node->type = SNL;
        node->value = strdup("\n");
        addToNodeArray(nodes, node);
        // free_node(node);
        return index;
    }
}

void parse_h1(struct narrayInfo *nodes) {
    struct narrayInfo *info = createNodeArray(10);
    struct narrayInfo *candidates = nodes->data[0]->children;
    struct Node *headnode = calloc(1, sizeof(struct Node));
    headnode->type = HEADER1;
    char added = 0;
    for (int i = 0; i < candidates->elements; i++) {
        if (candidates->data[i]->type == HASHSPACENODE && i < candidates->elements - 1) {
            added = 1;
            headnode->children = createNodeArray(10);
            addToNodeArray(info, candidates->data[i]);
            addToNodeArray(headnode->children, candidates->data[i]);
            i++;
            if (candidates->data[i]->type == SENTENCE || candidates->data[i]->type == PARAGRAPH) {
                while (((i <
                         candidates
                         ->elements) && (candidates->data[i]->type == SENTENCE || candidates->data[i]->type ==
                                         PARAGRAPH)
                        && candidates->data[i]->type != SNL)) {
                    addToNodeArray(headnode->children, candidates->data[i]);
                    i++;
                }
            }
            if (i <
                candidates
                ->elements && candidates->data[i]->type == SNL) {
                addToNodeArray(headnode->children, candidates->data[i]);
            }
            delete_last_n_nodes(info, 1);
            addToNodeArray(info, headnode);
        } else {
            addToNodeArray(info, candidates->data[i]);
        }
    }
    if (!added) {
        free(headnode);
    }
    // free(headnode);
    free(nodes->data[0]->children->data);
    free(nodes->data[0]->children);
    nodes->data[0]->children = info;
}

void parse_headers(struct narrayInfo *nodes) {
    parse_h1(nodes);
};

void parse_non_terminals(struct narrayInfo *nodes) {
    parse_sentences(nodes);
    parse_headers(nodes);
    parse_paragraphs(nodes);
}

void parse_paragraphs(struct narrayInfo *nodes) {
    struct narrayInfo *info = createNodeArray(10);
    struct narrayInfo *candidates = nodes->data[0]->children;
    struct Node *parnode = calloc(1, sizeof(struct Node));
    parnode->type = PARAGRAPH;
    char added = 0;
    for (int i = 0; i < candidates->elements; i++) {
        if (i < candidates->elements - 1 && candidates->data[i]->type == SENTENCE) {
            parnode->children = createNodeArray(10);
            addToNodeArray(info, candidates->data[i]);
            addToNodeArray(parnode->children, candidates->data[i]);
            i++;
            while ((candidates->data[i]->type == SENTENCE || candidates->data[i]->type == SNL) && i < candidates->
                   elements
                   - 1) {
                addToNodeArray(info, candidates->data[i]);
                addToNodeArray(parnode->children, candidates->data[i]);
                i++;
            }
            if (candidates->data[i]->type == DNL) {
                added = 1;
                addToNodeArray(parnode->children, candidates->data[i]);
                delete_last_n_nodes(info, parnode->children->elements - 1);
                addToNodeArray(info, parnode);
            } else {
                addToNodeArray(info, candidates->data[i]);
                free(parnode->children);
            }
        } else {
            addToNodeArray(info, candidates->data[i]);
        }
    }
    if (!added) {
        free(parnode);
    }
    // free(parnode);
    free(nodes->data[0]->children->data);
    free(nodes->data[0]->children);
    nodes->data[0]->children = info;
}

struct narrayInfo *parse(struct Token *tokens, int index, int length) {
    struct narrayInfo *node = createNodeArray(1);
    struct Node *head = calloc(1, sizeof(struct Node));
    head->type = BODY;
    head->children = createNodeArray(10);
    addToNodeArray(node, head);
    // free(head->children);


    tokens = parse_spaces(tokens, &length);
    parse_terminals(tokens, index, length, node->data[0]->children);
    parse_non_terminals(node);
    // free(head);
    // free(head->children);
    // for (int i = 0; i < length; i++) {
    //     free(tokens[i].value);
    // }
    free(tokens);
    return node;
}

struct Token *parse_spaces(struct Token *tokens, int *length) {
    int reductions = 0;
    struct tarrayInfo *info = createTokenArray(10);
    for (int i = 0; i < *length; i++) {
        if (tokens[i].type == HASH && i < *length - 1 && tokens[i + 1].type == SPACE) {
            struct Token *token = malloc(sizeof(struct Token));
            token->type = HASHSPACE;
            token->value = strdup("# ");
            addToTokenArray(info, token);
            i++;
            reductions++;
            free(token->value);
            free(token);
            continue;
        }
        if (tokens[i].type == SPACE) {
            tokens[i].type = TEXT;
            free(tokens[i].value);
            tokens[i].value = strdup(" ");
        }
        addToTokenArray(info, &tokens[i]);
    }
    struct Token *ret_tokens = info->data;
    free(info);
    // free(tokens);
    *length -= reductions;
    return ret_tokens;
}

void parse_sentences(struct narrayInfo *nodes) {
    struct narrayInfo *info = createNodeArray(10);
    char sentence = 0;
    struct narrayInfo *candidates = nodes->data[0]->children;
    char added = 0;
    struct Node *sentnode = NULL;
    struct narrayInfo *children = NULL;
    for (int i = 0; i < candidates->elements; i++) {
        if ((candidates->data[i]->type == EMPHASIS || candidates->data[i]->type == TEXTNODE || candidates->data[i]->type
             ==
             BOLD) && sentence == 0) {
            sentence = 1;
            added = 1;
            sentnode = calloc(1, sizeof(struct Node));
            sentnode->type = SENTENCE;
            sentnode->children = createNodeArray(10);
            addToNodeArray(sentnode->children, candidates->data[i]);
            addToNodeArray(info, sentnode);
            children = sentnode->children;
            // free(sentnode);
            // sentnode = NULL;
        } else if ((candidates->data[i]->type == EMPHASIS || candidates->data[i]->type == TEXTNODE || candidates->data[
                        i]->
                    type == BOLD) && sentence == 1) {
            addToNodeArray(children, candidates->data[i]);
        } else {
            sentence = 0;
            addToNodeArray(info, candidates->data[i]);
        }
        // }
        // if (added) {
    }
    free(nodes->data[0]->children->data);
    free(nodes->data[0]->children);
    nodes->data[0]->children = info;
    // } else {
    //     free(info);
    // }
    // if (sentnode->value != NULL) {
    //     free(sentnode->value);
    // }
    // free(sentnode->value);
    // free(sentnode);
}


int parse_underscores(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
    // TODO: IMPLEMENT PARSING TWO AND THREE UNDERSCORES
    if (index + 1 < length && tokens[index + 1].type == UNDERSCORE && index + 2 < length && tokens[index + 2].type
        ==
        UNDERSCORE) {
        return parse_three_underscores(tokens, index, length, nodes);
    }
    if (index + 1 < length && tokens[index + 1].type == UNDERSCORE) {
        return parse_two_underscores(tokens, index, length, nodes);
    }
    return parse_one_underscore(tokens, index, length, nodes);
}

struct narrayInfo *createNodeArray(int capacity) {
    struct Node **nodes = calloc(capacity, sizeof(struct Node *));
    struct narrayInfo *info = malloc(sizeof(struct narrayInfo));
    info->capacity = capacity;
    info->elements = 0;
    info->data = nodes;
    return info;
}

void addToNodeArray(struct narrayInfo *info, struct Node *node) {
    if (info->capacity - info->elements < 1) {
        info->capacity *= 2;
        info->data = realloc(info->data, info->capacity * sizeof(struct Node *)
        );
    }
    info->data[info->elements] = node;
    // if (node->value != NULL) {
    //     info->data[info->elements]->value = strdup(node->value);
    // }
    info->elements++;
}


int parse_two_underscores(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
}

int parse_three_underscores(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
}

int parse_one_underscore(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
    int last = 0;
    char found = 0;
    struct Node *node = calloc(1, sizeof(struct Node));
    for (int i = index + 1; i < length; i++) {
        if (tokens[i].type == UNDERSCORE && !tokens[i].parsed) {
            found = 1;
            last = i;
            break;
        }
    }
    if (!found) {
        node->type = TEXTNODE;
        node->value = strdup("_");
        tokens[index].parsed = 1;
        addToNodeArray(nodes, node);
        // free(node);
        return length;
    }
    if (index + 1 != last) {
        // struct Node* node = malloc(sizeof(struct Node));
        node->type = EMPHASIS;
        tokens[index].parsed = 1;
        tokens[last].parsed = 1;
        node->children = createNodeArray(10);
        addToNodeArray(nodes, node);
        parse_terminals(tokens, index + 1, last, node->children);
        // free(node);
        return last;
    } else {
        node->type = TEXTNODE;
        node->value = strdup("__");
        tokens[index].parsed = 1;
        tokens[last].parsed = 1;
        addToNodeArray(nodes, node);
        free(node);
        return last;
    }
}

int parse_text(struct Token *tokens, int index, int length, struct narrayInfo *nodes) {
    tokens[index].parsed = 1;
    struct Node *node = calloc(1, sizeof(struct Node));
    node->type = TEXT;
    node->value = strdup(tokens[index].value);
    node->children = NULL;
    addToNodeArray(nodes, node);
    // free_node(node);
    return index;
}

void delete_last_n_nodes(struct narrayInfo *info, int n) {
    info->elements -= n;
}

void free_node(struct Node *node) {
    if (node == NULL) return;
    if (node->children != NULL) {
        free_narray(node->children);
    }
    if (node->value != NULL) {
        free(node->value);
    }

    free(node);
}

void free_narray(struct narrayInfo *narray) {
    if (narray == NULL) return;
    for (int i = 0; i < narray->elements; i++) {
        free_node(narray->data[i]);
    }
    free(narray->data);
    free(narray);
}

