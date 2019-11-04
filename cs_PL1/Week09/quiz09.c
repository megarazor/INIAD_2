#include "atnd09.h"
#include <stdlib.h>
#include <string.h>

void gem_insert(gem_t *ring, int i, char *name) {
    if (i<0)
        return;
    gem_t *new_gem= malloc(sizeof(*new_gem));
    strcpy(new_gem->_name, name);
    if (i==0){
        new_gem->_ptr= ring;
        ring= new_gem;
        return;
    }
    gem_t *to_insert= ring;
    for (int j= 0; j<(i-1); j++) {
        to_insert= to_insert->_ptr;
    }
    new_gem->_ptr= to_insert->_ptr;
    to_insert->_ptr= new_gem;
}
