#include "atnd08.h"
#include <stdlib.h>

void gem_unlink(gem_t *ring, gem_t *target) {
    gem_t *cur= ring;
    while (cur->ring_next!=target) {
        cur= cur->ring_next;
    }
    cur->ring_next= target->ring_next;
    target->ring_next= NULL;
}
