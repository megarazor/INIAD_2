#include "ex2_3.h"
#include <stdlib.h>
#include <string.h>

int insert_from_file(gem_t *after_this, FILE *fp) {
    char val[1];
    int count= 0;
    gem_t *new_gem, *track= after_this;
    while (!feof(fp)){
        if(fread(val, sizeof(char), 1, fp)){
            new_gem= malloc(sizeof(*new_gem));
            new_gem->c= val[0];
            track->_ring_next= new_gem;
            track= track->_ring_next;
            count++;
        }
    }
    new_gem->_ring_next= after_this;
    return count;
}
