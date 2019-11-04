#include <stdio.h>
#include <stdlib.h>

typedef int _T;

struct integer{
        _T n;
        struct integer* next;
        struct integer* forward;
};

int main(void){
        struct integer *A, *t, *unit, *final;
        _T n = 10000;  // Factorial of n. 
        _T decimal = 10000;  // Base 10000 numbering system
				
        A = malloc(sizeof(struct integer));
        unit = A;
        final = A;
        A->n = 1;
        A->next = NULL;
        A->forward = NULL;
        for (_T i = 2; i <= n; i++ ){
                _T carry = 0;
                _T tmp = 0;
                for (A = unit; A; A=A->next){
                        tmp= A->n*i + carry;
                        if (tmp>=decimal) {
                                carry= tmp/decimal;
                                tmp= tmp%decimal;
                        }
                        else carry= 0;
                        A->n= tmp;
                }
                if (carry != 0){
                        t= malloc(sizeof(struct integer));
                        t->n= carry;
                        t->next= NULL;
                        t->forward= final;
                        final->next= t;
                        final= t;
                        carry= 0;
                }
        }

        A = final;
        printf("%d",A->n);
        for (A = A->forward; A; A=A->forward){
                printf("%04d",A->n);
        }
        printf("\n");

        for (A = unit; A; A=A->next){
                free(A);
        }
}
