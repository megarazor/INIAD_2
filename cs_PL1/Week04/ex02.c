#include <stdio.h>
#include "frac.h"

int main() {
    struct fraction a= {3, 4}, b= {-6, 1}, c= {2, 13};
    print(a);
    printf(" + ");
    print(b);
    printf(" = ");
    print(add(a, b));
    printf("\n");

    print(b);
    printf(" - ");
    print(c);
    printf(" = ");
    print(subs(b, c));
    printf("\n");

    print(a);
    printf(" * ");
    print(c);
    printf(" = ");
    print(mul(a, c));
    printf("\n");

    print(b);
    printf(" / ");
    print(c);
    printf(" = ");
    print(div(b, c));
    printf("\n");

    return 0;
}
