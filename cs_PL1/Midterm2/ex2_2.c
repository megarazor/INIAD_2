#include "ex2_2.h"

int count_m10(gem_t *first, gem_t *end_mark){
    int count= 0;
    for (gem_t *cur= first; cur!=end_mark; cur= cur->_next_gem) {
        if (cur->value%10 == 0) {
            count++;
        }
    }
    return count;
}
