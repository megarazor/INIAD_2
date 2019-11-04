/* insertion_sort.c */

#include "sort.h"
#include <stdio.h>

void sort(int *list, int length) {
    for (int p= 0; p < length - 1; p++){
        printf("%d, ", list[p]);
    }
    printf("%d\n", list[length - 1]);
    for(int i = 1; i < length; i++) {
        int target = list[i];
        int j;
        for(j = i - 1; j >= 0; j--) {
            if(target < list[j]) {
                list[j + 1] = list[j];
            } else {
                break;
            }
        }
        list[j + 1] = target;
        for (int p= 0; p < length - 1; p++){
            printf("%d, ", list[p]);
        }
        printf("%d\n", list[length - 1]);
    }
}
