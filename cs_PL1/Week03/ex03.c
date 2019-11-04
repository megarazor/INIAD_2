#include<stdio.h>

union crypt{
  short s;
  char c[2];
};

int main(void){
  union crypt A;
  char tmp;
	
  A.s = -12714;
	
  tmp=A.c[0];
  A.c[0]=A.c[1];
  A.c[1]=tmp;
	
  printf("%d\n",A.s);
}
