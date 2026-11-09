#include <stdio.h>
#include "header.h"

// Global variable declared in main or validation.c
extern int sign;

int perform_addition()
{
    Dlist *temp1 = tail1;
    Dlist *temp2 = tail2;
    int carry = 0;

    // Perform addition from LSB to MSB
    while (temp1 || temp2)
    {
        int d1 = temp1 ? temp1->data : 0;
        int d2 = temp2 ? temp2->data : 0;

        int sum = d1 + d2 + carry;
        carry = sum / 10;
        sum %= 10;

        insert_at_first(&headR, &tailR, sum);

        if (temp1) temp1 = temp1->prev;
        if (temp2) temp2 = temp2->prev;
    }

    if (carry)
        insert_at_first(&headR, &tailR, carry);

    // Remove leading zeros
    while (headR && headR->data == 0 && headR->next)
        delete_at_first(&headR, &tailR);

    // Final Output
    printf("Result: ");
    if (sign == 1)  // Negative result
        printf("-");

    print_list(headR);
    return SUCCESS;
}
