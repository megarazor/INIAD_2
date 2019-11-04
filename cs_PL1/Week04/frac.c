#include "frac.h"
#include <stdio.h>

int abs(int n) {
    if (n>= 0)
        return n;
    return n*-1;
}

int greatestCommonDivisor(int a, int b) {
    if (a==0)
        return abs(b);
    if (b==0)
        return abs(a);
    int res= 0;
    for (int i= 1; i<=a; i++) {
        if ((a%i==0) && (b%i==0))
            if (i> res)
                res= i;
    }
    return res;
}

struct fraction add(struct fraction a, struct fraction b) {
    struct fraction res;
    res.numer= a.numer*b.denom + b.numer*a.denom;
    res.denom= a.denom* b.denom;
    return reduce(res);
}

struct fraction subs(struct fraction a, struct fraction b) {
    struct fraction res;
    res.numer= a.numer*b.denom - b.numer*a.denom;
    res.denom= a.denom* b.denom;
    return reduce(res);
}

struct fraction mul(struct fraction a, struct fraction b) {
    struct fraction res;
    res.numer= a.numer * b.numer;
    res.denom= a.denom * b.denom;
    return reduce(res);
}

struct fraction div(struct fraction a, struct fraction b) {
    struct fraction res;
    res.numer= a.numer * b.denom;
    res.denom= a.denom * b.numer;
    return reduce(res);
}

void print(struct fraction a) {
    printf("%d / %d", a.numer, a.denom);
}

struct fraction reduce(struct fraction f) {
    int g= greatestCommonDivisor(f.denom, f.numer);
    if ((g!=0) && (g!=1)) {
        struct fraction res= {.numer= f.numer/g, .denom= f.denom/g};
        return res;
    }
    return f;
}
