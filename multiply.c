#include <stdio.h>
#include "header.h"

int add_two_lists(Dlist **headR, Dlist **tailR, Dlist *h2, Dlist *t2)
{
    Dlist *t1 = *tailR;
    int carry = 0;

    while (t1 || t2)
    {
        int d1 = t1 ? t1->data : 0;
        int d2 = t2 ? t2->data : 0;

        int sum = d1 + d2 + carry;
        carry = sum / 10;

        if (t1) t1->data = sum % 10, t1 = t1->prev;
        else insert_at_first(headR, tailR, sum % 10);

        if (t2) t2 = t2->prev;
    }
    if (carry) insert_at_first(headR, tailR, carry);

    return SUCCESS;
}

int mul_d_list(char *opr1, char *opr2)
{
    extern Dlist *head1,*tail1,*head2,*tail2,*headR,*tailR;
    extern int sign;

    Dlist *t2 = tail2;
    int shift = 0;

    while (t2)
    {
        int carry = 0;
        Dlist *hTemp=NULL,*tTemp=NULL;
        for (int i=0;i<shift;i++) insert_at_last(&hTemp,&tTemp,0);

        Dlist *t1 = tail1;
        while (t1)
        {
            int mul = t1->data * t2->data + carry;
            insert_at_first(&hTemp,&tTemp,mul%10);
            carry = mul/10;
            t1=t1->prev;
        }
        if (carry) insert_at_first(&hTemp,&tTemp,carry);

        if (!headR) headR=hTemp, tailR=tTemp;
        else add_two_lists(&headR,&tailR,hTemp,tTemp);

        shift++;
        t2 = t2->prev;
    }

    while (headR && headR->data==0 && headR->next)
        delete_at_first(&headR,&tailR);

    printf("Result: ");
    if (sign) printf("-");
    print_list(headR);

    return SUCCESS;
}
