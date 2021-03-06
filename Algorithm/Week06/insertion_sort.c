/* insertion_sort.c */

#include "sort.h"

void sort(T* list, int length, Comparefn compare) {
    for(int i = 1; i < length; i++) {
        T target = list[i];
        int j;
        for(j = i - 1; j >= 0; j--) {
            if(compare(list[j], target) > 0) {
                list[j + 1] = list[j];
            } else {
                break;
            }
        }
        list[j + 1] = target;
    }
}