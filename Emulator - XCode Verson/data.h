//
//  data.h
//  Emulator - XCode Verson
//
//  Created by Eric Diskin on 3/14/21.
//

#ifndef data_h
#define data_h

#include "dataTypes.h"


#define TRUE 1
#define FALSE 0


void free_data(struct Data* data)
{
    free(data->values);
}

void init_data(struct Data* data, unsigned int size)
{
    data->values = malloc(size * sizeof(int));
    data->size = size;
}

struct Data create_data(int value)
{
    struct Data data;
    
    init_data(&data, 1);
    data.values[0] = value;
    return data;
}
#endif /* data_h */
