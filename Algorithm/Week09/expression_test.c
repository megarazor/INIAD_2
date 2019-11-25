/* expression_test.c */

#include <stdlib.h>
#include <stdio.h>
#include "expression.h"

int main(int argc, char** argv) {
    /* Node* node1 = expression_construct_number(2);
    Node* node2 = expression_construct_number(5);
    Node* node3 = expression_construct_number(3);
    Node* node4 = expression_construct_number(2);
    Node* sub = expression_construct_operator(OPERATOR_SUB, node2, node3);
    Node* mul = expression_construct_operator(OPERATOR_MUL, sub, node4);
    Node* add = expression_construct_operator(OPERATOR_ADD, node1, mul);

    printf("Prefix notation: ");
    expression_print_prefix(add);
    printf("\n");

    printf("Infix notation: ");
    expression_print_infix(add);
    printf("\n");

    printf("Postfix notation: ");
    expression_print_postfix(add);
    printf("\n");

    printf("Evaluated as: %d\n", expression_eval(add));

    expression_free(add); */

    char str[1024]= "( ( 2 - ( 1   * 3 ) )  + (( ( 5 / 1 )  -  3 ) *  2 ))";
    printf("%s\n", str);
    Node* tree= expression_parse_infix(str);

    printf("Prefix notation: ");
    expression_print_prefix(tree);
    printf("\n");

    printf("Infix notation: ");
    expression_print_infix(tree);
    printf("\n");

    printf("Postfix notation: ");
    expression_print_postfix(tree);
    printf("\n");

    printf("Evaluated as: %d\n", expression_eval(tree));

    expression_free(tree);

    return 0;
}
