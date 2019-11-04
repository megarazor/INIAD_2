#include "ex3_2.h"

node_t *my_at(node_t *top, node_t *end, int i){
    node_t *p= top;
    for (int j= 0; j<i; j++) {
        if (p==end) {
            return p;
        }
        else {
            p= p->next;
        }
    }
    return p;
}
