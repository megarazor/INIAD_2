/* radix_sort.c */

#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

void sort(int *list, int length) {
    int* work = (int *)malloc(sizeof(int) * length);
    int place = 1;

    int max = 0;
    for(int i = 0; i < length; i++) {
        if(list[i] > max) {
            max = list[i];
        }
    }

    for (int p= 0; p < length - 1; p++){
        printf("%d, ", list[p]);
    }
    printf("%d\n", list[length - 1]);
    
    while(place < max) {
        int n = 0;
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < length; j++) {
                int digit = (list[j] / place) % 10;
                if(digit == i) {
                    work[n] = list[j];
                    n++;
                }
            }
        }

        for(int i = 0; i < length; i++) {
            list[i] = work[i];
            if (i != length - 1){
                printf("%d, ", list[i]);
            }
            else{
                printf("%d\n", list[i]);
            }
        }

        place *= 10;
    }

    free(work);
}
