//
// Created by tomek on 6/30/25.
//

#include "gtest/gtest.h"
#include "parser.h"

TEST(ParserTest, BasicTest) {
    char text[] = "_Hello_";
    Token *tokens = tokenize(text);
    narrayInfo* narray = createNodeArray(1);
    parse(tokens, 0, 2, narray);
    Node* nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0].type, EMPHASIS);
    ASSERT_EQ(nodes[0].children->data[0].type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0].children->data[0].value, "Hello") == 0);
}

TEST(ParsetTest, NotEvenUnderscores) {
    char text[] = "_Hello__";
    Token *tokens = tokenize(text);
    narrayInfo* narray = createNodeArray(1);
    parse(tokens, 0, 3, narray);
    Node* nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0].type, EMPHASIS);
    ASSERT_EQ(nodes[0].children->data[0].type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0].children->data[0].value, "Hello") == 0);
    ASSERT_TRUE(strcmp(nodes[1].value, "_") == 0);
}

TEST(ParsetTest, ThreeUnderscores) {
    char text[] = "__";
    Token *tokens = tokenize(text);
    narrayInfo* narray = createNodeArray(1);
    parse(tokens, 0, 2, narray);
    Node* nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0].type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0].value, "__") == 0);

}