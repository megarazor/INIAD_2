#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]){
    if (argc<2){
        printf("You need to specify and hour\n");
        return 0;
    }
    int hour= atoi(argv[1]);
    switch (hour){
        case 0 ... 4:
            printf("Good night\n");
            return 0;
        case 5 ... 10:
            printf("Good morning\n");
            return 0;
        case 11 ... 17:
            printf("Hello\n");
            return 0;
        case 18 ... 20:
            printf("Good evening\n");
            return 0;
        case 21 ... 23:
            printf("Good night\n");
            return 0;
        default:
            printf("Wrong hour input\n");
            return 0;
    }
    /*
    if ((hour<0) || (hour>23)){
        printf("Wrong hour\n");
        return 0;
    }
    if ((hour<=4) || (hour>=21)){
        printf("Good night\n");
        return 0;
    }
    if (hour<=10){
        printf("Good morning\n");
        return 0;
    }
    if (hour<=17){
        printf("Hello\n");
        return 0;
    }
    if (hour<=20){
        printf("Good evening\n");
        return 0;
    } */
    return -1;
}
