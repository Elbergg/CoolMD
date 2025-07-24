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
    char *result = to_html(narray->data[0]);
    ASSERT_TRUE(strcmp(result, "<h1>Hello</h1><p>dzien dobry</p>") == 0);

    free_tarray(info);
    free_narray(narray);
    free(result);
}

TEST(TranslatorTest, HeaderParagraphEmphasisTranslateTest) {
    char text[] = "# Hello\n_dzien dobry_\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_html(narray->data[0]);
    ASSERT_TRUE(strcmp(result, "<h1>Hello</h1><p><em>dzien dobry</em></p>") == 0);
    free_tarray(info);
    free_narray(narray);
    free(result);
}

TEST(TranslatorTest, Header3ParagraphEmphasisTranslateTest) {
    char text[] = "### Hello\n_dzien dobry_\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_html(narray->data[0]);
    ASSERT_TRUE(strcmp(result, "<h3>Hello</h3><p><em>dzien dobry</em></p>") == 0);
    free_tarray(info);
    free_narray(narray);
    free(result);
}

TEST(TranslatorTest, NoHeaderParagraphEmphasisTranslateTest) {
    char text[] = "Hello\n_dzien dobry_\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_html(narray->data[0]);
    ASSERT_TRUE(strcmp(result, "<p>Hello<em>dzien dobry</em></p>") == 0);
    free_tarray(info);
    free_narray(narray);
    free(result);
}

TEST(TranslatorTest, NoHeaderParagraphBoldTranslateTest) {
    char text[] = "Hello\n__dzien dobry__\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_html(narray->data[0]);
    ASSERT_TRUE(strcmp(result, "<p>Hello<strong>dzien dobry</strong></p>") == 0);
    free_tarray(info);
    free_narray(narray);
    free(result);
}


