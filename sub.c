#include <stdio.h>
#include "header.h"

int perform_subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, int isNegative)
{
    extern Dlist *headR, *tailR;
    extern int sign;
    sign = isNegative;

    Dlist *t1 = tail1;
    Dlist *t2 = tail2;
    int borrow = 0;

    while (t1 || t2)
    {
        int d1 = t1 ? t1->data : 0;
        int d2 = t2 ? t2->data : 0;

        d1 -= borrow;

        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else borrow = 0;

        insert_at_first(&headR, &tailR, d1 - d2);

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    while (headR && headR->data == 0 && headR->next)
        delete_at_first(&headR, &tailR);

    printf("Result: ");
    if (sign) printf("-");
    print_list(headR);

    return SUCCESS;
}
