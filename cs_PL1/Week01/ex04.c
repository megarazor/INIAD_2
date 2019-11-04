#include<stdio.h>

int fib(int n) {
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
    int n= -10;
    if (n>=0) {
        int res= fib(n);
        printf("%d\n", res);
    }
    else
        printf("Error: n<0\n");
    return 0;
}
