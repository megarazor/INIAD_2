#include <stdio.h>

int main() {
    FILE *out_fp= fopen("text.txt", "w");
    if (out_fp==NULL)
        perror("");
    char txt[24]= "I am a student at INIAD!";
    fwrite(txt, 1, sizeof(txt), out_fp);
    fclose(out_fp);
}

