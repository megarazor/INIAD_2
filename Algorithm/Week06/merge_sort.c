/* merge_sort.c */

#include <stdlib.h>
#include "sort.h"

void merge(T* list, T *tmp, int start, int mid, int end, Comparefn compare) {
    int i = start;
    int j = mid + 1;
    int k = start;
    while((i <= mid) && (j <= end)) {
        if(compare(list[i], list[j]) > 0) {
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

void merge_sort(T* list, T *tmp, int start, int end, Comparefn compare) {
    if(start == end) {
        return;
    }

    int mid = (start + end) / 2;
    merge_sort(list, tmp, start, mid, compare);
    merge_sort(list, tmp, mid + 1, end, compare);

    merge(list, tmp, start, mid, end, compare);
}

void sort(T* list, int length, Comparefn compare) {
    T* tmp = (T*)malloc(sizeof(T*) * length);
    merge_sort(list, tmp, 0, length - 1, compare);
    free(tmp);
}