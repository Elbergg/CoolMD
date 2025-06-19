//
// Created by tomps on 19/06/2025.
//
#include "gtest/gtest.h"
#include "tokenizer.h"

TEST(TokenizerTests, BasicTest) {
    char text[] = "_Hello*\n";
    Token *tokens = fragmentize(text);
    ASSERT_EQ(tokens[0].type, UNDERSCORE);
    ASSERT_EQ(tokens[1].type, TEXT);
    ASSERT_EQ(tokens[2].type, STAR);
    ASSERT_EQ(tokens[1].value, "Hello");
}
