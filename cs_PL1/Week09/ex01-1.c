#include <stdio.h>

double d_tri_mass(double width, double height){
  return 0.5*width*height;
}

int main(void){
  printf("%lf\n", d_tri_mass(2.5,1.5));
}
