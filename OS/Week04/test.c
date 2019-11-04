#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 3

int main (){
    int n= 2;
    char **lines= malloc(sizeof(sizeof(char)*BUF)*(n+1));
    for (int i= 0; i < n; i++){
        lines[i]= malloc(sizeof(char)*BUF);
    }
    lines[0][0]= 'A';
    lines[0][1]= 'B';
    lines[0][2]= '\0';
    lines[1][0]= 'C';
    lines[1][1]= 'D';
    lines[1][2]= '\0';
    lines[2]= NULL;
    printf("%s\n%s\n%s\n", lines[0], lines[1], lines[2]);
    return 0;
}
