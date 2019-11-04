#include "cmplx.h"

#include <stdio.h>

#define Arow 3
#define Acol 4
#define Brow 4
#define Bcol 3

cmplx A[Arow*Acol]; 
cmplx B[Brow*Bcol]; 
cmplx C[Arow*Bcol]; 

void printmat(cmplx A[], int n, int m){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
        printf("%lf + %lf*i  ", A[i + n*j].real, A[i + n*j].imag);
    }
      printf("\n");
  }
}

int main(void){
  for (int i = 0; i < Arow*Acol; i++){
    A[i].real = i;
    A[i].imag = i + 1;
  }
  for (int i = 0; i < Brow*Bcol; i++){
    B[i].real = i;
    B[i].imag = i + 1;
  }

  for (int i = 0; i < Arow; i++ ){
    for (int j = 0; j < Bcol; j++ ){
      for (int k = 0; k < Brow; k++ ){	
        C[i+ Arow*j]= add_cmplx(C[i+ Arow*j], mul_cmplx(A[i + Arow*k], B[k + Brow*j])) ;
      }
    }
  }

  printmat(A, Arow, Acol);
  printf("\n");
  printmat(B, Brow, Bcol);
  printf("\n");
  printmat(C, Arow, Bcol);
}
