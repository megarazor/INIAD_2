#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 1024

char change_cap(char c){
    if (c>= 'A' && c<= 'Z'){
        return c + 32;
    }
    if (c>= 'a' && c<= 'z'){
        return c - 32;
    }
    return '\0';
}

int count(char *str, char c){
    int res= 0;
    char cap_c= change_cap(c);
    //printf("Counting %c and %c\n", c, cap_c);
    for (int i= 0; i< strlen(str); i++){
        if ((str[i]== c) || (str[i]== cap_c))
            res++;
    }
    return res;
}

int main (int argc, char* argv[]){
    if (argc!=1)
        return -1;
    char str[BUF];
    int no[26];
    for (int i= 0; i< 26; i++){
        no[i]= 0;
    }
    while(fgets(str, BUF, stdin)!= NULL){
        for (char cur= 'a'; cur<= 'z'; cur++){
            int n= count(str, cur);
            no[cur - 97]+= n;
        }    
    }
    char blip= 'a';
    for (int i= 0; i< 26; i++){
        if (no[i]!= 0)
            printf("%c: %d\n", blip, no[i]);
        blip++;
    }
    return 0;
}
