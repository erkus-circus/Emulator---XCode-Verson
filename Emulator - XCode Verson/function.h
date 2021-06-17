#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "array.h"
#include "BinKeys.h"

int ucharsToInt (unsigned char* buf)
{
    int total = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 8; j >= 0; j--)
        {
            total <<= 1;
            if ((buf[i] >> j) & 0x01) total^=1;
        }
    }
    return total;
}

int ucharToShort(unsigned char* buf)
{
    unsigned char a[4] =
    {
        0, 0,
        buf[0], buf[1]
    };

    return ucharsToInt(a);
}

int ucharFromByte(unsigned char* buf) {
    unsigned char a[4] =
    {
        0, 0,
        0, buf[0]
    };
    return ucharsToInt(a);
}

struct Function
{
    unsigned int paramCount;

    struct Vector varArr;

    unsigned int PC;
    unsigned int numIntructions;
    
    unsigned char* intstructions;

    struct Stack stack;
};

struct Function* functions = NULL;

int setFunctions(unsigned char* file, int i)
{
    int numFuncs;
    numFuncs = ucharToShort(file + i);

    i += 2;

    functions = malloc(numFuncs * sizeof (struct Function) );

    for (int funcCount = 0; funcCount < numFuncs; funcCount++)
    {
        i++;
        // get number of params:
        int numParams = ucharToShort(file + i);

        i += 2;

        // process instructions:

        int preInstr = i;
        // loop till i is ucharsToIntt the string substring thing to get the instructions (one bytene  each).
        while(file[++i] != INSTR_END)
        {
        }


        unsigned char* instructions;

        unsigned int numInstructions = (i-preInstr);

        instructions = malloc( numInstructions * sizeof(unsigned char) );
        // memcpy(instructions, file + preInstr + 1, (i - preInstr - 1) * sizeof(unsigned char) );
        memcpy(instructions, file + preInstr, i - preInstr + 1);


        struct Function func;

        func.paramCount = numParams;
        func.intstructions = instructions;
        func.numIntructions = numInstructions;


        functions[funcCount] = func;

        i++;
    }
    // should be at main
    return i;
}

void copy_function (struct Function* f1, struct Function* f2)
{
    // does this need to be here?
    // s_free(&f1->stack);
    f1->intstructions = f2->intstructions;
    f1->numIntructions = f2->numIntructions;
    f1->paramCount = f2->paramCount;
    f1->PC = f2->PC;
    f1->stack = f2->stack;
}

#endif // FUNCTION_H_INCLUDED
