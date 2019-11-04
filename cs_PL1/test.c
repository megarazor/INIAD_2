#include <stdio.h>
#include <stdlib.h>

int is_digit(char c){
    if (c>='0' && c<='9') {
        return 1;
    }
    return 0;
}

int main(void){
    FILE* fp1 = fopen("Week05/int.i", "r");
    FILE* fp2 = fopen("Week05/int.o", "w");
    int new_n;
    while (!feof(fp1)){
        int scan_result= fscanf(fp1, "%d", &new_n);
        printf("%d ", scan_result);
        if (scan_result!= 1){
            fseek(fp1, 1, SEEK_CUR);
        }
    }
    /*while (!feof(fp1)){
        fread(&new_n, sizeof(int), 1, fp1);
        printf("%d ", new_n);
    }*/
    printf("\n");
    fclose(fp1);
    fclose(fp2);
}
