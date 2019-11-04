#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 1000

int main (int argc, char* argv[]){
    if (argc!=2)
        return -1;
    int n= atoi(argv[1]);
    if (n == 0){
        return 0;
    }
    char **lines= malloc(sizeof(sizeof(char)*BUF)*(n + 1));
    for (int i= 0; i < (n + 1); i++){
        lines[i]= malloc(sizeof(char)*BUF);
        lines[i][0]= '\0';
    }
    while (fgets(lines[n], BUF, stdin) != NULL){
        for (int i= 0; i < n; i++){
            strcpy(lines[i], lines[i + 1]);
        }
    }
    for (int i= 0; i < n; i++){
        printf("%s", lines[i]);
    }
    return 0;
}
