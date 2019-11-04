#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "atnd15.h"

void node_insert(node_t *top, int i, char *name) {
    if (i<=0) return;
    //printf("%d %s\n", i, name);
    node_t *to_insert= top;
    for (int j= 1; j<i; j++) {
        to_insert= to_insert->_nx;
    }
    node_t *new_node= malloc(sizeof(*new_node));
    strcpy(new_node->_name, name);
    new_node->_nx= to_insert->_nx;
    to_insert->_nx= new_node;
}
