#include <stdio.h>

int main() {
    int array[]= {11, 2, 7, -3, -1};
    int min= array[0], max= array[0];
    for (int i= 1; i<sizeof(array)/sizeof(int); i++) {
        if (array[i]>max)
            max= array[i];
        if (array[i]<min)
            min= array[i];
    }
    printf("Max - Min = %d\n", max-min);
}
