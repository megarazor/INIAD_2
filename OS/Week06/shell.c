#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_SIZE 1024
#define ARG_SIZE 64

int main(int argc, char* argv[]){
    if (argc != 1){
        fprintf(stderr, "shell takes no arguments.\n");
        return -1;
    }
    while (1){
        printf("> "); // Shell interface

        // Input command & handling strings
        char buf[BUF_SIZE];
        char *save;
        char *token;
        char *cmd[ARG_SIZE];
        int i= 0;

        // Reading first token
        if(fgets(buf, BUF_SIZE, stdin) == NULL){
            continue;
        }
        token= strtok_r(buf, " ", &save);
        cmd[i++]= token;

        // Reading second and more tokens
        while (token != NULL){
            //printf("Token: %s\n", token);
            token= strtok_r(NULL, " ", &save);
            cmd[i++]= token;
        }
        cmd[i - 2][strlen(cmd[i - 2]) - 1]= '\0';
        cmd[i - 1]= NULL;

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
    }
    return 0;
}
