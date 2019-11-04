#include <stdio.h>
int main(void) {
    int i=1;
    int *p_i;
    p_i = &i;
    printf("%p\n",p_i);
    printf("%d\n",*p_i);
}
