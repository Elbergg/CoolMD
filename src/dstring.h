//
// Created by tomek on 10/5/25.
//

#ifndef DSTRING_H
#define DSTRING_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO ADD TYPEDEFS TO ALL THE STRUCTS!
struct dstring {
    char *data;
    int len;
    int cap;
};

struct dstringArrayInfo {
    struct dstring **data;
    int elements;
    int capacity;
};

struct dstringArrayInfo *create_dstring_array(size_t size);

void add_to_dstring_array(struct dstringArrayInfo *array, struct dstring *dstring);

struct dstring *create_dstring(const char *data);

void append_to_dstring(struct dstring *d, const char *data);

void add_to_dstring_front(struct dstring *d, const char *data);

void check_if_cap(struct dstring *d, const char *data);

void free_dstring(struct dstring *d);

void concat_dstrings(struct dstring *d, struct dstring *s);

#ifdef __cplusplus
}
#endif

#endif // DSTRING_H
