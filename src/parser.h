//
// Created by tomek on 6/29/25.
//
#include <stdlib.h>
#include "tokenizer.h"

#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

enum nodeType {
    BODY,
    PARAGRAPH,
    EMPHASIS,
    TEXTNODE,
    BOLD,
    SENTENCE,
    DNL,
    SNL,
    HASHNODE,
    HASHSPACENODE,
    HEADER1,
    HEADER2,
};

struct Node {
    enum nodeType type;
    struct narrayInfo *children;
    char *value;
    int begin, end;
};

struct narrayInfo {
    int capacity;
    int elements;
    struct Node **data;
};

struct narrayInfo *parse(struct Token *tokens, int index, int length);

void parse_terminals(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

int parse_text(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

struct narrayInfo *createNodeArray(int capacity);

void parse_non_terminals(struct narrayInfo *nodes);

void parse_paragraphs(struct narrayInfo *nodes);

void parse_sentences(struct narrayInfo *nodes);

int parse_newline(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

int parse_underscores(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

int parse_one_underscore(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

int parse_two_underscores(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

int parse_three_underscores(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

int parse_hashtags(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

void addToNodeArray(struct narrayInfo *info, struct Node *node);

void delete_last_n_nodes(struct narrayInfo *info, int n);

int parse_one_hashtag(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

int parse_two_hashtags(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

int parse_three_hashtags(struct Token *tokens, int index, int length, struct narrayInfo *nodes);

void parse_headers(struct narrayInfo *nodes);

void parse_h1(struct narrayInfo *nodes);

struct Token *parse_spaces(struct Token *tokens, int *length);

void free_narray(struct narrayInfo *narray);

void free_node(struct Node *node);


#ifdef __cplusplus
}
#endif

#endif //PARSER_H
