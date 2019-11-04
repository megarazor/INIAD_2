#include <stdio.h>

#define Arow 3
#define Acol 4
#define Brow 4
#define Bcol 3

double A[Arow*Acol]; 
double B[Brow*Bcol]; 
double C[Arow*Bcol]; 

void printmat(double A[], int n, int m){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      printf("%lf ", A[i + n*j]);
    }
      printf("\n");
  }
}

int main(void){
  for (int i = 0; i < Arow*Acol; i++){
    A[i] = i;
  }
  for (int i = 0; i < Brow*Bcol; i++){
    B[i] = i;
  }

  for (int i = 0; i < Arow; i++ ){
    for (int j = 0; j < Bcol; j++ ){
      for (int k = 0; k < Brow; k++ ){
        C[i+ Arow*j]+= A[i + Arow*k] * B[k + Brow*j];		
      }
    }
  }

  printmat(A, Arow, Acol);
  printmat(B, Brow, Bcol);
  printmat(C, Arow, Bcol);
}
