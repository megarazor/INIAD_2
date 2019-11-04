/* fib2.c */

#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
    if(n <= 0) {
        return 0;
    }
    if(n == 1) {
        return 1;
    }
    int f_2 = 0;
    int f_1 = 1;
    int f = 1;
    for(int i = 2; i <= n; i++) {
        f = f_1 + f_2;
        f_2 = f_1;
        f_1 = f;
    }
    return f;
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
