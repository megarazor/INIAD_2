#include "atnd14.h"
#include <stdlib.h>

node_t *list_64m(FILE *fp) {
    node_t* new_node;
    node_t *back;
    node_t *first;
    unsigned char val[1024];
    int first_time= 1;

    while (!feof(fp)){
        int n= fread(val, 1, sizeof val, fp);
        if (n>0) {
            for (int i= 0; i<n; i++) {
                if (val[i]%64==0) {
                    if (first_time!= 1){
                        new_node= malloc(sizeof(*new_node));
                        new_node->value= val[i];
                        back->next= new_node;
                        back= back->next;
                    }
                    else {
                        first= malloc(sizeof(*new_node));
                        first->value= val[i];
                        back= first;
                        first_time= 0;
                    }
                }
            }
        }
    }
    new_node->next= NULL;
    return first;
}
