/* merge_sort.c */

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void merge(int* list, int *tmp, int start, int mid, int end) {
    int i = start;
    int j = mid + 1;
    int k = start;
    while((i <= mid) && (j <= end)) {
        if(list[i] > list[j]) {
            tmp[k] = list[j];
            j++;
            k++;
        } else {
            tmp[k] = list[i];
            i++;
            k++;
        }
    }

    while(i <= mid) {
        tmp[k] = list[i];
        i++;
        k++;
    }

    while(j <= end) {
        tmp[k] = list[j];
        j++;
        k++;
    }

    for(i = start; i <= end; i++) {
        list[i] = tmp[i];
    }
}

void merge_sort(int* list, int *tmp, int start, int end, int real_start, int real_end) {
    if(start == end) {
        return;
    }

    int mid = (start + end) / 2;
    merge_sort(list, tmp, start, mid, real_start, real_end);
    merge_sort(list, tmp, mid + 1, end, real_start, real_end);
    for(int i = real_start; i < real_end; i++) {
        printf("%d, ", list[i]);
    }
    printf("%d\n", list[real_end]);
    merge(list, tmp, start, mid, end);
}

void sort(int* list, int length) {
    int* tmp = malloc(sizeof(int) * length);
    merge_sort(list, tmp, 0, length - 1, 0, length - 1);
    free(tmp);
}
