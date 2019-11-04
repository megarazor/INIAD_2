#include <stdio.h>
#include <stdlib.h>

typedef struct hoge{
  int fuga;
} HOGE;

/* int main(void){
  HOGE *ppiyo;
  ppiyo= malloc(sizeof(*ppiyo));
  ppiyo->fuga= 3;
}*/

typedef struct foo{
  HOGE *ppiyo;
} FOO;

int main(void){
  FOO bar;
  bar.ppiyo= malloc(sizeof(*bar.ppiyo));
  bar.ppiyo->fuga= 3;
}
