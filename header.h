#ifndef HEADER_H
#define HEADER_H

#define SUCCESS 0
#define FAILURE -1

// Doubly linked list structure
typedef struct Dlist
{
    int data;
    struct Dlist *prev;
    struct Dlist *next;
} Dlist;

// Global operand/result pointers
extern Dlist *head1, *tail1;
extern Dlist *head2, *tail2;
extern Dlist *headR, *tailR;

// Global sign flag
extern int sign;

// Function declarations
int validate_inputs(char *opr1, char *opr2, char op);
int insert_at_first(Dlist **head, Dlist **tail, int data);
int insert_at_last(Dlist **head, Dlist **tail, int data);
int add_d_list(char *opr1, char *opr2);  
int compare_lists(Dlist *h1, Dlist *h2);
int delete_at_first(Dlist **head, Dlist **tail);
int perform_addition();
int perform_subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, int isNegative);
int mul_d_list(char *opr1, char *opr2);
int add_two_lists(Dlist **headR, Dlist **tailR, Dlist *h2, Dlist *t2);
int perform_division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2);

void print_list(Dlist *head);


#endif
