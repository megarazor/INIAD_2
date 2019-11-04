/* fact1.c */

#include <stdio.h>
#include <stdlib.h>

int fact(int n) {
    int result = 1;
    for(int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        return -1;
    }
    int n = atoi(argv[1]);
    int result = fact(n);
    printf("fact(%d)=%d\n", n, result);
    return 0;
}