#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_SIZE 1024
#define ARG_SIZE 64

int main(int argc, char* argv[]){
    // Input command & handling strings
    char buf[BUF_SIZE];
    char *save;
    char *cmd[ARG_SIZE];
    int i= 0;

    for (int i= 0; i < argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
    // Token handling
    cmd= malloc(sizeof(char *) * argc);
    for (i= 0; i < argc - 1; i++){
        strcpy(cmd[i], argv[i + 1]);
        printf("%s\n", cmd[i]);
    }
    [i]= NULL;
    for (int j= 0; j < i + 1; j++){
        printf("%s ", token[j]);
    }    
    printf("\n");

    // Handling parallel processes
    pid_t pid= fork();
    if (pid < 0){
        fprintf(stderr, "ERROR: fork() failed.\n");
        return -1;
    }
    else if (pid > 0){
        // Parent            
        int status;
        waitpid(pid, &status, 0);
    }
    else{
        // Child
        int n= execvp(cmd[0], cmd);
        if (n != 0){
            printf("execvp(3) returns %d.\nERROR: Can't run the command.\n", n);        
            return -1;
        }
    }

return 0;
}
