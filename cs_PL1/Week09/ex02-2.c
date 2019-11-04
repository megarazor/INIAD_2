#include <stdio.h>
#include <math.h>

double my_exp_auto(double x){
  double ans = 1.0, y = 1.0;
  int i = 1;
  double lim= pow(2, -52);

  while (1){
      y= y*x/i;
      if (y/ans<lim && -y/ans<lim) {
          break;
      }
      ans= ans + y;
      i++;
  }

  return ans;
}

int main(void){
  double x = -20.0;
	
  printf("my_exp_auto(%lf) = %17.13lf \n", x, my_exp_auto(x));
  printf("exp(%lf) = %17.13lf \n", x, exp(x));
  //printf("%17.30lf \n", pow(2, -52));
}
