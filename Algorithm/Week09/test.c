#include <stdio.h>
#include <string.h>

#define TOKEN_SIZE 1024

int main(){
    char str[128]= "( 2  + (( 5  -  3 ) *  2 ))";
    printf("str: %s\n", str);
    char *tokens[TOKEN_SIZE];
    char *token= strtok(str, " \n");
    int i= 0;
    while(token != NULL){
        strcpy(tokens[i++], token);
        token= strtok(str, " \n");
    }
    for (int j= 0; j < i; j++){
        printf("%s ", tokens[j]);
    }
    printf("\n");
    return 0;
}