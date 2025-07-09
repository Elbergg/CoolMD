//
// Created by tomek on 7/8/25.
//

#include "gtest/gtest.h"
#include "../../translator.h"

TEST(TranslatorTest, HeaderParagraphTranslateTest) {
    char text[] = "# Hello\ndzien dobry\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    ASSERT_TRUE(strcmp(to_html(&narray->data[0]), "<h1>Hello</h1><p>dzien dobry</p>") == 0);
}
