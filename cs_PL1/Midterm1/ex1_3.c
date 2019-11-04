#include "ex1_3.h"
#include <stdlib.h>
#include <string.h>

gem_t *make_ring3(char *gem0, char *gem1, char *gem2) {
    gem_t *g0= malloc(sizeof(*g0));
    strcpy(g0->name, gem0);
    gem_t *g1= malloc(sizeof(*g1));
    strcpy(g1->name, gem1);
    gem_t *g2= malloc(sizeof(*g2));
    strcpy(g2->name, gem2);
    g0->ring_next= g1;
    g1->ring_next= g2;
    g2->ring_next= g0;
    return g0;
}