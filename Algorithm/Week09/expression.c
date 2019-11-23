/* expression.c */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_stack.h"
#include "expression.h"

Node* expression_construct_operator(NodeType type, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));

    node->type = type;  
    node->value = 0;

    node->left = left;
    node->right = right;

    return node;
}

Node* expression_construct_number(int value) {
    Node* node = (Node*)malloc(sizeof(Node));

    node->type = NUMBER;
    node->value = value;

    node->left = NULL;
    node->right = NULL;
    
    return node;
}

void expression_free(Node* tree) {
    if(tree->left != NULL) {
        expression_free(tree->left);
    }
    if(tree->right != NULL) {
        expression_free(tree->right);
    }
    free(tree);
}

void print_node(Node* node) {    
    switch(node->type) {
        case OPERATOR_ADD:
            printf(" + ");
            break;
        case OPERATOR_SUB:
            printf(" - ");
            break;
        case OPERATOR_MUL:
            printf(" * ");
            break;
        case OPERATOR_DIV:
            printf(" / ");
            break;
        default:
            printf(" %d ", node->value);
            break;
    }
}

void expression_print_prefix(Node* tree) {
    print_node(tree);

    if(tree->left != NULL) {
        expression_print_prefix(tree->left);
    }

    if(tree->right != NULL) {
        expression_print_prefix(tree->right);
    }
}

void expression_print_infix(Node* tree) {
    if(tree->left != NULL) {
        printf("(");
        expression_print_infix(tree->left);
    }

    print_node(tree);

    if(tree->right != NULL) {
        expression_print_infix(tree->right);
        printf(")");
    }
}

void expression_print_postfix(Node* tree) {
    if(tree->left != NULL) {
        expression_print_prefix(tree->left);
    }

    if(tree->right != NULL) {
        expression_print_prefix(tree->right);
    }
    print_node(tree);
}

Node* expression_parse_prefix(char *str) {
    char *token = strtok(str, " \n");
    if(token == NULL) {
        return NULL;
    }
    if(strcmp(token, "+") == 0) {
        Node* op1 = expression_parse_prefix(NULL);
        Node* op2 = expression_parse_prefix(NULL);
        return expression_construct_operator(OPERATOR_ADD, op1, op2);
    } else if(strcmp(token, "-") == 0) {
        Node* op1 = expression_parse_prefix(NULL);
        Node* op2 = expression_parse_prefix(NULL);
        return expression_construct_operator(OPERATOR_SUB, op1, op2);
    } else if(strcmp(token, "*") == 0) {
        Node* op1 = expression_parse_prefix(NULL);
        Node* op2 = expression_parse_prefix(NULL);
        return expression_construct_operator(OPERATOR_MUL, op1, op2);
    } else if(strcmp(token, "/") == 0) {
        Node* op1 = expression_parse_prefix(NULL);
        Node* op2 = expression_parse_prefix(NULL);
        return expression_construct_operator(OPERATOR_DIV, op1, op2);
    } else {
        char *end;
        int value = strtol(token, &end, 10);
        return expression_construct_number(value);
    }
}

Node* expression_parse_infix(char *str){
    char str_[1024];
    int str__count= 0;
    for (int i= 0; i < strlen(str); i++){ // Copy str to a new string str_
        if (str[i] == '(' || str[i] == ')'){  // Make sure there are spaces between all the tokens. "((" is changed to "( ("
            if (i > 0){
                if (str[i - 1] == '(' || str[i - 1] == ')'){
                    str_[str__count++]= ' ';
                }
            }
        }
        str_[str__count++]= str[i];
    }
    
    for (int i= strlen(str_) - 1; i > 0; i--){ // Remove the last ')'
        if (str_[i] == ')'){
            str_[i]= ' ';
            break;
        }
    }

    char *token= strtok(str_, " \n");
    if (strcmp(token, "(") != 0){ // The expression is just a number, not a calculation
        char *end;
        int value = strtol(token, &end, 10);
        return expression_construct_number(value);
    }

    // Split the expression into two parts: left side and right side of the operation sign
    char op1[1024]= "\0";
    char op2[1024]= "\0";
    char op[3]= "";
    int open_prth_count= 0, close_prth_count= 0;
    
    while(1){ // Left side
        token= strtok(NULL, " \n");
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0){
            if (open_prth_count == close_prth_count){ // If it's the operation sign in the middle of the expression
                strcpy(op, token);
                break;
            }
            else goto parse_next;
        }
        else{
            parse_next:
            strcat(op1, token);
            strcat(op1, " ");
            if (strcmp(token, "(") == 0){
                open_prth_count++;
            }
            else if (strcmp(token, ")") == 0){
                close_prth_count++;
            }
        }
    }

    while(1) { // Right side
        token= strtok(NULL, " \n");
        if (token != NULL){ 
            strcat(op2, token);
            strcat(op2, " ");
        }
        else{ // End of expression
            // printf("op1: %s<end>\n", op1);
            // printf("op: %s<end>\n", op);
            // printf("op2: %s<end>\n\n", op2);
            if(strcmp(op, "+") == 0) {
                Node* op1_node = expression_parse_infix(op1);
                Node* op2_node = expression_parse_infix(op2);
                return expression_construct_operator(OPERATOR_ADD, op1_node, op2_node);
            }
            else if(strcmp(op, "-") == 0) {
                Node* op1_node = expression_parse_infix(op1);
                Node* op2_node = expression_parse_infix(op2);
                return expression_construct_operator(OPERATOR_SUB, op1_node, op2_node);
            }
            else if(strcmp(op, "*") == 0) {
                Node* op1_node = expression_parse_infix(op1);
                Node* op2_node = expression_parse_infix(op2);
                return expression_construct_operator(OPERATOR_MUL, op1_node, op2_node);
            }
            else {
                Node* op1_node = expression_parse_infix(op1);
                Node* op2_node = expression_parse_infix(op2);
                return expression_construct_operator(OPERATOR_DIV, op1_node, op2_node);
            }
        }
    }
}

Node* expression_parse_postfix(char *str) {
    Node* result = NULL;
    STACK stack = stack_construct();
    char *token;
    for(token = strtok(str, " \n"); token != NULL; token = strtok(NULL, " \n")) {
        if(strcmp(token, "+") == 0) {
            Node* op2 = stack_pop(stack);
            Node* op1 = stack_pop(stack);
            Node* operator = expression_construct_operator(OPERATOR_ADD, op1, op2);
            stack_push(stack, operator);
        } else if(strcmp(token, "-") == 0) {
            Node* op2 = stack_pop(stack);
            Node* op1 = stack_pop(stack);
            Node* operator = expression_construct_operator(OPERATOR_SUB, op1, op2);
            stack_push(stack, operator);
        } else if(strcmp(token, "*") == 0) {
            Node* op2 = stack_pop(stack);
            Node* op1 = stack_pop(stack);
            Node* operator = expression_construct_operator(OPERATOR_MUL, op1, op2);
            stack_push(stack, operator);
        } else if(strcmp(token, "/") == 0) {
            Node* op2 = stack_pop(stack);
            Node* op1 = stack_pop(stack);
            Node* operator = expression_construct_operator(OPERATOR_DIV, op1, op2);
            stack_push(stack, operator);
        } else {
            char *end;
            int value = strtol(token, &end, 10);
            Node* number = expression_construct_number(value);
            stack_push(stack, number);
        }
    }
    if(! stack_empty(stack)) {
        result = stack_pop(stack);
    }
    while(! stack_empty(stack)) {
        Node* node = stack_pop(stack);
        expression_free(node);
    }
    stack_free(stack);

    return result;
}

void expression_print(Node* tree) {
    if(tree->left != NULL) {
        printf("(");
        expression_print(tree->left);
    }
    
    switch(tree->type) {
        case OPERATOR_ADD:
            printf(" + ");
            break;
        case OPERATOR_SUB:
            printf(" - ");
            break;
        case OPERATOR_MUL:
            printf(" * ");
            break;
        case OPERATOR_DIV:
            printf(" / ");
            break;
        default:
            printf(" %d ", tree->value);
            break;
    }

    if(tree->right != NULL) {
        expression_print(tree->right);
        printf(")");
    }
}

int expression_eval(Node* tree) {
    switch(tree->type) {
        case OPERATOR_ADD:
            return expression_eval(tree->left) + expression_eval(tree->right);
        case OPERATOR_SUB:
            return expression_eval(tree->left) - expression_eval(tree->right);
        case OPERATOR_MUL:
            return expression_eval(tree->left) * expression_eval(tree->right);
        case OPERATOR_DIV:
            return expression_eval(tree->left) / expression_eval(tree->right);
        default:
            return tree->value;
    }
}
