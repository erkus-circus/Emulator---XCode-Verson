#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED


#include "function.h"

// returns value of i
int setConstants(unsigned char* file, union Value* constants)
{
    int constNumber = -1;

    int i = 3;

    while(file[i++] != CONST_END)
    {
        if (file[i] == CONST_SEPERATOR)
        {
            continue;
        }

        // REMOVED: no string constants, they are just going to be initalized arrays in code as of now.
        // if string constant
        // if (file[i] == STR_CONST)
        // {
        //     union Value curConst;

        //     int len = i;
        //     while(file[++i] != CONST_SEPERATOR)
        //     {
        //     }

        //     curConst.stringValue = calloc(i - len - 1,sizeof(char));
        //     memcpy(curConst.stringValue, file + len + 1, (i - len - 1) * sizeof(unsigned char) );
        //     constants[++constNumber] = curConst;
        // }
        else
        {
            // integer constant

            union Value curConst;

            curConst.intValue = ucharsToInt(file + i);
            i += 4;

            constants[++constNumber] = curConst;
        }
    }
    return i;
};

#endif // CONSTANTS_H_INCLUDED
