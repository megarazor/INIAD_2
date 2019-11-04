#include "atnd13.h"

long count_64m(FILE *fp) {
    long count= 0;
    unsigned char val[1024];
    while (!feof(fp)){
        int n= fread(val, 1, sizeof val, fp);
        if (n>0) {
            for (int i= 0; i<n; i++) {
                if (val[i]%64==0)
                        count++;
                }
        }
    }
    return count;
}
