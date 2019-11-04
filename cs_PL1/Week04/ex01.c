#include<stdio.h>

int Fibonacci(int n) {
    if (n==0)
        return 0;
    if (n==1)
        return 1;
    int next, f1=1, f2=0;
    for (int i= 1; i<n; i++){
        next= f1 + f2;
        f2= f1;
        f1= next;
    }
    return f1;
}

int main(){
    printf("%d\n", Fibonacci(5));
    return 0;
}
