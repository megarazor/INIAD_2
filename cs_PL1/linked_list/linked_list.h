#include <stdio.h>

typedef struct num
{
  struct num *next;
  long n;
} num_t;

num_t *pop_head(num_t **s);
num_t *push_head(num_t **s, long v);
num_t *pop_tail(num_t **s);
num_t *push_tail(num_t **s, long v);
long read_from_file(num_t **pp, FILE *fp);
long write_to_file(num_t *list, FILE *fp);
void print_list(num_t *list);
