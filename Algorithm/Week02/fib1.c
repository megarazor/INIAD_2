/* fib1.c */

#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
    if(n <= 0) {
        return 0;
    }
    if(n == 1) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        return -1;
    }
    int n = atoi(argv[1]);
    int result = fib(n);
    printf("fib(%d)=%d\n", n, result);

    return 0;
}
