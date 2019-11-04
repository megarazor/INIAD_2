#include <stdio.h>
#include <stdlib.h>

int check_swap(int* a, int* b){
    if (*a >= *b){
        return 0;
    }
    int tmp= *a;
    *b= *a;
    *a= tmp;
    return 1;
}

int main(){
    int *a, *b;
    a= malloc(sizeof(int));
    *a= 4;
    b= malloc(sizeof(int));
    *b= 10;
    printf("%d a: %d, b: %d\n", check_swap(a, b), *a, *b);
}
