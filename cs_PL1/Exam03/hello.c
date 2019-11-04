#include <stdio.h>
#include <stdlib.h>

struct X{
  int val1;
  int val2;
};

void print(struct X n){
  printf("%p %d %d\n", &n, n.val1, n.val2);
}

int main() {
  print((struct X){12, 1});
  struct X n= {13, 21};
  print(n);
}
