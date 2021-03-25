//
//  dataTypes.h
//  Emulator - XCode Verson
//
//  Created by Eric Diskin on 3/14/21.
//

#ifndef dataTypes_h
#define dataTypes_h

// for supporting more than one value at one place in the stack
struct Data {
    int* values;
    unsigned int size;
};

// stack
struct Stack
{
    int size;
    int index;

    struct Data* arr;
};

struct Vector
{
    struct Data* arr;
    int size;
    int offset;
};
#endif /* dataTypes_h */
