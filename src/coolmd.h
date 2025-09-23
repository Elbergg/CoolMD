//
// Created by tomek on 7/24/25.
//
#include "translator.h"
#include "preprocessor.h"
#define COOLMD_H
#ifdef __cplusplus
extern "C" {
#endif


char *compile_to_html(const char *text);

struct narray *compile_to_nodes(const char *text);

#ifdef __cplusplus
}
#endif //COOLMD_H
