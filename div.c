#include <stdio.h>
#include <stdlib.h>
#include "header.h"

extern Dlist *headR, *tailR;
extern int sign;

static void subtract_lists(Dlist **h1, Dlist **t1, Dlist *h2, Dlist *t2)
{
    Dlist *tA = *t1;
    Dlist *tB = t2;
    int borrow = 0;

    while (tA || tB)
    {
        int d1 = tA ? tA->data : 0;
        int d2 = tB ? tB->data : 0;

        d1 -= borrow;
        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else borrow = 0;

        if (tA)
        {
            tA->data = d1 - d2;
            tA = tA->prev;
        }
        if (tB) tB = tB->prev;
    }

    while (*h1 && (*h1)->data == 0 && (*h1)->next)
        delete_at_first(h1, t1);
}

int perform_division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2)
{
    // Check divide by zero
    Dlist *tmp = head2;
    int isZero = 1;
    while (tmp)
    {
        if (tmp->data != 0) { isZero = 0; break; }
        tmp = tmp->next;
    }
    if (isZero)
    {
        printf("Error: Division by zero!\n");
        return FAILURE;
    }

    // If numerator < denominator → quotient is 0
    if (compare_lists(head1, head2) < 0)
    {
        insert_at_first(&headR, &tailR, 0);
        return SUCCESS;
    }

    Dlist *qH = NULL, *qT = NULL;
    Dlist *tempH = NULL, *tempT = NULL;

    while (head1)
    {
        insert_at_last(&tempH, &tempT, head1->data);
        delete_at_first(&head1, &tail1);

        while (tempH && tempH->data == 0 && tempH->next)
            delete_at_first(&tempH, &tempT);

        int count = 0;

        while (compare_lists(tempH, head2) >= 0)
        {
            subtract_lists(&tempH, &tempT, head2, tail2);
            count++;
        }

        insert_at_last(&qH, &qT, count);
    }

    while (qH && qH->data == 0 && qH->next)
        delete_at_first(&qH, &qT);

    // copy result
    headR = qH;
    tailR = qT;

    return SUCCESS;
}
