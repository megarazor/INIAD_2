#include "atnd04.h"
#include <stdlib.h>


num_t *push(num_t **s, long v){
 num_t *new_node = malloc(sizeof *new_node);
 new_node->n = v;
 new_node->next = *s;
 *s = new_node;
 return new_node;
}

num_t *pop(num_t **s){
 if (NULL != *s){
 num_t *removed_top = *s;
 *s = removed_top->next;
 return removed_top;
 } else {
 return NULL;
 }
}
