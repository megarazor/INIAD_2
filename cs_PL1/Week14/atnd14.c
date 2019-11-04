#include "atnd14.h"
#include <stdlib.h>

node_t *list_64m(FILE *fp) {
    node_t* new_node;
    node_t *back;
    node_t *first;
    unsigned char val[1024];
    unsigned char first_data[1];
    first_data[0]= 1;

    while ((first_data[0]%64!=0) && (!feof(fp))) {
        int n= fread(first_data, sizeof(unsigned char), 1, fp);
        if (n>0) {
            if (first_data[0]%64==0){
                first= malloc(sizeof(*first));
                first->value= first_data[0];
                first->next= NULL;
                back= first;
            }
        }
    }

    while (!feof(fp)){
        int n= fread(val, 1, sizeof val, fp);
        if (n>0) {
                for (int i= 0; i<n; i++) {
                    if (val[i]%64==0) {
                        new_node= malloc(sizeof(*new_node));
                        new_node->value= val[i];
                        back->next= new_node;
                        back= back->next;
                    }
                }
        }
    }
    new_node->next= NULL;
    return first;
}
