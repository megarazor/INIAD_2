#include <stdio.h>
#include <stdlib.h>

typedef struct num {
  struct num *next;
  long n;
} num_t;

int main() {
  int n = 20;
  num_t *list = NULL;
  for (int i = 0; i < n; i++)  {
    long r = random();
    num_t *cur= malloc(sizeof(*cur));
    cur->n= r;
    cur->next= list;
    list= cur;
  }
  long curr_min= list->n, curr_max= list->n;
  for (num_t* p= list; p!= NULL; p= p->next) {
      printf("%ld ", p->n);
      if (p->n > curr_max) {
          curr_max= p->n;
      }
      else if (p->n < curr_min) {
          curr_min= p->n;
      }
  }
  printf("\n");
  printf("max: %ld\nmin: %ld\n", curr_max, curr_min);
  printf("diff %ld\n", curr_max - curr_min);
}
