//
// Created by tomek on 6/29/25.
//

#ifndef PARSER_H
#define PARSER_H


enum NodeType {
    BODY,
    PARAGRAPH,
};

struct Node {
    enum NodeType;
    struct Node* children;
    char* value;
};

#endif //PARSER_H
