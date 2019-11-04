#include <stdio.h>

int main() {
    unsigned short A[9];
    A[0]= 1;
    unsigned short f= 1;
    for (int i= 1; i<9; i++) {
        f= i*f;
        A[i]= f;
    }
    for (int i= 0; i<9; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
