#include <stdio.h>
#include <stdlib.h>

/* int main (void){
    FILE *fin= fopen("/proc/uptime", "r");
    double uptime;
    if(fscanf(fin, "%lf", &uptime)){
        printf("Up for %lf seconds\n", uptime);
        return 0;
    }
    return -1;
} */

/* int main(int argc, char *argv[]){
    char buf[1000];
    FILE *fp = fopen("/proc/uptime", "r");
    fgets(buf, sizeof(buf), fp);
    fclose(fp);
    // printf("%s\n", buf);
    printf("Up for ");
    for (int i = 0; i < 1000; i++){
        if (buf[i] == '\0'){ // end of string
            return -1;
        }
        else if (buf[i]== ' '){ // if reaches space char then stops
            printf(" seconds.\n");
            return 0;
        }
        else{
            printf("%c", buf[i]);
        }
    }
    return -1;
} */


int main (void){
    FILE *fin = fopen("/proc/uptime", "r");
    double time;
    if(fscanf(fin, "%lf", &time)){
        printf("Up for %lf seconds\n", time);
        return 0;
    }
    return 1;
}
