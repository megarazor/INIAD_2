#include <stdio.h>

int fibonacci(int n) {
    if (n==0)
        return 0;
    int next, f1= 0, f2= 1;
    for (int i= 0; i<n; i++) {
        next= f1+f2;
        f1= f2;
        f2= next;
    }
    return f1;
}
int main() {
    int n= 10;
    printf("%d\n", fibonacci(n));
    /*for (int i= 0; i<n; i++) {
        printf("%d ", fibonacci(i));
    } */
}
