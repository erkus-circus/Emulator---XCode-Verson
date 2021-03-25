#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "constants.h"

#include "function.h"
#include "stack.h"


/*
numBytesOFContants(int) : Constants  : numFunctions : Function0 { numParams : instructions } : Function1 { ... }
*/




// include is down here because otherwise constants is undefined in "BinKeys.h".
#include "BinKeys.h"
#include "runtime.h"


int main(int argc, char *argv[])
{
    FILE * fp;

    // TODO: file:
    
    char* Fname = "out.emulate";

    if ((fp = fopen(Fname,"rb")) == NULL)
    {
        printf("Error opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long int size = ftell(fp);
    fclose(fp);

    // Reading data to array of unsigned chars
    fp = fopen(Fname, "rb");
    unsigned char * in = (unsigned char *) malloc(size);
    int bytes_read = fread(in, sizeof(unsigned char), size, fp);
    fclose(fp);

    // i should check if this is the correct number to malloc.
    constants = malloc( ucharsToInt(in) * sizeof(union Value) );

    int i = setConstants(in, constants);

    //set the functions variable and return index of main
    setFunctions(in, i);

    union Value res = call(functions[0]);
    
    printf("Return Value: %i\n",res.intValue);

    return 0;
}
