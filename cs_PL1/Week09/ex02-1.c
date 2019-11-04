#include <stdio.h>
#include <math.h>

double my_exp(double x, int n){
  double ans = 1.0, y = 1.0;

  for (int i = 1; i <= n; i++){
      y= y*(x/i);
      ans= ans + y;

      //printf("%f\n", ans);
  }

  return ans;
}

int main(void){
  int n = 100;
  double x = 20.0;
  printf("my_exp(%lf) = %lf \n", x, my_exp(x, n));
  printf("exp(%lf) = %lf \n", x, exp(x));
}
