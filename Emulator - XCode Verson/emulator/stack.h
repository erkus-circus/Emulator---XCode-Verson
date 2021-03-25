#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

union Value
{
    int intValue;
    // for debugging purposes:
    char charValue;
};

struct Stack
{
    int size;
    int index;

    union Value* arr;
};


void s_push(struct Stack* stack, union Value value)
{

    if (stack->index + 1 >= stack->size)
    {
        // double size of array
        stack->arr = realloc(stack->arr, stack->size *= 2 * sizeof (union Value) );
    }

    *(stack->arr + (++stack->index)) = value;
}

void s_pop(struct Stack* stack)
{
    // if (stack->index <= 0)
    //     return;

    // For testing, remove for efficiency.
    stack->arr[stack->index].intValue = 0;
    stack->index -= 1;
}

void s_init(struct Stack* stack, int size)
{
    stack->size = size;
    stack->index = -1;
    stack->arr = malloc(size * sizeof(union Value) );
}

int s_empty (struct Stack* stack)
{
    // check if stack is empty
    return stack->index <= 0;
}

union Value s_top(struct Stack* stack)
{
    return stack->arr[stack->index];
}

void s_free(struct Stack* stack)
{
    free(stack->arr);
    stack->size = -1;
    stack->index = -1;
}

#endif // STACK_H_INCLUDED
