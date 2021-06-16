#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for sleep function
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "constants.h"

#include "function.h"
#include "stack.h"


/*
numBytesOFContants(int) : Constants  : numFunctions : Function0 { numParams : instructions } : Function1 { ... }
*/

/*
 Constants Structure:
 # of constants
 isByteConstant or intConstant? Boalean
 # of bytes in this constant: (int)
 0x00 0x00 0x00 0x00 ...
 # of byes in this constant: (int)
 0x00 0x00 0x00 0x00 ...
 CONST_END
 */


// include is down here because otherwise constants is undefined in "BinKeys.h".
#include "BinKeys.h"
#include "runtime.h"



int main(int argc, char *argv[])
{
    FILE * fp;
    
    // DEBUG ONLY: assemble assembly to bytecode, then run
    system("python3 \"/Users/ericdiskin/Documents/code/code/c/Emulator - XCode Verson/Emulator - XCode Verson/python/assembler.py\"");
    
    
    // TODO: file:
    
    char* Fname = "/Users/ericdiskin/Library/Developer/Xcode/DerivedData/Emulator_-_XCode_Verson-bgutdxdelmtmxqdfbharumjtmmjp/Build/Products/Debug/out.emulate";
    
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
    unsigned long bytes_read = fread(in, sizeof(unsigned char), size, fp);
    fclose(fp);

    // get the constants
    int i = setConstants(in);

    //set the functions variable and return index of main
    setFunctions(in, i);
    
    // should probably free in here.
    
    // init the global variable vector:
    v_init(&globalVars);
    
    int retVal = call(functions[0]).values[0];
    // remove this later:
    printf("\n");
    return retVal;
}
