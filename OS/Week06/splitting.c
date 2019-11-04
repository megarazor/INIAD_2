#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

        // Splitting cmd into two commands, seperated by '>'
        char *cmd1[ARG_SIZE], *cmd2[ARG_SIZE];
        i= 0;
        int local_i= 0;
        while(strcmp(cmd[i], ">") != 0){
            cmd1[local_i]= cmd[i];
            local_i++;
            i++;
        }
        i++;
        local_i= 0;
        while(cmd[i] != NULL){
            cmd2[local_i]= cmd[i];
            i++;
            local_i++;
        }
        cmd2[local_i]= NULL;
        
        // // Test printing
        // int j= 0;
        // while(cmd1[j] != NULL){
        //     printf("%s ", cmd[j++]);
        // }
        // printf("\n");
        // j= 0;
        // while(cmd2[j] != NULL){
        //     printf("%s ", cmd2[j++]);
        // }
        // printf("\n");

        // Handling pipes
        int pipefd[2];
        if(pipe(pipefd) != 0){
            fprintf(stderr, "pipe(2) failed.\n");
            goto ERROR;
        }

        // Handling parallel processes
        int pid= fork();
        if (pid < 0){
            fprintf(stderr, "ERROR: fork() failed.\n");
            goto ERROR;
        }
        else if (pid > 0){
            // Parent
            close(pipefd[0]);
            close(STDOUT_FILENO);
            dup2(pipefd[1], STDOUT_FILENO); // Use pipefd[1] as stdout

            int n= execvp(cmd1[0], cmd2);
            if (n != 0){
                printf("execvp(3) returns %d.\nERROR: Can't run the command.\n", n);
            }
            int status;
            waitpid(pid, &status, 0);            
        }
        else{
            // Child
            close(pipefd[1]);

            close(STDIN_FILENO);
            dup2(pipefd[0], STDIN_FILENO);
            int n= execvp(cmd2[0], cmd2);
            if (n != 0){
                printf("execvp(3) returns %d.\nERROR: Can't run the command.\n", n);
            }
            return -1;
        }



        
    }
    return 0;
ERROR:
    return -1;
}
