#include <stdio.h>

unsigned int addtwo(unsigned int a){
  return a + 2;
}


unsigned int subtwo(unsigned int a){
  return a - 2;
}

int main(void){
  unsigned int (*p)(unsigned int);
  p = addtwo;
  printf("addtwo : %u \n", p(4) );

  p = subtwo;
  printf("subtwo : %u \n", p(4) );
}
