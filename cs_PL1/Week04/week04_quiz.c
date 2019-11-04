#include "atnd04.h"
#include <stdio.h>
#include <stdlib.h>

num_t *push(num_t **s, long v) {
    num_t *new_num= malloc(sizeof(*new_num));
    new_num->n= v;
    new_num->next= *s;
    *s= new_num;
    return new_num;
}

num_t *pop(num_t **s) {
    if (*s==NULL) return NULL;
    num_t *to_pop= *s;
    *s= (*s)->next;
    return to_pop;
}

