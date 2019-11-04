#include "ex1_3.h"
#include <stdlib.h>
#include <string.h>

int count_gem(gem_t *ring, char *name) {
    int count= 0;
    if (strcmp(ring->name, name)== 0){
        count++;  
    }
    gem_t* cur= ring->ring_next;
    while (cur!= ring) {
        if (strcmp(cur->name, name)== 0){
            count++;
        }
        cur= cur->ring_next;
    }
    return count;
}
