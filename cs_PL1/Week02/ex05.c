#include <stdio.h>

int main(void){
  int i = 10;
  int *p_i = &i;
  int **pp_i = &p_i;
	
  printf("i: %d\n",i);
  printf("&i: %p\n",&i);
  printf("*p_i: %d\n",*p_i);
  printf("p_i: %p\n",p_i);
  printf("&p_i: %p\n",&p_i);
  printf("**p_i: %d\n",**pp_i);
  printf("*pp_i: %p\n",*pp_i);
  printf("pp_i: %p\n",pp_i);
  printf("&pp_i: %p\n",&pp_i);
}
