//#define DEBUG
#include <stdio.h>
#include "cmplx.h" // Previous problems
#include "cmplx.h" // Include cmplx.h again for confirmation

#define CPRINT(a) printf("%lf + i %lf\n", a.real, a.imag);

int main(void){
  cmplx a = {1.0, 2.0};
  cmplx b = {3.0, 4.0};

  cmplx c = add_cmplx(a, b);
  printf("%lf + i %lf\n", c.real, c.imag);

  cmplx d = mul_cmplx(a, b);
  printf("%lf + i %lf\n", d.real, d.imag);
  
  CPRINT(a);
  CPRINT(b);
  CPRINT(c);
}


