//
// Created by tomek on 6/29/25.
//
#include "tokenizer.h"
#ifndef PARSER_H
#define PARSER_H


enum nodeType {
    BODY,
    PARAGRAPH,
    EMPHASIS,
    TEXTNODE
};

struct Node {
    enum nodeType type;
    struct Node* children;
    char* value;
};

struct Node* parse(struct Token * tokens) {

}

#endif //PARSER_H
