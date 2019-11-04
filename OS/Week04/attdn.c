#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 10

void print_decimal(unsigned long v){
    printf("%ld\n", v);
}

void print_hexadecimal(unsigned long v){
    printf("0x");
    printf("%lx\n", v);
}

void print_binary(unsigned long v){
    printf("0b");
    if (v == 0){
        printf("0\n");
        return;
    }
    int remainder= 0;
    while (v!=0){
        remainder= v%2;
        v= v/2;
        printf("%d", remainder);
    }
    printf("\n");
}

int main (int argc, char* argv[]){
    int v= 129;
    print_decimal(v);
    print_hexadecimal(v);
    print_binary(v);
}
