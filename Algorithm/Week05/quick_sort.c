/* quick_sort.c */

#include "sort.h"
#include <stdio.h>

int find_pivot(int *list, int start, int end, int *pivot) {
    int first = list[start];
    for(int i = start + 1; i <= end; i++) {
        if(first < list[i]) {
            *pivot = list[i];
            return 1;
        } else if(first > list[i]) {
            *pivot = first;
            return 1;
        }
    }
    return 0;
}

int partition(int *list, int left, int right, int pivot) {
    for(;;) {
        while(list[left] < pivot) {
            left++;
        }
        while(list[right] >= pivot) {
            right--;
        }
        if(left >= right) {
            break;
        }
        
        int tmp = list[left];
        list[left] = list[right];
        list[right] = tmp;
        left++;
        right--;
    }

    return left;
}

void quick_sort(int *list, int start, int end, int l_start, int l_end) {
    int pivot;
    if(! find_pivot(list, start, end, &pivot)) {
        return;
    }
    for (int i= l_start; i < l_end; i++){
        printf("%d, ", list[i]);
    }
    printf("%d\n", list[l_end]);
    int p = partition(list, start, end, pivot);
    
    quick_sort(list, start, p - 1, l_start, l_end);
    quick_sort(list, p, end, l_start, l_end);
}

void sort(int *list, int length) {
    quick_sort(list, 0, length - 1, 0, length - 1);
    
    for (int p= 0; p < length - 1; p++){
        printf("%d, ", list[p]);
    }
    printf("%d\n", list[length - 1]);
}
