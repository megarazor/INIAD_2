#include "atnd13.h"

long count_64m(FILE *fp) {
    long count= 0;
    unsigned char val;
    while (!feof(fp)){
        if(fread(&val, sizeof(unsigned char), 1, fp)){
            if (val%64==0)
                count++;
        }
    }
    return count;
}
