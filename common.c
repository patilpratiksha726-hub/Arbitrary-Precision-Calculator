#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>



int add_d_list(char *opr1, char *opr2)
{
    head1 = tail1 = head2 = tail2 = headR = tailR = NULL;

    int i;
    
    // operand1 → head1
    for (i = strlen(opr1) - 1; i >= 0; i--)
        insert_at_first(&head1, &tail1, opr1[i] - '0');

    // operand2 → head2
    for (i = strlen(opr2) - 1; i >= 0; i--)
        insert_at_first(&head2, &tail2, opr2[i] - '0');

    return SUCCESS;
}


int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new) return FAILURE;
    new->data=data;
    new->prev=NULL;
    new->next=*head;
    if (*head) (*head)->prev=new;
    else *tail=new;
    *head=new;
    return SUCCESS;
}

int insert_at_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new) return FAILURE;
    new->data=data;
    new->next=NULL;
    new->prev=*tail;
    if (*tail) (*tail)->next=new;
    else *head=new;
    *tail=new;
    return SUCCESS;
}

int delete_at_first(Dlist **head, Dlist **tail)
{
    if (!*head) return FAILURE;
    Dlist *temp = *head;
    *head=temp->next;
    if (*head) (*head)->prev=NULL;
    else *tail=NULL;
    free(temp);
    return SUCCESS;
}

void print_list(Dlist *head)
{
    while(head)
    {
        printf("%d",head->data);
        head=head->next;
    }
    printf("\n");
}

int compare_lists(Dlist *h1, Dlist *h2)
{
    int c1=0,c2=0;
    Dlist *t1=h1,*t2=h2;

    while(t1) c1++,t1=t1->next;
    while(t2) c2++,t2=t2->next;

    if (c1>c2) return 1;
    if (c1<c2) return -1;

    while(h1&&h2)
    {
        if (h1->data>h2->data) return 1;
        if (h1->data<h2->data) return -1;
        h1=h1->next;
        h2=h2->next;
    }
    return 0;
}

#include <stdio.h>
#include "header.h"

// Subtract divisor (h2,t2) from temporary number (h1,t1)

int local_subtract(Dlist **h1, Dlist **t1, Dlist *h2, Dlist *t2)
{
    Dlist *p = *t1;
    Dlist *q = t2;
    int borrow = 0;

    while (p || q)
    {
        int d1 = p ? p->data : 0;
        int d2 = q ? q->data : 0;

        d1 -= borrow;

        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else borrow = 0;

        if (p)
        {
            p->data = d1 - d2;
            p = p->prev;
        }

        if (q) q = q->prev;
    }

    // Remove leading zeros
    while (*h1 && (*h1)->data == 0 && (*h1)->next)
        delete_at_first(h1, t1);

    return SUCCESS;
}
