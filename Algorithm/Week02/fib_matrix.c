#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Arow 2
#define Acol 2
#define Brow 2
#define Bcol 1

long unsigned int A[Arow*Acol]; 
long unsigned int B[Brow*Bcol]; 
long unsigned int C[Arow*Bcol]; 

void printmat(long unsigned int A[], int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%lu ", A[i + n*j]);
        }
        printf("\n");
    }
    printf("\n");
}

void multmatAB(){
    for (int i = 0; i < Arow; i++ ){
        for (int j = 0; j < Bcol; j++ ){
            for (int k = 0; k < Brow; k++ ){
                C[i+ Arow*j]+= A[i + Arow*k] * B[k + Brow*j];
            }
        }
    }
}

void set0(long unsigned int A[], int n, int m){
    for (int i= 0; i < n; i++){
        for (int j= 0; j< m; j++){
            A[i + n*j]= 0;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2)
        return -1;
    int n = atoi(argv[1]);
    if (n == 0){
        printf("fib(0)= 0\n");
    }
    
    A[0]= 1; // A matrix: 1 1
    A[1]= 1; //           1 0      
    A[2]= 1;
    A[3]= 0;

    B[0]= 1; // B matrix:  1
    B[1]= 0; //            0

    for (int i= 0; i < n; i++){
        multmatAB();
        memcpy(B, C, sizeof(C));
        set0(C, 2, 1);
    }
    printf("fib(%d)= %lu\n", n, B[1]);

    return 0;
}
