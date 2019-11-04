#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]){
    if (argc!=3)
        return -1;
    FILE *fin= fopen(argv[1], "r");
    FILE *fout= fopen(argv[2], "w");
    char buf[10]; 
    while(!feof(fin)){
        int rd= fread(buf, sizeof(buf), 1, fin);
        if (rd){
            fwrite(buf, sizeof(buf), 1, fout);
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;