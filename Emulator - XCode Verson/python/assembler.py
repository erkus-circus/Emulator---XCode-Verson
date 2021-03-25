"""

    unsigned char ion[] = {
    0,0,0,11,
    //  84 121 112 101 32 104 101 114 101 58 
    0,0,0,84,
    CONST_SEPERATOR,

    0,0,0,121,
    CONST_SEPERATOR,

    0,0,0,112,
    CONST_SEPERATOR,

    0,0,0,101,
    CONST_SEPERATOR,

    0,0,0,32,
    CONST_SEPERATOR,

    0,0,0,104,
    CONST_SEPERATOR,

    0,0,0,101,
    CONST_SEPERATOR,

    0,0,0,114,
    CONST_SEPERATOR,

    0,0,0,101,
    CONST_SEPERATOR,
    
    0,0,0,58,
    CONST_SEPERATOR,

    0,0,0,10,
    CONST_END,

    0,0b1,
    FUN_HEAD,
    0,0,

    // 12 (size)
    // IARR_INIT (init the array)
    
    // 1 (value)
    // 0 (index)
    // IARR_PUT


    // 0 (arr index)
    // IARR_PUT_STACK (copies arr to stack)
    // IARR_PUT_STACK_R (reverse copies arr to stack)

    C_B,
    10,
    C_B,
    9,
    C_B,
    8,
    C_B,
    7,
    C_B,
    6,
    C_5,
    C_4,
    C_3,
    C_2,
    C_1,
    C_0,

    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,
    PUT_CHAR,

    RET,
    INSTR_END
    

    };

"""
import os, sys

binKeys = {
    "INSTR_END": b'\x00',
    "FUN_HEAD": b'\x01',
    "CONST_SEPERATOR": b'\x02',
    "CONST_ESCAPE": b'\x03',
    "SHORT_CONST": b'\x05',
    "MAIN": b'\x06',
    "CONST_END": b'\x07',
    "C_0": b'\x0a',
    "C_1": b'\x0b',
    "C_2": b'\x0c',
    "C_3": b'\x0d',
    "C_4": b'\x0e',
    "C_5": b'\x0f',
    "C_B": b'\x10',
    "C_S": b'\x13',
    "IADD": b'\x14',
    "ISUB": b'\x15',
    "IMUL": b'\x16',
    "IDIV": b'\x17',
    "IMOD": b'\x18',
    "RET": b'\x19',
    "CALL": b'\x1a',
    "P_0": b'\x1b',
    "P_1": b'\x1c',
    "P_2": b'\x1d',
    "P_3": b'\x1e',
    "P_4": b'\x1f',
    "P_5": b'\x20',
    "P_B": b'\x21',
    "P_S": b'\x22',
    "L_0": b'\x23',
    "L_1": b'\x24',
    "L_2": b'\x25',
    "L_3": b'\x26',
    "L_4": b'\x27',
    "L_5": b'\x28',
    "L_B": b'\x29',
    "L_S": b'\x2a',
    "S_0": b'\x2b',
    "S_1": b'\x2c',
    "S_2": b'\x2d',
    "S_3": b'\x2e',
    "S_4": b'\x2f',
    "S_5": b'\x30',
    "S_B": b'\x31',
    "S_S": b'\x32',
    "DUP": b'\x33',
    "CON": b'\x34',
    "GET_CHAR": b'\x35',
    "PUT_CHAR": b'\x36',
    "IARR_INIT": b'\x37',
    "IARR_PUT": b'\x38' ,
    "IARR_PUT_STACK": b'\x39',
    "IARRPUT_STACK": b'\x3a',
    "ZERO": b'\x3b',
    "S_ST": b'\x3c',
    "MVU": b'\x3d'
}


file = ""

with open("./assembly.txt","r") as f:
    file = f.read()



with open("out.emulate", "wb") as out:
    for i in file.split():
        if not i.startswith("0x"):
            i = i.upper()
            out.write(binKeys[i])
        else:
            print(i[2:])
            out.write(bytearray.fromhex(i[2:]))