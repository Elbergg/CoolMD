//
// Created by tomek on 10/5/25.
//
#include <dstring.h>
#include <stdlib.h>
#include <string.h>


struct dstring *create_dstring(const char *data) {
    struct dstring *d = calloc(1, sizeof(struct dstring));
    d->data = data;
    d->len = strlen(data);
    d->cap = d->len * 2;
    return d;
}

void append_to_dstring(struct dstring *d, const char *data) {
    check_if_cap(d, data);
    strcat(d->data, data);
}

void check_if_cap(struct dstring *d, const char *data) {
    if (d->len += strlen(data) > d->cap) {
        d->cap = d->cap * 2;
        realloc(d->data, d->cap);
    }
}

void free_dstring(struct dstring *d) {
    free(d->data);
    free(d);
}

void concat_dstrings(struct dstring *d, struct dstring *s) {
    append_to_dstring(d, s->data);
    free_dstring(s);
}

void add_to_dstring_front(struct dstring *d, const char *data) {
    check_if_cap(d, data);
    realloc(data, d->cap);
    strcat(data, d->data);
    free(d->data);
    d->data = data;
}
