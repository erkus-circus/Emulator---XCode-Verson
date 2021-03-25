#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include "function.h"
#include "dataTypes.h"


void v_set (struct Vector* vector, int index, struct Data value)
{
    if (index + vector->offset >= vector->size) {
        vector->arr = realloc(vector->arr, vector->size * 2);
    }
    vector->arr[index + vector->offset] = value;
}

void v_init (struct Vector* vector)
{
    vector->size = 8;
    vector->offset = 0;
    vector->arr = malloc( vector->size * sizeof(struct Data) );
}

struct Data v_get(struct Vector* vector, int index)
{
    return vector->arr[index + vector->offset];
}

void v_concat(struct Vector* dest, struct Vector* src)
{
    memcpy(dest->arr,src->arr,src->size);
}
#endif // ARRAY_H_INCLUDED
