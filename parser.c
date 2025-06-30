//
// Created by tomek on 6/29/25.
//
#include "parser.h"

void parse(struct Token * tokens, int index, int length, struct narrayInfo * nodes) {
    for (int i = index; i <= length; i++) {
        switch (tokens[i].type) {
            case UNDERSCORE:
                i = parse_underscores(tokens, i, length, nodes);
                break;
            case TEXTNODE:
                i = parse_text(tokens, i, length, nodes);
                break;
            default: ;
        }
    }
}
int parse_underscores(struct Token* tokens, int index, int length, struct narrayInfo * nodes) {
    if (index + 1 < length && tokens[index + 1].type == UNDERSCORE && index + 2 < length && tokens[index + 2].type == UNDERSCORE) {
        return parse_three_underscores(tokens, index, length, nodes);
    }
    if (index + 1 < length && tokens[index + 1].type == UNDERSCORE) {
        return parse_two_underscores(tokens, index, length, nodes);
    }
    return parse_one_underscore(tokens, index, length, nodes);
}

struct narrayInfo *createNodeArray(int capacity) {
    struct Node *nodes = malloc(sizeof(struct Node) * capacity);
    struct narrayInfo *info = malloc(sizeof(struct narrayInfo));
    info->capacity = capacity;
    info->elements = 0;
    info->data = nodes;
    return info;
}

void addToNodeArray(struct narrayInfo *info, struct Node *node) {
    if (info->capacity - info->elements < 1) {
        info->capacity *= 2;
        info->data = realloc(info->data, info->capacity * sizeof(struct Node));
    }
    info->data[info->elements] = *node;
    info->elements++;
}


int parse_two_underscores(struct Token* tokens, int index, int length, struct narrayInfo * nodes)
{}
int parse_three_underscores(struct Token* tokens, int index, int length, struct narrayInfo * nodes)
{}

int parse_one_underscore(struct Token* tokens, int index, int length, struct narrayInfo* nodes) {
    int last =  0;
    char found = 0;
    struct Node* node = malloc(sizeof(struct Node));
    for (int i = index+1; i <= length; i++) {
        if (tokens[i].type == UNDERSCORE && !tokens[i].parsed) {
            found = 1;
            last = i;
            break;
        }
    }
    if (!found) {
        node->type = TEXTNODE;
        node->value = "_";
        tokens[index].parsed = 1;
        addToNodeArray(nodes, node);
        return length;
    }
    if (index + 1 != last){
        // struct Node* node = malloc(sizeof(struct Node));
        node->type = EMPHASIS;
        tokens[index].parsed = 1;
        tokens[last].parsed = 1;
        node->children = createNodeArray(10);
        addToNodeArray(nodes, node);
        parse(tokens, index + 1, last, node->children);
        return last;
    }
    else {
        node->type = TEXTNODE;
        node->value = "__";
        tokens[index].parsed = 1;
        tokens[last].parsed = 1;
        addToNodeArray(nodes, node);
        return last;
    }
}

int parse_text(struct Token* tokens, int index, int length, struct narrayInfo* nodes) {
    tokens[index].parsed = 1;
    struct Node* node = malloc(sizeof(struct Node));
    node->type = TEXT;
    node->value = tokens[index].value;
    node->children = NULL;
    addToNodeArray(nodes, node);
    return length;
}



