#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include "function.h"
#include "dataTypes.h"
#include "data.h"
#include "runtime.h"


/**
 New Format:
 
 CONST_LEN (0x08)
 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08
 CONST_LEN (0x02)
 0x5a 0xa4
 CONST_END
 */


// returns value of i
int setConstants(unsigned char* file)
{
    // number of total constants
    int constNumber = -1;
    
    constNumber = ucharsToInt(file);
    
    constants = malloc(constNumber * sizeof(struct Data));
    
    int i = 4;

    
    for (int k = 0; k < constNumber; k++)
    {
    
        struct Data curConst;
        
        // if this data segment should be counted through 4 bytes at a time or 1 byte at a time (char)
        int numberOfChars = ucharFromByte(file + i);
        i += 1;
        
//        the length of this data segment
        unsigned int dataLen = ucharsToInt(file + i);
        // += 4 to skip the next for bytes, which went into making the int
        i += 4;
        
        init_data(&curConst, dataLen);
        
        // if the constant is defined with 4 byte spacers
        if (numberOfChars == 4) {
            for (int j = 0; j < dataLen; j += 1) {
                curConst.values[j] = ucharsToInt(file + i);
                // skip to the next byte.
                i += 4;
            }
        } else {
            // the constant is defined with 1 byte spacers
            for (int j = 0; j < dataLen; j += 1) {
                curConst.values[j] = ucharFromByte(file + i);
                // skip to the next byte.
                i += 1;
            }
        }
        constants[k] = curConst;
        
    }
    
    return i + 1;
};

#endif // CONSTANTS_H_INCLUDED

