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

TEST(TranslatorTest, NoHeaderParagraphBoldItalicTranslateTest) {
    char text[] = "Hello\n***dzien dobry***\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_html(narray->data[0]);
    ASSERT_TRUE(strcmp(result, "<p>Hello<em><strong>dzien dobry</strong></em></p>") == 0);
    free_tarray(info);
    free_narray(narray);
    free(result);
}


TEST(TranslatorTest, HeadersInNewlinesTest) {
    char text[] = "# Hello\n## halo\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_html(narray->data[0]);
    ASSERT_TRUE(strcmp(result, "<h1>Hello</h1><h2>halo</h2>") == 0);
    free_tarray(info);
    free_narray(narray);
    free(result);
}

TEST(TranslatorTest, ThreeHeadersInNewlinesTest) {
    char text[] = "# Hello\n## halo\n### balo\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_html(narray->data[0]);
    ASSERT_TRUE(strcmp(result, "<h1>Hello</h1><h2>halo</h2><h3>balo</h3>") == 0);
    free_tarray(info);
    free_narray(narray);
    free(result);
}


TEST(TranslatorTest, NestedBlockquotesTest) {
    char text[] = ">_He llo_\n>>HI\n>YO\n> \n>pozdrawiam\n\nmelo melo\n\n>dzien dobry\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_html(narray->data[0]);

    ASSERT_TRUE(
        strcmp(result,
            "<blockquote><p><em>He llo</em></p><blockquote><p>HIYO</p></blockquote><p>pozdrawiam</p></blockquote><p>melo melo</p><blockquote><p>dzien dobry</p></blockquote>"
        ) == 0);

    free_tarray(info);
    free_narray(narray);
    free(result);
}


TEST(TranslatorTest, ToRawTest) {
    char text[] = ">_He llo_\n>>HI\n>YO\n>\n>pozdrawiam\n\nmelo melo\n\n>dzien dobry\n\n";
    struct tarrayInfo *info = tokenize(text);
    Token *tokens = info->data;
    struct narrayInfo *narray = parse(tokens, 0, info->elements);
    char *result = to_raw(narray->data[0]);
    ASSERT_TRUE(strcmp(result, ">_He llo_\n>>HI\n>YO\n>\n>pozdrawiam\n\nmelo melo\n\n>dzien dobry\n\n")==0);
    free_tarray(info);
    free_narray(narray);
    free(result);
}

