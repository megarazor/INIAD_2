/* gcd.c */

#include <stdio.h>

unsigned int gcd(unsigned int a, unsigned int b) {
    if ((a==0) || (b==0)) return 0;
    if (a<b) {
        unsigned int tmp= a;
        a= b;
        b= tmp;
    }
    unsigned int r= a%b;;
    while (r!=0){
        a= b;
        b= r;
        r= a%b;
    }
    return b;
}

int main(int argc, char* argv[]) {
    unsigned int a, b;
    printf("Input a:");
    scanf("%d", &a);
    printf("Input b:");
    scanf("%d", &b);

    printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
    
    return 0;
}
