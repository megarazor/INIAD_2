#include <stdio.h>

double A[3*3]; // 3*3 matrix
double B[3*3]; // 3*3 matrix
double C[3*3]; // 3*3 matrix

void printmat(double A[], int n, int m){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      printf("%lf ", A[i + 3*j]);
    }
      printf("\n");
  }
}

int main(void){
  for (int i = 0; i < 9; i++){
    A[i] = i;
    B[i] = i;
  }

  for (int i = 0; i < 3; i++ ){
    for (int j = 0; j < 3; j++ ){
      for (int k = 0; k < 3; k++ ){
        C[i+ 3*j]+= A[i + 3*k] * B[k + 3*j];		
      }
    }
  }

  printmat(A, 3, 3);
  printmat(B, 3, 3);
  printmat(C, 3, 3);
}
