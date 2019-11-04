#include "atnd10.h"
#include <stdlib.h>
#include <string.h>

gem_t *create_ring_from_file(FILE *fp) {
    char value;
    gem_t* list= NULL, *cur= NULL;
    while(!feof(fp)) {
        int n= fread(&value, sizeof(char), 1, fp);
        if (n>0) {
            gem_t* new_gem= malloc(sizeof(*new_gem));
            new_gem->value= value;
            new_gem->_nxt= NULL;
            if (list==NULL){
                list= new_gem;
                cur= list;
            }
            else {
                cur->_nxt= new_gem;
                cur= new_gem;
            }
        }
    }
    cur->_nxt= list;
    return list;
}
