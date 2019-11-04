#include <stdio.h>

void halfadder(int a, int b, int *r, int *c) {
    if (a==0){
        if (b==0) {
            *r= 0;
            *c= 0;
        }
        else {
            *r= 1;
            *c= 0;
        }
    }
    else {
        if (b==0){
            *r= 1;
            *c= 0;
        }
        else {
            *r= 1;
            *c= 1;
        }
    }
}

void main(){
    int a=1, b=1, *c, *d;
    halfadder(a, b, c, d);
    printf("%d, %d\n", *c, *d);
}
