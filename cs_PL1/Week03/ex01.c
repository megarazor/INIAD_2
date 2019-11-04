#include <stdio.h>
#include <stdlib.h>

int main() {
    int n= 9;
    int *F= malloc(sizeof(F[0])*n);
    int f1= 0, f2= 1;
    F[0]= 0;
    for (int i=1; i<n; i++) {
        F[i]= f1 + f2;
        f2= f1;
        f1= F[i];
    }
    for (int i=0; i<n; i++) {
        printf("%d ", F[i]);
    }
    printf("\n");
    free(F);
}
