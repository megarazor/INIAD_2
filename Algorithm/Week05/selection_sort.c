/* selection_sort.c */

#include "sort.h"
#include <stdio.h>

void sort(int *list, int length) {
    for (int p= 0; p < length - 1; p++){
        printf("%d, ", list[p]);
    }
    printf("%d\n", list[length - 1]);
    for(int i = 0; i < length; i++) {
        int min_index = i;
        for(int j = i + 1; j < length; j++) {
            if(list[j] < list[min_index]) {
                min_index = j;
            }
        }
        int tmp = list[i];
        list[i] = list[min_index];
        list[min_index] = tmp;
        for (int p= 0; p < length - 1; p++){
            printf("%d, ", list[p]);
        }
        printf("%d\n", list[length - 1]);
    }
}
