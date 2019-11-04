#include <stdio.h>

double i_tri_mass(int width, int height){
  return (double)0.5*width*height;
}

int main(void){
  printf("%lf\n", i_tri_mass(1,3));
}
