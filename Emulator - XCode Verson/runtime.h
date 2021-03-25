#ifndef RUNTIME_H_INCLUDED
#define RUNTIME_H_INCLUDED

#include "stack.h"
#include "array.h"
#include "function.h"
#include "BinKeys.h"

union Value *constants;
struct Vector *arrays;


union Value call(struct Function fn)
{
    s_init(&fn.stack, 8);
    v_init(&fn.varArr);

    for (fn.PC = 0; fn.PC < fn.numIntructions; fn.PC++)
    {
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
            int a = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            int b = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            union Value val;
            val.intValue = a + b;

            s_push(&fn.stack, val);
            break;
        }
        case ISUB:
        {

            int a = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            int b = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            union Value val;
            val.intValue = b - a;

            s_push(&fn.stack, val);
            break;
        }
        case IMUL:
        {

            int a = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            int b = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            union Value val;
            val.intValue = b * a;

            s_push(&fn.stack, val);
            break;
        }
        case IDIV:
        {

            int a = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            int b = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            union Value val;
            val.intValue = (int)(b / a);

            s_push(&fn.stack, val);
            break;
        }
        case IMOD:
        {

            int a = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            int b = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            union Value val;
            val.intValue = b % a;

            s_push(&fn.stack, val);
            break;
        }

        case RET:
        {
            union Value retVal = s_top(&fn.stack);
            s_free(&fn.stack);

            return retVal;
            break;
        }
        case CALL:
        {

            // function to call
            struct Function fnc;
            copy_function(&fnc, &functions[s_top(&fn.stack).intValue]);
            s_pop(&fn.stack);

            fnc.params = (union Value *)malloc(fnc.paramCount * sizeof(union Value));
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

        case DUP:
            s_push(&fn.stack, s_top(&fn.stack));
            break;

        case CON:
        {
            int op1 = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            int op2 = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            int toSkip = s_top(&fn.stack).intValue;
            s_pop(&fn.stack);

            if (op1 != op2)
            {
                // function to call
                struct Function fnc;
                copy_function(&fnc, &functions[s_top(&fn.stack).intValue]);
                s_pop(&fn.stack);

                fnc.params = (union Value *)malloc(fnc.paramCount * sizeof(union Value));
                for (int i = 0; i < fnc.paramCount; i++)
                {
                    fnc.params[i] = s_top(&fn.stack);
                    s_pop(&fn.stack);
                }

                s_push(&fn.stack, call(fnc));
            }
            else
            {
                fn.PC += toSkip;
            }
            
            break;
        }
        case GET_CHAR:
        {
            union Value val;
            val.intValue = getchar();
            s_push(&fn.stack, val);
            break;
        }
        case PUT_CHAR:
            putchar(s_top(&fn.stack).intValue);
            s_pop(&fn.stack);
            break;
        case ZERO:
        {
            union Value val;
            val.intValue = 0;
            s_push(&fn.stack, val);
            break;
        }
        case MVU:
            fn.PC -= s_top(&fn.stack).intValue;
            s_pop(&fn.stack);
            break;
        }
    };
}

#endif // RUNTIME_H_INCLUDED
