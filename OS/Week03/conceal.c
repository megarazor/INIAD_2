#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 10

void conceal(char* str){
    for (int i= 0; i< strlen(str); i++){
        if (str[i]>= '0' && str[i]<= '9'){
            str[i]= '*';
        }
    }
}

int main (int argc, char* argv[]){
    if (argc!=1)
        return -1;
    char str[BUF];
    while(fgets(str, BUF, stdin)!= NULL){
        conceal(str);
        printf("%s", str);
    }
    printf("\n");
    return 0;
}
