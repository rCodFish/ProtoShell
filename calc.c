#include "shell.h"
#include <math.h>

//math
void calc(char *value1, char *op, char *value2){
    float valueA = atof(value1); 
    float valueB = atof(value2); 
    float res = 0;

    switch (*op)
    {
    case '+':
        res = valueA + valueB;
        break;
    case '-':
        res = valueA - valueB;
        break;
    case '*':
        res = valueA * valueB;
        break;
    case '/':
        if(valueB == 0){
            printf("Value B can't be 0\n");
            return;
        }
        res = valueA / valueB;
        break;
    case '^':
        res = powf(valueA, valueB);
        break;
    default:
        printf("Operacao nao existente");
        return;
        break;
    }

    printf("Resultado calc %f\n", res);

    return;
}
