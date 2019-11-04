#include <stdio.h>
#include <stdlib.h>

struct fraction{
    int numer;
    int denom;
};

int main() {
    struct fraction a= { .numer= 10, .denom= 9}, b= { .numer= 5, .denom= 6};
    struct fraction c= { .numer= a.numer*b.numer, .denom= a.denom*b.denom};
    printf("a= %d/%d, b= %d/%d, c= %d/%d\n", a.numer, a.denom, b.numer, b.denom, c.numer, c.denom);
}
