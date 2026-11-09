/***************************************************************
 *                    PROJECT DOCUMENTATION
 *               ARITHMETIC PRECISION CALCULATOR (APC)
 *   Using 2D Linked List, Command Line Input and Modulus (%)
 *
 * -------------------------------------------------------------
 * 1. INTRODUCTION
 * -------------------------------------------------------------
 * APC performs arithmetic operations on very large integers which
 * cannot be stored in normal C data types. Digits are stored in a
 * custom 2D Linked List structure, enabling unlimited precision.
 *
 * Supported operations:
 *      - Addition
 *      - Subtraction
 *      - Multiplication
 *      - Division
 *      - Modulus (Remainder)
 *
 * Input Format:
 *      ./apc <operand1> <operator> <operand2>
 *
 * -------------------------------------------------------------
 * 2. DATA STRUCTURE : 2D LINKED LIST
 * -------------------------------------------------------------
 * Each digit is stored in:
 *
 *      struct Node {
 *          int data;          // one digit (0–9)
 *          struct Node *next; // next digit in row
 *          struct Node *down; // next row (multiplication rows, etc.)
 *      };
 *
 * Benefits:
 *      - Arbitrary number size
 *      - Easy digit-level operations
 *      - Efficient carry/borrow handling
 *      - Ideal for long division and modulus
 *
 * -------------------------------------------------------------
 * 3. COMMAND LINE INPUT
 * -------------------------------------------------------------
 * argv[1] → first operand
 * argv[2] → operator (+, -, x, /, %)
 * argv[3] → second operand
 *
 * Valid examples:
 *      ./apc 999999999 % 123
 *      ./apc 987654321 / 12345
 *      ./apc 123456 + 654321
 *
 * -------------------------------------------------------------
 * 4. DIVISION & MODULUS LOGIC (LONG DIVISION METHOD)
 * -------------------------------------------------------------
 * Division and Modulus both use the same long-division algorithm.
 *
 * dividend = OPR.head1
 * divisor  = OPR.head2
 *
 * STEP 1: Check divide-by-zero
 *      If divisor is zero → return FAILURE
 *
 * STEP 2: Build partial dividend (tempH)
 *      Read digits of dividend one-by-one.
 *
 * STEP 3: Compare partial dividend with divisor
 *      while (tempH >= divisor):
 *            subtract divisor from tempH
 *            increment div (quotient digit)
 *
 * STEP 4: Quotient digit is appended into quotient list
 *
 * STEP 5: After all digits processed:
 *      - Quotient  → OPR.headR (final result of '/')
 *      - Remainder → tempH     (final result of '%')
 *
 * SUMMARY:
 *      a / b → quotient
 *      a % b → remainder
 *
 * Modulus is simply the remainder linked list after division.
 *
 *
 * -------------------------------------------------------------
 * 5. MODULUS (%) OPERATION DETAILS
 * -------------------------------------------------------------
 * Modulus does NOT require a separate algorithm.
 * It directly reuses the division logic.
 *
 * How modulus works:
 *      1. Perform long division using linked lists.
 *      2. Ignore the quotient.
 *      3. The final tempH (partial dividend left)
 *         is the remainder.
 *
 * Therefore:
 *      a % b  = remainder obtained after long division
 *
 * Example:
 *      98765 % 123
 *
 * During division:
 *      Quotient  = 802
 *      Remainder =  89  ← (This is the modulus result)
 *
 * Implementation Steps:
 *      - Call division() internally
 *      - After division completes:
 *            remainder = tempH
 *      - Print the remainder linked list as the result of '%'.
 *
 * -------------------------------------------------------------
 * 6. COMPARE FUNCTION
 * -------------------------------------------------------------
 * compare(a, b):
 *      - Removes leading zeros from a
 *      - Compares digit count
 *      - If equal length → compares digit-by-digit
 *
 * Returns:
 *      SUCCESS → a >= b
 *      FAILURE → a < b
 *
 * Used in:
 *      - Division
 *      - Modulus
 *      - Subtraction validation
 *
 * -------------------------------------------------------------
 * 7. FEATURES
 * -------------------------------------------------------------
 * - Unlimited precision using 2D linked list
 * - Command line user interface
 * - Handles very large numbers
 * - Manual arithmetic logic (add, sub, mul, div, mod)
 * - Proper quotient–remainder separation for division/modulus
 *
 * -------------------------------------------------------------
 * 8. APPLICATIONS
 * -------------------------------------------------------------
 * - Cryptography (RSA, Big Integers)
 * - Banking and finance
 * - Arbitrary precision mathematics
 * - Scientific computations
 *
 * -------------------------------------------------------------
 * 9. CONCLUSION
 * -------------------------------------------------------------
 * The APC project implements full big-integer arithmetic using a 
 * custom 2D linked list. Long division is used to compute both 
 * quotient and remainder, enabling correct implementation of the 
 * modulus (%) operator.
 *
 * This project demonstrates:
 *      - Linked list manipulation
 *      - Command-line processing
 *      - Manual arithmetic algorithm design
 *      - Efficient handling of large integer values
 *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Global lists declared here
Dlist *head1 = NULL, *tail1 = NULL;
Dlist *head2 = NULL, *tail2 = NULL;
Dlist *headR = NULL, *tailR = NULL;

int sign = 0;  // 0 = positive, 1 = negative (used for result)

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./a.out <num1> <operator> <num2>\n");
        return 1;
    }

    char *opr1 = argv[1];
    char *opr2 = argv[3];
    char op = argv[2][0];

    // Validate input first
    if (validate_inputs(opr1, opr2, op) == FAILURE)
        return 1;

    printf("Performing: %s %c %s\n", opr1, op, opr2);

    // Detect signs
    int op1Sign = (*opr1 == '-') ? -1 : 1;
    int op2Sign = (*opr2 == '-') ? -1 : 1;

    // Remove +/- before inserting into list
    if (*opr1 == '-' || *opr1 == '+') opr1++;
    if (*opr2 == '-' || *opr2 == '+') opr2++;

    // Clear lists before operation
    head1 = tail1 = head2 = tail2 = headR = tailR = NULL;

    // Store digits into DLL
    add_d_list(opr1, opr2);

    switch(op)
    {
        case '+':
        {
            if (op1Sign == op2Sign)
            {
                sign = (op1Sign == -1);
                perform_addition();
            }
            else
            {
                int cmp = compare_lists(head1, head2);
                if (cmp >= 0)
                    perform_subtraction(head1, tail1, head2, tail2, (op1Sign == -1));
                else
                    perform_subtraction(head2, tail2, head1, tail1, (op2Sign == -1));
            }
        }
        break;

        case '-':
        {
            if (op1Sign != op2Sign)
            {
                sign = (op1Sign == -1);
                perform_addition();
            }
            else
            {
                int cmp = compare_lists(head1, head2);
                if (cmp >= 0)
                    perform_subtraction(head1, tail1, head2, tail2, (op1Sign == -1));
                else
                    perform_subtraction(head2, tail2, head1, tail1, !(op1Sign == -1));
            }
        }
        break;

        case 'x':
        case '*':
            sign = (op1Sign != op2Sign);  // negative result if different signs
            mul_d_list(opr1, opr2);       // perform multiplication
            break;


        case '/':
        {
            int resultSign = (op1Sign != op2Sign);

            perform_division(head1, tail1, head2, tail2);

            while (headR && headR->data == 0 && headR->next)
                delete_at_first(&headR, &tailR);

            printf("Result: ");
            if (resultSign) printf("-");

            print_list(headR);
        }
        break;

        default:
            printf("Error: Unsupported operator\n");
            return 1;
    }

    printf("\nProgram finished ✓\n");
    return 0;
}
