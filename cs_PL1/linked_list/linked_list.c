#include "linked_list.h"
#include <stdlib.h>

num_t *push_head(num_t **s, long v) {
    num_t *new_num= malloc(sizeof(*new_num));
    new_num->n= v;
    new_num->next= *s;
    *s= new_num;
    return new_num;
}

num_t *pop_head(num_t **s) {
    if (*s==NULL) return NULL;
    num_t *to_pop= *s;
    *s= (*s)->next;
    return to_pop;
}

num_t *push_tail(num_t **s, long v) {
    if (*s==NULL) {
        num_t *new_num= malloc(sizeof(*new_num));
        new_num->n= v;
        new_num->next= NULL;
        *s= new_num;
        return new_num;
    }
    num_t *cur= *s;
    while (cur->next!= NULL) {
        cur= cur->next;
    }
    num_t *new_num= malloc(sizeof(*new_num));
    new_num->n= v;
    new_num->next= NULL;
    cur->next= new_num;
    return new_num;
}

num_t *pop_tail(num_t **s) {
    if (*s==NULL) return NULL;
    if ((*s)->next==NULL){
        num_t *to_pop= *s;
        *s= NULL;
        return to_pop;
    }
    num_t *cur= *s;
    while(cur->next->next!= NULL) {
        cur= cur->next;
    }
    num_t *to_pop= cur->next;
    cur->next= NULL;
    return to_pop;
}

long read_from_file(num_t **pp, FILE *fp) {
    long node_count= 0;
    long new_n;
    while(fscanf(fp, "%ld", &new_n)==1){
        push_tail(pp, new_n);
        node_count++;
    }
    return node_count;
}

long write_to_file(num_t *list, FILE *fp) {
    long node_count= 0;
    num_t* cur= list;
    while (cur!=NULL) {
        fprintf (fp, "%ld ", cur->n);
        node_count++;
        cur= cur->next;
    }
    return node_count;
}

void print_list(num_t* list) {
    num_t* cur= list;
    while (cur!= NULL) {
        printf("%ld ", cur->n);
        cur= cur->next;
    }
    printf("\n");
}
