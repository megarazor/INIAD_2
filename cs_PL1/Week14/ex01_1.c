#include <stdio.h>

void print(unsigned int c) {
    unsigned int mask= 2147483648; // in binary: 10000000000000000000000000000000
    for (int i= 0; i<sizeof(unsigned int)*8; i++){
        printf ("%d", (c & mask)>>(sizeof(unsigned int)*8 - 1));
        c= c<<1;
    }
    printf("\n"); 
}

unsigned int checkbit(unsigned int c, int offset) {
    unsigned int mask= 1; // 00000000000000000000000000000001
    return ((c>>(offset - 1)) & mask);
}

unsigned int setbit(unsigned int c, int offset) {
    unsigned int mask= 1;
    for (int i= 0; i<(offset - 1); i++) {
        mask*= 2;
    }
    //print(mask);
    return c | mask;
}

unsigned int clearbit(unsigned int c, int offset) {
    unsigned int mask= 4294967295; // 11111111111111111111111111111111
    unsigned int to_minus= 1;
    for (int i= 0; i<(offset - 1); i++) {
        to_minus*= 2;
    }
    //printf("Value to minus: %d\n", to_minus);
    //print(to_minus);
    mask-= to_minus;
    //printf("Mask: ");
    //print(mask);
    return c & mask;
}


int main(){
    //unsigned int a= 123; // 00000000000000000000000001111011
    /* 
    // Reverse order
    for (int i= 0; i<sizeof(unsigned int)*8; i++){
        int rmn= a%2;
        a= a/2;
        printf ("%d", rmn);
    }
    printf("\n"); */

    // Correct order
    
    unsigned int b= 123;
    printf("Check bit %d\n", b);
    printf("B in bin: \n");
    print(b);
    printf("%d %d %d %d\n", checkbit(b, 1), checkbit(b, 2), checkbit(b, 3), checkbit(b, 4));
    printf("\n");

    printf("Set bit %d\n", b);
    printf("B in bin: \n");
    print(b);
    print(setbit(b, 1));
    print(setbit(b, 2));
    print(setbit(b, 3));
    print(setbit(b, 8));
    printf("\n");

    printf("Clear bit %d\n", b);
    printf("B in bin: \n");
    print(b);
    print(clearbit(b, 1));
    print(clearbit(b, 2));
    print(clearbit(b, 3));
    print(clearbit(b, 4));
    printf("\n");

    print(2147483648);
    print(2147483648 >> 1);
    print(1);
    print(1 << 1);
}
