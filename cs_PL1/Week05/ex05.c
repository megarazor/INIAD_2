#include <stdio.h>
#include <stdbool.h>

bool isLetterorNumber(char c) {
    if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
        return true;
    return false;
}

void toggleBool(bool *b){
    if (*b) {
        *b= false;
        return;
    }
    *b= true;    
}

int wordCount(char* txt, int n){
    int word_count= 0;
    bool in_word= false;
    for (int i= 0; i < n; i++){
        if (isLetterorNumber(txt[i])) {
            if (!in_word) {
                toggleBool(&in_word);
                word_count++;
            }
        }
        else {
            if (in_word)
                toggleBool(&in_word);
        }
    }
    return word_count;
}
int main(void){
    char txt[10000];
    int n= fread(txt, sizeof(char), 10000, stdin);
    printf("Word count: %d\n", wordCount(txt, n));
}
