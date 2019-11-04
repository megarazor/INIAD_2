#include <stdio.h>

unsigned int addtwo(unsigned int a){
  return a + 2;
}


unsigned int subtwo(unsigned int a){
  return a - 2;
}

unsigned int mul(unsigned int a, unsigned int(*p)(unsigned int)){
  return a * (*p)(a);
}

int main(void){
  printf("addtwo : %u \n", mul(4, addtwo) );
  printf("subtwo : %u \n", mul(4, subtwo) );
}
