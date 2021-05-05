#ifndef BIN_KEYS
#define BIN_KEYS // skip

// file headers
#define INSTR_END '\x00'
#define FUN_HEAD '\x01'
#define CONST_SEPERATOR '\x02'

// INT_CONST is in else statement

#define MAIN '\x03'
#define CONST_END '\x04'

// number constants for references:
#define C_0 '\x05'
#define C_1 '\x06'
#define C_2 '\x07'
#define C_3 '\x08'
#define C_4 '\x09'
#define C_5 '\x0a'

// load character from next unsigned char in intructions
#define C_B '\x0b'
// load a short into int from next char
#define C_S '\x0c'

// int methods
#define IADD '\x0d'
#define ISUB '\x0e'
#define IMUL '\x0f'
#define IDIV '\x10'
#define IMOD '\x11'

// functions:
#define RET '\x12'
#define CALL '\x13'

// load params into stack
#define P_0 '\x14'
#define P_1 '\x15'
#define P_2 '\x16'
#define P_3 '\x17'
#define P_4 '\x18'
#define P_5 '\x19'

#define P_B '\x1a'
#define P_S '\x1b'

// load local variables
#define L_0 '\x1c'
#define L_1 '\x1d'
#define L_2 '\x1e'
#define L_3 '\x1f'
#define L_4 '\x20'
#define L_5 '\x21'

#define L_B '\x22'
#define L_S '\x23'

// set local variables

#define S_0 '\x24'
#define S_1 '\x25'
#define S_2 '\x26'
#define S_3 '\x27'
#define S_4 '\x28'
#define S_5 '\x29'

#define S_B '\x2a'

// set short, next 2 bytes
#define S_S '\x2b'


// stack instructions
// duplicate top of stack
#define DUP '\x2c'

// conditionals


// '\x2d' is skipped, used to be CON statement


// get input, and add value of input to stack
#define GET_CHAR '\x2e'
// place a character in stdout
#define PUT_CHAR '\x2f'

// IARR_OFFSET

// Values:
#define ZERO '\x30'

// Variables
// set variable of index (top of stack)
#define S_ST '\x31'

// moveup # of Lines, decrement PC by s_top
// could be used for loops
#define MVU '\x32'

// control
#define SLEEP '\x33'

// for Data struct managment:
// get (index):
// index = TOP; POP; ret TOP.values[index]
#define DGET '\x34'

// set (index):
// index = TOP; POP; ret TOP.values[index] = (POP)TOP
// index first, then value to set, then Data to set to
#define DSET '\x35'

// mem copy a Data to another Data
// memcpy(TOP0, TOP1)
#define DCPY '\x36'

// get size of Data on the top of the stack
#define DSIZE '\x37'

// put chars of every value inside Data.values
#define PUT_CHARS '\x38'

// Conditionals:
// only checks values[0], might need to fix that eventually, in fact i will need to fix this eventually
// takes op1 and op2 off the stack, then does the operation (<> <=> == !=), then returns the 0|1 value and pushes that value onto the stack.
#define LT '\x39'
#define GT '\x3a'
#define GTE '\x3b'
#define LTE '\x3c'
#define EQ '\x3d'
#define NEQ '\x3e'

// skip a few lines
#define SKIP '\x3f'

// set PC to s_top
#define JMP '\x40'

// number to string:
// this returns a null terminated string.
#define ITOA '\x41'

// string to number:
// maybe i will add. Also maybe i will add c strings support.
// '\x42'


// global variables:

// load local variables
#define GL_0 '\x43'
#define GL_1 '\x44'
#define GL_2 '\x45'
#define GL_3 '\x46'
#define GL_4 '\x47'
#define GL_5 '\x48'

#define GL_B '\x49'
#define GL_S '\x4a'

// set global variables

#define GS_0 '\x4b'
#define GS_1 '\x4c'
#define GS_2 '\x4d'
#define GS_3 '\x4e'
#define GS_4 '\x4f'
#define GS_5 '\x50'

#define GS_B '\x51'

// set short, next 2 bytes
#define GS_S '\x52'

// pop function
// pops off top of stack
#define POP '\x53'


// conditionals - Actual
/// made this late at night dont expect anything good.
#define COMP '\x54'

// for exiting the program

// File IO (later convert to streams):

// debugging tools:
#define BREAKPOINT '\x55'

#endif // BIN_KEYS
