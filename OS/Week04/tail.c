#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 1000

int main (int argc, char* argv[]){
    if (argc!=1)
        return -1;
    char s1[BUF]; // ストリングを4つ作る
    char s2[BUF];
    char s3[BUF];
    char s4[BUF];
    s1[0]= '\0'; // 空っぽのストリングにする。'\0'はストリングの終わりのキャラクター
    s2[0]= '\0';
    s3[0]= '\0';
    s4[0]= '\0';
    while (fgets(s4, BUF, stdin) != NULL){ // 新しい行をs4に入れる。NULLの場合はもう全部読んだ。
        strcpy(s1, s2);
        strcpy(s2, s3);
        strcpy(s3, s4);
    }

    printf("%s%s%s", s1, s2, s3);
    return 0;
}
