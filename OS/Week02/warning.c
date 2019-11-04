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
    
}
