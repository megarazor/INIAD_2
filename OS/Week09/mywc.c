#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main (int argc, char* argv[]){
    if (argc != 2){
        goto error_var;
    }
    
    int fin= open(argv[1], O_RDONLY);
    if (fin == NULL){
        goto error_fin;
    }

    char buf[BUFSIZE];
    int word_cnt= 0, newl_cnt= 0, char_cnt= 0; 
    int in_word= 0, r;
    while(1){
        r= read(fin, buf, sizeof(buf));
        if (r == 0){
            if (in_word)
                word_cnt++;
            break;
        } 
        else if (r == -1){
            goto error_read;
        }
        // printf("%s\n", buf);
        
        int length= r;
        for (int i= 0; i < length; i++){
            if (buf[i] == '\n'){
                newl_cnt++;
            }
            else if (buf[i] == EOF){
                break;
            }
            if ((buf[i] != ' ') && (buf[i] != '\n')){
                if (in_word == 0)
                    in_word= 1;
            }
            else{
                if (in_word == 1){
                    word_cnt++;
                    in_word= 0;
                }
            }
            char_cnt++;
        }
    }
    printf("%d %d %ld %s\n", newl_cnt, word_cnt, char_cnt*sizeof(char), argv[1]);
    close(fin);
    return 0;
error_var:
    fprintf(stderr, "mywc usage: mywc <filename>\n");
    return -1;
error_fin:
    fprintf(stderr, "ERROR: Can't open file %s\n", argv[1]);
    return -1;
error_read:
    fprintf(stderr, "ERROR: Failed while reading %s\n", argv[1]);
    return -1;
}
