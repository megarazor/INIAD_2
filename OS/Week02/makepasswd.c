#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unwanted(char c){
    if (c>='0' && c<='9')
        return 0;
    if (c>='a' && c<='z')
        return 0;
    if (c>='A' && c<='Z')
        return 0;
    return 1;
}

int main (void){
    FILE *fin= fopen("/dev/random", "r");
    char rand[100];
    char res[101];
    if(fread(rand, sizeof(rand), 1, fin)){
        //printf("%s\n", rand);
        int res_cnt= 0;
        for (int i= 0; i<strlen(rand); i++){
            if (!unwanted(rand[i])){
                res[res_cnt++]= rand[i];
            }
        }
        res[res_cnt]= '\0';
        //printf("-------------\n");
        printf("%s\n", res);
        return 0;
    }
    return -1;
}
