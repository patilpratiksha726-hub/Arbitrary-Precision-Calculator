#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

static int validate_number(char *s)
{
    int i = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;

    if (s[i] == '\0')
        return FAILURE;

    for (; s[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)s[i]))
            return FAILURE;
    }

    return SUCCESS;
}

int validate_inputs(char *opr1, char *opr2, char op)
{
    if (!(op == '+' || op == '-' || op == 'x' || op == 'X' ||
          op == '*' || op == '/'))
    {
        printf("Error: Invalid operator! Use +  -  x  X  *  /\n");
        return FAILURE;
    }

    if (validate_number(opr1) == FAILURE)
    {
        printf("Error: Operand1 is invalid: %s\n", opr1);
        return FAILURE;
    }

    if (validate_number(opr2) == FAILURE)
    {
        printf("Error: Operand2 is invalid: %s\n", opr2);
        return FAILURE;
    }

    if (op == '/')
    {
        char *p = opr2;
        if (*p == '+' || *p == '-')
            p++;

        int all_zero = 1;
        for (; *p; p++)
        {
            if (*p != '0')
            {
                all_zero = 0;
                break;
            }
        }

        if (all_zero)
        {
            printf("Error: Division by zero not allowed.\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}
