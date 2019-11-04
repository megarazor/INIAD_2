#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
int main (void){
    char buf[1000];
    for (int i= 1; fgets(buf) ; i++) {
        printf("%d %s\n", i, buf);
    }
}*/
/*
int main(void){
    char buf[10];
    int same_line= 0;
    int i= 1;
    while (fgets(buf, 10, stdin)!=NULL){
        if (same_line==0){
            printf("%d ", i++);
            same_line= 1;
        }
        printf("%s", buf);
        if (buf[strlen(buf) - 1] == '\n'){
            same_line= 0;
        }
        else{
            same_line= 1;
        }
    }
}
*/

int main(void)
{
    char buf[1000];
    int i = 1;
    while (gets(buf))
    {
        printf("%d %s\n", i, buf);
        i++;
    }
    return 0;
}
