//
// Created by tomps on 19/06/2025.
//


#ifndef TOKENIZER_H
#define TOKENIZER_H

#ifdef __cplusplus
extern "C" {
#endif

enum tokenType {
    UNDERSCORE,
    STAR,
    NEWLINE,
    TEXT,
    EOF_S,
    HASH,
    HASHSPACE,
};

struct Token {
    enum tokenType type;
    char *value;
    char parsed;
};

struct preToken {
    int start;
    int end;
    struct Token token;
};


struct tarrayInfo {
    int capacity;
    int elements;
    struct Token *data;
};


struct ptarrayInfo {
    int capacity;
    int elements;
    struct preToken *data;
};

struct tarrayInfo *tokenize(char *str);

// struct Token *blockerize(char *str);

// struct Token *fragmentize(char *str);

struct tarrayInfo *createTokenArray(int capacity);

void addToTokenArray(struct tarrayInfo *info, struct Token *token);

#ifdef __cplusplus
}
#endif

#endif



