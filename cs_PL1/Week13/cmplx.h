#ifndef INCLUDE_CMPLX_H
#define INCLUDE_CMPLX_H
#include <stdio.h>

typedef struct cmplx {
    double real;
    double imag;
} cmplx;

cmplx add_cmplx(cmplx a, cmplx b){
    cmplx res;
    res.imag= a.imag + b.imag;
    res.real= a.real + b.real;

    #ifdef DEBUG
    printf("%lf + i %lf\n", res.real, res.imag);
    #endif

    return res;
}

cmplx mul_cmplx(cmplx a, cmplx b){
    cmplx res;
    res.real= a.real*b.real - a.imag*b.imag;
    res.imag= a.real*b.imag + a.imag*b.real;

    #ifdef DEBUG
    printf("%lf + i %lf\n", res.real, res.imag);
    #endif

    return res;
}

#endif
