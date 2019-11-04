#include <stdio.h>
#include <stdlib.h>
#include "big_int.h"

_T decimal = 10000;

void push(struct big_integer *Big_A, _T value){
        struct integer *t = malloc(sizeof(struct integer));
        t->n = value;
        t->next = NULL;
				
        if (Big_A->final){
            Big_A->final->next= t;
            t->forward= Big_A->final;
            Big_A->final= t;												
        }
        else {
            Big_A->unit= t;
            Big_A->final= t;	
            t->forward= NULL;						
        }
}

struct big_integer fact(int n){
        struct big_integer Big_A = {NULL, NULL};
        struct integer *A;

        push(&Big_A, 1);

        for (_T i = 2; i <= n; i++ ){
                _T carry = 0;
                _T tmp = 0;
                for (A = Big_A.unit; A; A=A->next){
                    tmp= A->n*i + carry;
                    if (tmp>=decimal) {
                        carry= tmp/decimal;
                        tmp= tmp%decimal;
                    }
                    else carry= 0;
                    A->n= tmp;
                }
                if (carry != 0){
                        push(&Big_A, carry);
                }
        }
        return Big_A;
}

struct big_integer add(struct big_integer Big_A, struct big_integer Big_B){
        struct big_integer Big_C = {NULL, NULL};
        struct integer *A, *B, *t;
        A = Big_A.unit;
        B = Big_B.unit;

        _T carry = 0;
				
        while ((A!=NULL) && (B!=NULL)) {
            _T tmp= A->n + B->n + carry;
            push(&Big_C, tmp%decimal);
            carry= tmp/decimal;
            A= A->next;
            B= B->next;
        }
        if ((A==NULL) && (B==NULL)) {
            push(&Big_C, carry);
            carry= 0;
        }
        else {
            if (A!=NULL) t= A;
            else t= B;
            while (t!=NULL) {
                _T tmp2= t->n + carry;
                push(&Big_C, tmp2%decimal);
                carry= tmp2/decimal;
                t= t->next;
            }
            if (carry!=0) {
            push(&Big_C, carry);
            }
        }
        
        return Big_C;
}

void print(struct big_integer Big_A){
        struct integer *A;
        A = Big_A.final;
        printf("%d",A->n);
        for (A = A->forward; A; A=A->forward){
                printf("%04d",A->n);
        }
        printf("\n");
}

void big_integer_free(struct big_integer Big_A){
        for (struct integer *A = Big_A.unit; A; A=A->next){
                free(A);
        }
}
