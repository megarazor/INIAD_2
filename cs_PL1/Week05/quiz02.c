#include "atnd05_2.h"
#include <stdlib.h>

long read_from_file(num_t **pp, FILE *fp) {
    long node_count= 0;
    long value;
    num_t* tail= *pp;
    while(fscanf(fp, "%ld", &value)==1){
        num_t* new_num= malloc(sizeof(*new_num));
        new_num->n= value;
        new_num->next= NULL;
        if (*pp==NULL){
            *pp= new_num;
            tail= new_num;
        }
        else {
            tail->next= new_num;
            tail= tail->next;
        }
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

