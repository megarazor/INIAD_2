#include <stdio.h>

#define BUFFERSIZE 100

int main ()
{
    char c = fgetc(stdin); 
    int i= 0;
    while (c != EOF) { 
        i++;
        if(i == 50){
            break;
        }
        fputc(c, stdout); 
        c = fgetc(stdin); 
        
    }
    printf("Done printing.\n");
}