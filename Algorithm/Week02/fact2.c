/* fact2.c */

#include <stdio.h>
#include <stdlib.h>

int fact(int n) {
    if(n <= 1) {
        return 1;
    }
    return n * fact(n - 1);
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
