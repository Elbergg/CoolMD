//
// Created by tomps on 19/06/2025.
//
#include "gtest/gtest.h"
#include "tokenizer.h"

TEST(TokenizerTests, BasicTest) {
    char text[] = "_Hello***";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    ASSERT_EQ(tokens[0].type, UNDERSCORE);
    ASSERT_EQ(tokens[1].type, TEXT);
    ASSERT_EQ(tokens[2].type, STAR);
    ASSERT_TRUE(strcmp(tokens[1].value, "Hello") == 0);
}

TEST(TokenizerTests, BasicTest2) {
    char text[] = "_*aaa__bb";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    ASSERT_EQ(tokens[0].type, UNDERSCORE);
    ASSERT_EQ(tokens[1].type, STAR);
    ASSERT_EQ(tokens[2].type, TEXT);
    ASSERT_EQ(tokens[3].type, UNDERSCORE);
    ASSERT_EQ(tokens[4].type, UNDERSCORE);
    ASSERT_EQ(tokens[5].type, TEXT);
    ASSERT_TRUE(strcmp(tokens[2].value, "aaa") == 0);
    ASSERT_TRUE(strcmp(tokens[5].value, "bb") == 0);
}
