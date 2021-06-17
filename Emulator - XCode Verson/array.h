#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include "function.h"
#include "dataTypes.h"


void v_set (struct Vector* vector, int index, struct Data value)
{
    if (index >= vector->size) {
        vector->size *= 2;
        vector->arr = realloc(vector->arr, vector->size * sizeof(struct Data));
    }
    vector->arr[index] = value;
}

void v_init (struct Vector* vector, int size)
{
    vector->size = size;
    vector->arr = malloc( vector->size * sizeof(struct Data) );
}

struct Data v_get(struct Vector* vector, int index)
{
    return vector->arr[index];
}
#endif // ARRAY_H_INCLUDED
