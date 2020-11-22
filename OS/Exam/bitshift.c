#include <stdio.h>
#include <stdlib.h>

void printBits(int const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int shift_int(int *x){
    *x = ((1 << 3) | (1 << 5)) ^ *x;
    return 0;
}



int main(){
    int *x= malloc(sizeof(int));
    *x= 12;
    printf("x before: \t");
    printBits(sizeof(*x), x);

    shift_int(x);
    printf("x after: \t");
    printBits(sizeof(*x), x);

    return 0;
}