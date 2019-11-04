#include "ex3_3.h"

const int SIZE= 1024;

long my_find(FILE *fp, char v) {
    char val[SIZE];
    int count= 0;
    while (!feof(fp)){
        if(fread(&val, sizeof(char), SIZE, fp)){
            for (int i= 0; i<SIZE; i++) {
                if (val[i]==v){
                    return count;
                }
                else {
                    count++;
                }
            }
        }
    }
    return -1;
}
