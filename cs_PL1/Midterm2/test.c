#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileA.c"
#include "fileB.c"

int main() {
    funcA();
    printf("%d\n",funcB());
}
