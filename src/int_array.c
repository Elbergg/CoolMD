#include <int_array.h>
#include <stdlib.h>

intarray *create_intarray(size_t size) {
    intarray *array = calloc(size, sizeof(intarray));
    array->data = calloc(size, sizeof(int));
    array->capacity = size;
    array->elements = 0;
    return array;
}


void add_to_intarray(intarray *array, int number) {
    if (array->elements == array->capacity) {
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * sizeof(int));
    }
    array->data[array->elements] = number;
    array->elements++;
}


int get_back_ia(intarray *array) { return array->data[array->elements - 1]; }
