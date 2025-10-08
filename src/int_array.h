#include <stddef.h>
typedef struct {
    int *data;
    int elements;
    int capacity;

} intarray;

intarray *create_intarray(size_t size);

int get_back_ia(intarray *array);

void add_to_intarray(intarray *array, int number);
