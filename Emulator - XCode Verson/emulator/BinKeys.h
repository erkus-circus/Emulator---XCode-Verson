#ifndef BIN_KEYS
#define BIN_KEYS

// file headers
#define INSTR_END '\x00'
#define FUN_HEAD '\x01'
#define CONST_SEPERATOR '\x02'
#define CONST_ESCAPE '\x03'

// INT_CONST is in else statement

// removed: not needed anymore
// #define STR_CONST '\x04'
#define SHORT_CONST '\x05'

#define MAIN '\x06'
#define CONST_END '\x07'

// number constants for references:
#define C_0 '\x0a'
#define C_1 '\x0b'
#define C_2 '\x0c'
#define C_3 '\x0d'
#define C_4 '\x0e'
#define C_5 '\x0f'

// load character from next unsigned char in intructions
#define C_B '\x10'
// load a short into int from next char
#define C_S '\x13'

// int methods
#define IADD '\x14'
#define ISUB '\x15'
#define IMUL '\x16'
#define IDIV '\x17'
#define IMOD '\x18'

// functions:
#define RET '\x19'
#define CALL '\x1a'

// load params into stack
#define P_0 '\x1b'
#define P_1 '\x1c'
#define P_2 '\x1d'
#define P_3 '\x1e'
#define P_4 '\x1f'
#define P_5 '\x20'

#define P_B '\x21'
#define P_S '\x22'

// load local variables
#define L_0 '\x23'
#define L_1 '\x24'
#define L_2 '\x25'
#define L_3 '\x26'
#define L_4 '\x27'
#define L_5 '\x28'

#define L_B '\x29'
#define L_S '\x2a'

// set local variables

#define S_0 '\x2b'
#define S_1 '\x2c'
#define S_2 '\x2d'
#define S_3 '\x2e'
#define S_4 '\x2f'
#define S_5 '\x30'

#define S_B '\x31'

// set short, next 2 bytes
#define S_S '\x32'


// stack instructions
// duplicate top of stack
#define DUP '\x33'

// conditionals

// op1, op2, # of lines to skip else, function number to call if false, parameters, call: CONDITION statement
#define CON '\x34'



// get input, and add value of input to stack
#define GET_CHAR '\x35'
// place a character in stdout
#define PUT_CHAR '\x36'


// Not implemented, Arrays: 
// (arrayIndex, size): init the array
#define IARR_INIT '\x37'

// (arrayIndex,value,index): put value into array at index
#define IARR_PUT '\x38' 

// (arrayIndex):
#define IARR_PUT_STACK '\x39'
#define IARRPUT_STACK '\x3a'


// IARR_OFFSET

// Values:
#define ZERO '\x3b'

// Variables
// set variable of index (top of stack)
#define S_ST '\x3c'

// moveup # of Lines, decrement PC by s_top
#define MVU '\x3d'

// Arrays:
// (newSize,) resize array
#define IARR_RZ '\x3e'

#define IARR_CAT '\x3f'

// (arrayIndex, indexFrom, indexTo): push stack values 
#define IARR_GETM '\x40'
// (arrayIndex, indexFrom, indexTo): push stack values in reverse
#define IARR_GETMR '\x41'


// File IO:

#endif // BIN_KEYS