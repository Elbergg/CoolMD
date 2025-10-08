//
// Created by tomek on 7/8/25.
//
#include "dstring.h"
#include "int_array.h"
#include "parser.h"

#define TRANSLATOR_H


#ifdef __cplusplus
extern "C" {
#endif


struct dstring *to_html(struct Node *narray);

char *to_raw(struct Node *narray);

#ifdef __cplusplus
}
#endif // TRANSLATOR_H
