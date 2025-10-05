//
// Created by tomek on 7/8/25.
//
#include "parser.h"
#include "dstring.h"

#define TRANSLATOR_H


#ifdef __cplusplus
extern "C" {
#endif


struct dstring *to_html(struct Node *narray);

struct dstring *to_raw(struct Node *narray);

#ifdef __cplusplus
}
#endif //TRANSLATOR_H
