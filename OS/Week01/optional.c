#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char buf[50];
    int cnt= 1;
    int check = 0;
    while(fgets(buf,50,stdin)!=NULL){
        if(check == 0){
            check = 1;
            printf("%d ",cnt);
        }
        if(buf[strlen(buf)-1]=='\n'){
            printf("%s\n",buf);
            ++cnt;
            check = 0;
        }
        else printf("%s",buf);
    }
}
