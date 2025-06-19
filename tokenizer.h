//
// Created by tomps on 19/06/2025.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

enum tokenType {
    UNDERSCORE,
    STAR,
    NEWLINE,
    TEXT,
    EOF_S,
};

struct Token {
    tokenType type;
    char* value;
};

Token* tokenize(const char* str);


#endif //TOKENIZER_H
