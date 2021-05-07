#ifndef RUNTIME_H_INCLUDED
#define RUNTIME_H_INCLUDED


#include <time.h>
#include <string.h>

#include "stack.h"
#include "array.h"
#include "function.h"
#include "BinKeys.h"
#include "constants.h"
#include "dataTypes.h"
#include "data.h"
#include "sleep.h"

static struct Data *constants;
// maybe because it is static?

struct Vector globalVars;
// TODO: putchar and getchar used in other streams, like files

static int instructionsExecuted = 0;

struct Data call(struct Function fn)
{
//    instructionsExecuted = 0;
    s_init(&fn.stack, 8);
    v_init(&fn.varArr);
    
    for (fn.PC = 0; fn.PC < fn.numIntructions; fn.PC++)
    {
        instructionsExecuted++;
        switch (fn.intstructions[fn.PC])
        {
            case C_0:
                s_push(&fn.stack, constants[0]);
                break;
            case C_1:
                s_push(&fn.stack, constants[1]);
                break;
            case C_2:
                s_push(&fn.stack, constants[2]);
                break;
            case C_3:
                s_push(&fn.stack, constants[3]);
                break;
            case C_4:
                s_push(&fn.stack, constants[4]);
                break;
            case C_5:
                s_push(&fn.stack, constants[5]);
                break;
                
            case C_B:
                s_push(&fn.stack, constants[(int)fn.intstructions[++fn.PC]]);
                break;
            case C_S:
                s_push(&fn.stack, constants[ucharToShort(fn.intstructions + fn.PC + 1)]);
                fn.PC += 2;
                break;
                
            case IADD:
            {
                int a = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                int b = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                struct Data val;
                
                init_data(&val, 1);
                
                val.values[0] = a + b;
                
                s_push(&fn.stack, val);
                
//                free_data(&val);
                
                break;
            }
            case ISUB:
            {
                
                int a = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                int b = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                struct Data val;
                init_data(&val, 1);
                
                val.values[0] = b - a;
                
                s_push(&fn.stack, val);
                
                
                
                break;
            }
            case IMUL:
            {
                
                int a = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                int b = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                struct Data val;
                init_data(&val, 1);
                
                val.values[0] = b * a;
                
                s_push(&fn.stack, val);
                break;
            }
            case IDIV:
            {
                
                int a = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                int b = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                struct Data val;
                
                init_data(&val, 1);
                val.values[0] = (int)(b / a);
                
                s_push(&fn.stack, val);
                break;
            }
            case IMOD:
            {
                
                int a = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                int b = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                struct Data val;
                
                init_data(&val, 1);
                val.values[0] = b % a;
                
                s_push(&fn.stack, val);
                
                free_data(&val);
                break;
            }
                
            case RET:
            {
                // does this work?
                struct Data retVal;
                retVal = s_top(&fn.stack);
                // i need to free this, but i cant because it frees retVal.
                //s_free(&fn.stack);
                
                // almost works
                return retVal;
                break;
            }
            case CALL:
            {
                
                // function to call
                struct Function fnc;
                copy_function(&fnc, &functions[s_top(&fn.stack).values[0]]);
                s_pop(&fn.stack);
                
                fnc.params = malloc(fnc.paramCount * sizeof(struct Data));
                for (int i = 0; i < fnc.paramCount; i++)
                {
                    
                    fnc.params[i] = s_top(&fn.stack);
                    s_pop(&fn.stack);
                }
                
                s_push(&fn.stack, call(fnc));
                
                break;
            }
                
            case P_0:
                s_push(&fn.stack, fn.params[0]);
                break;
            case P_1:
                s_push(&fn.stack, fn.params[1]);
                break;
            case P_2:
                s_push(&fn.stack, fn.params[2]);
                break;
            case P_3:
                s_push(&fn.stack, fn.params[3]);
                break;
            case P_4:
                s_push(&fn.stack, fn.params[4]);
                break;
            case P_5:
                s_push(&fn.stack, fn.params[5]);
                break;
            case P_B:
                s_push(&fn.stack, fn.params[(int)++fn.PC]);
                break;
            case P_S:
                s_push(&fn.stack, fn.params[ucharToShort(fn.intstructions + fn.PC + 1)]);
                fn.PC += 2;
                break;
                
            case L_0:
                s_push(&fn.stack, v_get(&fn.varArr, 0));
                break;
            case L_1:
                s_push(&fn.stack, v_get(&fn.varArr, 1));
                break;
            case L_2:
                s_push(&fn.stack, v_get(&fn.varArr, 2));
                break;
            case L_3:
                s_push(&fn.stack, v_get(&fn.varArr, 3));
                break;
            case L_4:
                s_push(&fn.stack, v_get(&fn.varArr, 4));
                break;
            case L_5:
                s_push(&fn.stack, v_get(&fn.varArr, 5));
                break;
                
            case L_B:
                s_push(&fn.stack, v_get(&fn.varArr, (int)++fn.PC));
                break;
            case L_S:
                s_push(&fn.stack, v_get(&fn.varArr, ucharToShort(fn.intstructions + fn.PC + 1)));
                fn.PC += 2;
                break;
                
            case S_0:
                v_set(&fn.varArr, 0, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case S_1:
                v_set(&fn.varArr, 1, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case S_2:
                v_set(&fn.varArr, 2, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case S_3:
                v_set(&fn.varArr, 3, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case S_4:
                v_set(&fn.varArr, 4, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case S_5:
                v_set(&fn.varArr, 5, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
                
            case S_B:
                v_set(&fn.varArr, (int)++fn.PC, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case S_S:
                v_set(&fn.varArr, ucharToShort(fn.intstructions + fn.PC + 1), s_top(&fn.stack));
                s_pop(&fn.stack);
                fn.PC += 2;
                break;
            case GL_0:
                s_push(&fn.stack, v_get(&globalVars, 0));
                break;
            case GL_1:
                s_push(&fn.stack, v_get(&globalVars, 1));
                break;
            case GL_2:
                s_push(&fn.stack, v_get(&globalVars, 2));
                break;
            case GL_3:
                s_push(&fn.stack, v_get(&globalVars, 3));
                break;
            case GL_4:
                s_push(&fn.stack, v_get(&globalVars, 4));
                break;
            case GL_5:
                s_push(&fn.stack, v_get(&globalVars, 5));
                break;
                
            case GL_B:
                s_push(&fn.stack, v_get(&globalVars, (int)++fn.PC));
                break;
            case GL_S:
                s_push(&fn.stack, v_get(&globalVars, ucharToShort(fn.intstructions + fn.PC + 1)));
                fn.PC += 2;
                break;

            case GS_0:
                v_set(&globalVars, 0, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case GS_1:
                v_set(&globalVars, 1, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case GS_2:
                v_set(&globalVars, 2, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case GS_3:
                v_set(&globalVars, 3, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case GS_4:
                v_set(&globalVars, 4, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case GS_5:
                v_set(&globalVars, 5, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
                
            case GS_B:
                v_set(&globalVars, (int)++fn.PC, s_top(&fn.stack));
                s_pop(&fn.stack);
                break;
            case GS_S:
                v_set(&globalVars, ucharToShort(fn.intstructions + fn.PC + 1), s_top(&fn.stack));
                s_pop(&fn.stack);
                fn.PC += 2;
                break;
                
            case DUP:
                s_push(&fn.stack, s_top(&fn.stack));
                break;
            case GET_CHAR:
            {
                // get a char from stdin
                struct Data val;
                init_data(&val, 1);
                val.values[0] = getchar();
                s_push(&fn.stack, val);
                break;
            }
            case PUT_CHAR:
                // put char on stdout
                putchar(s_top(&fn.stack).values[0]);
                s_pop(&fn.stack);
                break;
            case PUT_CHARS:
            {
                for (int i = 0; i < s_top(&fn.stack).size; i++) {
                    putchar(s_top(&fn.stack).values[i]);
                }
                
                s_pop(&fn.stack);
                break;
            }
            case ZERO:
            {
                // push zero onto the stack
                s_push(&fn.stack, create_data(0));
                break;
            }
            case MVU:
                // move PC up n amount of lines
                fn.PC -= s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                break;
            case SLEEP:
            {
                // sleep the script for n amount of miliseconds
                
                int mseconds = s_top(&fn.stack).values[0];
                
                msleep(&mseconds);
                
                s_pop(&fn.stack);
                
                break;
            }
            case DGET:
            {
                int index = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                s_push(&fn.stack, create_data(s_top(&fn.stack).values[index]));
                break;
            }
            case DSET:
            {
                int index = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                int value = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                s_top(&fn.stack).values[index] = value;
                break;
            }
            case DCPY:
            {
                // TODO: do this, dont feel like doing this one rn
                struct Data dest = s_top(&fn.stack);
                s_pop(&fn.stack);
                struct Data src = s_top(&fn.stack);
                s_pop(&fn.stack);
                
                struct Data res;
                init_data(&res, dest.size + src.size);
                
                for (int i = 0; i < src.size; i++) {
                    res.values[i] = src.values[i];
                }
                
                for (int j = 0; j < dest.size; j++) {
                    res.values[src.size + j] = dest.values[j];
                    
                }
                
                s_push(&fn.stack, res);
                break;
            }
            case DSIZE:
            {
                s_push(&fn.stack, create_data((int)s_top(&fn.stack).size));
            }
                /// TODO: CHANGE ALL OF THESE TO JUST PUT A 1 OR ZERO ONTO THE STACK AFTER EVALUATING. THEN YOU CAN HAVE A JMP ONLY _IF_ THE TOP OF THE STACK SAYS TRUE. THIS IS SO MUCH MORE EFFICIENT
            case LT:
            {
                // operator 1
                int op1 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // operator 2
                int op2 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // push the result onto the stack:
                struct Data res;
                init_data(&res, 1);
                
                res.values[0] = op1 > op2;
                
                s_push(&fn.stack, res);
                break;
            }
            case GT:
            {
                // operator 1
                int op1 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // operator 2
                int op2 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // push the result onto the stack:
                struct Data res;
                init_data(&res, 1);
                
                res.values[0] = op1 < op2;
                
                s_push(&fn.stack, res);
                break;
            }
            case GTE:
            {
                // operator 1
                int op1 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // operator 2
                int op2 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // push the result onto the stack:
                struct Data res;
                init_data(&res, 1);
                
                res.values[0] = op1 <= op2;
                
                s_push(&fn.stack, res);
                break;
            }
            case LTE:
            {
                // operator 1
                int op1 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // operator 2
                int op2 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // push the result onto the stack:
                struct Data res;
                init_data(&res, 1);
                
                res.values[0] = op1 >= op2;
                
                s_push(&fn.stack, res);
                break;
            }
            case EQ:
            {
                // operator 1
                int op1 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // operator 2
                int op2 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // push the result onto the stack:
                struct Data res;
                init_data(&res, 1);
                
                res.values[0] = op1 == op2;
                
                s_push(&fn.stack, res);
                break;
            }
            case NEQ:
            {
                // operator 1
                int op1 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // operator 2
                int op2 = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // push the result onto the stack:
                struct Data res;
                init_data(&res, 1);
                
                res.values[0] = op1 != op2;
                
                s_push(&fn.stack, res);
                break;
            }
            case SKIP:
                fn.PC += s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                break;
            case COMP:
            {
                // get the numbe of lines to skip if evaluates to FALSE:
                int linesToSkip = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // get the true or false to compare.
                int compareRes = s_top(&fn.stack).values[0];
                s_pop(&fn.stack);
                
                // do the comparing
                if (!compareRes) {
                    fn.PC += linesToSkip;
                }
                break;
            }
            case BREAKPOINT:
                s_top(&fn.stack);
                break;
        } // end of switch
    }; // end of for loop
    struct Data retVal;
    
    init_data(&retVal, 1);
    
    // is this supposed to be here?
    retVal.values[0] = -7;
    // why does this breakpoint over here?
    return retVal;
}

#endif // RUNTIME_H_INCLUDED
