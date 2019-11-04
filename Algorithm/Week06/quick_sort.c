/* quick_sort.c */

#include "sort.h"

int find_pivot(T *list, int start, int end, T *pivot, Comparefn compare) {
    T first = list[start];
    for(int i = start + 1; i <= end; i++) {
        if(compare(list[i], first) > 0) {
            *pivot = list[i];
            return 1;
        } else if(compare(first, list[i]) > 0) {
            *pivot = first;
            return 1;
        }
    }
    return 0;
}

int partition(T *list, int left, int right, T pivot, Comparefn compare) {
    for(;;) {
        while(compare(list[left], pivot) < 0) {
            left++;
        }
        while(compare(list[right], pivot) >= 0) {
            right--;
        }
        if(left >= right) {
            break;
        }
        
        T tmp = list[left];
        list[left] = list[right];
        list[right] = tmp;
        left++;
        right--;
    }

    return left;
}

void quick_sort(T *list, int start, int end, Comparefn compare) {
    T pivot;
    if(! find_pivot(list, start, end, &pivot, compare)) {
        return;
    }

    int p = partition(list, start, end, pivot, compare);

    quick_sort(list, start, p - 1, compare);
    quick_sort(list, p, end, compare);
}

void sort(T* list, int length, Comparefn compare) {
    quick_sort(list, 0, length - 1, compare);
}
