#include <stdio.h>

extern int sigma(int n, int m);

int main(){
    int n= 5;
    int m= 10;
    printf("sigma(%d, %d) = %d\n", n, m, sigma(n, m));
    return 0;
}
