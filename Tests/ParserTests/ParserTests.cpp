//
// Created by tomek on 6/30/25.
//

#include "gtest/gtest.h"
#include "parser.h"

TEST(ParserTest, BasicTest) {
    char text[] = "_Hello_";
    Token *tokens = tokenize(text);
    Node* nodes = parse(tokens);
    ASSERT_EQ(nodes[0].type, BODY);
    ASSERT_EQ(nodes[0].children[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0].children[0].children[0].type, EMPHASIS);
    ASSERT_EQ(nodes[0].children[0].children[0].children[0].type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0].children[0].children[0].children[0].value, "Hello") == 0);
}