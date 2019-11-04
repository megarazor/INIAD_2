#include "ex1_5.h"
#include <stdlib.h>

int count_elms(unsigned char v, FILE *fp) {
    unsigned char ch[1];
    int count= 0;
    while (!feof(fp)){
        fread(ch, sizeof(char), 1, fp);
        if (ch[0]== v)
            count++;
    }
    return count;
}
