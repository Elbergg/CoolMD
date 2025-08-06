//
// Created by tomek on 6/30/25.
//

#include "gtest/gtest.h"
#include "../../parser.h"

TEST(ParserTest, EmphasisUnderscoreTest) {
    char text[] = "_Hello_";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    narrayInfo *narray = createNodeArray(1);
    parse_terminals(tokens, 0, info->elements, narray);
    Node **nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, EMPHASIS);
    ASSERT_EQ(nodes[0]->children->data[0]->type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0]->children->data[0]->value, "Hello") == 0);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, EmphasisStarTest) {
    char text[] = "*Hello*";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    narrayInfo *narray = createNodeArray(1);
    parse_terminals(tokens, 0, info->elements, narray);
    Node **nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, EMPHASIS);
    ASSERT_EQ(nodes[0]->children->data[0]->type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0]->children->data[0]->value, "Hello") == 0);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, BoldStarTest) {
    char text[] = "**Hello**";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    narrayInfo *narray = createNodeArray(1);
    parse_terminals(tokens, 0, info->elements, narray);
    Node **nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, BOLD);
    ASSERT_EQ(nodes[0]->children->data[0]->type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0]->children->data[0]->value, "Hello") == 0);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, BoldItalicStarTest) {
    char text[] = "***Hello***";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    narrayInfo *narray = createNodeArray(1);
    parse_terminals(tokens, 0, info->elements, narray);
    Node **nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, EMPHASIS);
    ASSERT_EQ(nodes[0]->children->data[0]->type, BOLD);
    ASSERT_EQ(nodes[0]->children->data[0]->children->data[0]->type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0]->children->data[0]->children->data[0]->value, "Hello") == 0);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, BoldItalicUnderscoreTest) {
    char text[] = "***Hello***";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    narrayInfo *narray = createNodeArray(1);
    parse_terminals(tokens, 0, info->elements, narray);
    Node **nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, EMPHASIS);
    ASSERT_EQ(nodes[0]->children->data[0]->type, BOLD);
    ASSERT_EQ(nodes[0]->children->data[0]->children->data[0]->type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0]->children->data[0]->children->data[0]->value, "Hello") == 0);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, BoldUnderscoreTest) {
    char text[] = "__Hello__";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    narrayInfo *narray = createNodeArray(1);
    parse_terminals(tokens, 0, info->elements, narray);
    Node **nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, BOLD);
    ASSERT_EQ(nodes[0]->children->data[0]->type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0]->children->data[0]->value, "Hello") == 0);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, ParagraphTest) {
    char text[] = "_Hello_\n\nHi";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, PARAGRAPH);
    ASSERT_EQ(nodes[1]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, ParagraphSpaceTest) {
    char text[] = "_He llo_\n\nHi";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, PARAGRAPH);
    ASSERT_EQ(nodes[1]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, TwoParagraphsSpaceTest) {
    char text[] = "_He llo_\n\nHi\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, PARAGRAPH);
    ASSERT_EQ(nodes[1]->type, PARAGRAPH);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, BlockquoteParagraphTest) {
    char text[] = ">_He llo_\n\nHi\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, BLOCKQUOTE);
    ASSERT_EQ(nodes[1]->type, PARAGRAPH);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, NestedBlockquotesTest) {
    char text[] = ">>_He llo_\n\n>>HI\n\n>YO\n\nmelo melo\n\n>dzien dobry\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, BLOCKQUOTE);
    ASSERT_EQ(nodes[0]->children->data[0]->type, BLOCKQUOTE);
    ASSERT_EQ(nodes[1]->type, PARAGRAPH);
    ASSERT_EQ(nodes[2]->type, BLOCKQUOTE);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, ParagraphSnlSpaceTest) {
    char text[] = "_He llo_\n\nHi\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, PARAGRAPH);
    ASSERT_EQ(nodes[1]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, Paragraph2Test) {
    char text[] = "_Hello_";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}


TEST(ParserTest, SentenceTest) {
    char text[] = "_Hello_\n\nHi";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *node = createNodeArray(1);
    Node *head = (Node *) calloc(1, sizeof(struct Node));
    head->type = BODY;
    head->children = createNodeArray(10);
    addToNodeArray(node, head);
    parse_terminals(tokens, 0, info->elements, node->data[0]->children);
    parse_sentences(node);

    Node **nodes = node->data[0]->children->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, SENTENCE);
    ASSERT_EQ(nodes[1]->type, DNL);
    ASSERT_EQ(nodes[2]->type, SENTENCE);
    // ASSERT_TRUE(strcmp(nodes[0].value, "Hello") == 0);
    // ASSERT_TRUE(strcmp(nodes[2].value, "Hi") == 0);
    free_tarray(info);
    free_narray(node);
}


// TEST(ParserTest, SentenceDifferentTokenTypesTest) {
//     char text[] = "_Hello_Heyo_hiii_\n\nHi";
//     struct tarrayInfo *info = tokenize(text);
//     Token *tokens = info->data;
//     struct narrayInfo *narray = parse(tokens, 0, info->elements);
//     Node *nodes = narray->data[0].children->data;
//     // ASSERT_EQ(nodes[0].type, BODY);
//     // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
//     ASSERT_EQ(nodes[0].type, SENTENCE);
//     ASSERT_EQ(nodes[1].type, DNL);
//     ASSERT_EQ(nodes[2].type, SENTENCE);
//     // ASSERT_TRUE(strcmp(nodes[0].value, "Hello") == 0);
//     // ASSERT_TRUE(strcmp(nodes[2].value, "Hi") == 0);
// }

TEST(ParserTest, HeaderSimpleTest) {
    char text[] = "# Hello";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, HEADER1);
    ASSERT_EQ(nodes[0]->children->data[0]->type, HASHSPACENODE);
    ASSERT_EQ(nodes[0]->children->data[1]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, Header2SimpleTest) {
    char text[] = "## Hello";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, HEADER2);
    ASSERT_EQ(nodes[0]->children->data[0]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[1]->type, HASHSPACENODE);
    ASSERT_EQ(nodes[0]->children->data[2]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, Header3SimpleTest) {
    char text[] = "### Hello";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, HEADER3);
    ASSERT_EQ(nodes[0]->children->data[0]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[1]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[2]->type, HASHSPACENODE);
    ASSERT_EQ(nodes[0]->children->data[3]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, Header4SimpleTest) {
    char text[] = "#### Hello";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, HEADER4);
    ASSERT_EQ(nodes[0]->children->data[0]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[1]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[2]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[3]->type, HASHSPACENODE);
    ASSERT_EQ(nodes[0]->children->data[4]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, Header5SimpleTest) {
    char text[] = "##### Hello";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->children->data[0]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[1]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[2]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[3]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[4]->type, HASHSPACENODE);
    ASSERT_EQ(nodes[0]->children->data[5]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, Header6SimpleTest) {
    char text[] = "###### Hello";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, HEADER6);
    ASSERT_EQ(nodes[0]->children->data[0]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[1]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[2]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[3]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[4]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[5]->type, HASHSPACENODE);
    ASSERT_EQ(nodes[0]->children->data[6]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, HeaderParagraphTestSimpleTest) {
    char text[] = "# Hello\ndzien dobry\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, HEADER1);
    ASSERT_EQ(nodes[1]->type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->children->data[0]->type, HASHSPACENODE);
    ASSERT_EQ(nodes[0]->children->data[1]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParserTest, Header3ParagraphTestSimpleTest) {
    char text[] = "### Hello\ndzien dobry\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    Node **nodes = narray->data[0]->children->data;
    ASSERT_EQ(nodes[0]->type, HEADER3);
    ASSERT_EQ(nodes[1]->type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->children->data[0]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[1]->type, HASHNODE);
    ASSERT_EQ(nodes[0]->children->data[2]->type, HASHSPACENODE);
    ASSERT_EQ(nodes[0]->children->data[3]->type, SENTENCE);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParsetTest, NotEvenUnderscores) {
    char text[] = "_Hello__";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    narrayInfo *narray = createNodeArray(1);
    parse_terminals(tokens, 0, info->elements, narray);
    Node **nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, EMPHASIS);
    ASSERT_EQ(nodes[0]->children->data[0]->type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0]->children->data[0]->value, "Hello") == 0);
    ASSERT_TRUE(strcmp(nodes[1]->value, "_") == 0);
    free_tarray(info);
    free_narray(narray);
}

TEST(ParsetTest, TwoUnderscores) {
    char text[] = "__";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    narrayInfo *narray = createNodeArray(1);
    parse_terminals(tokens, 0, info->elements, narray);
    Node **nodes = narray->data;
    // ASSERT_EQ(nodes[0].type, BODY);
    // ASSERT_EQ(nodes[0].children->data[0].type, PARAGRAPH);
    ASSERT_EQ(nodes[0]->type, TEXTNODE);
    ASSERT_TRUE(strcmp(nodes[0]->value, "__") == 0);
    free_tarray(info);
    free_narray(narray);
}
