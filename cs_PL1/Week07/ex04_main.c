#include <stdio.h>
#include <stdlib.h>
#include "big_int.h"

int main(void){
        struct big_integer A, B, C;
        // C =  1234! + 4321! + 321!
        A = fact(1234);
        B = fact(4321);
        C = add(A, B);

        B = fact(321);
        C = add(C, B);

        printf("C = \n");
        print(C);

        big_integer_free(A);
        big_integer_free(B);
        big_integer_free(C);
}
