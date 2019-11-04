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

        // Check if the command contains redirect '>' or not
        int redirect= 0, types_i= 0;
        char types[5][2];
        for(int j= 0; j < i - 1; j++){
            if ((strcmp(cmd[j], ">") == 0) || (strcmp(cmd[j], "<") == 0) || (strcmp(cmd[j], ">>") == 0) || (strcmp(cmd[j], "2>&1") == 0)){
                redirect++;
                strcpy(types[types_i++], cmd[j]);
            }
        }

        // Handle parent/child processes
        pid_t pid_grand= fork();
        if (pid_grand < 0){
            fprintf(stderr, "ERROR: fork() failed.\n");
            return -1;
        }
        else if (pid_grand > 0){
            // Parent            
            int status;
            waitpid(pid_grand, &status, 0);
        }
        else{
            // Child
            if (!redirect){
                int n= execvp(cmd[0], cmd);
                if (n != 0){
                    printf("execvp(3) returns %d.\nERROR: Can't run the command.\n", n);
                }
                return -1;
            }
            else {
                if (redirect == 1){
                    // Get file name after redirect symbol
                    char filename[BUF_SIZE];
                    strcpy(filename, cmd[i - 2]);
                    cmd[i - 3]= NULL; // Erase tokens of redirect and "<filename>", leaving pure command
                    cmd[i - 2]= NULL;

                    char buf[BUF_SIZE]; // Prepare buf

                    // Handling pipes
                    int pipefd[2];
                    if(pipe(pipefd) != 0){
                        fprintf(stderr, "pipe(2) failed.\n");
                        goto ERROR;
                    }
                    if ((strcmp(types[0], ">") == 0) || (strcmp(types[0], ">>") == 0)){ // '>' or ">>" case  

                        // Handling parent/child processes
                        pid_t pid= fork();
                        if (pid < 0){
                            fprintf(stderr, "ERROR: fork() failed.\n");
                            goto ERROR;
                        }
                        else if (pid > 0){
                            // Parent
                            close(pipefd[0]);
                            close(STDOUT_FILENO);
                            dup2(pipefd[1], STDOUT_FILENO); // Use pipefd[1] as stdout

                            int n= execvp(cmd[0], cmd);
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
                            FILE *fout;
                            if (strcmp(types[0], ">") == 0)
                                fout= fopen(filename, "w");
                            else
                                fout= fopen(filename, "a");

                            if (fout == NULL){
                                fprintf(stderr, "ERROR: fopen(2) returns NULL. Can't open %s.\n", filename);
                            }
                            
                            while(fgets(buf, BUF_SIZE, stdin) != NULL){
                                fwrite(buf, 1, strlen(buf), fout);
                            }

                            fclose(fout);
                            return 0;
                        }
                    }
                    else if (strcmp(types[0], "<") == 0){
                        // '<' case
                        // Handling parent/child processes;

                        pid_t pid= fork();
                        if (pid < 0){
                            fprintf(stderr, "ERROR: fork() failed.\n");
                            goto ERROR;
                        }
                        else if (pid > 0){
                            // Parent
                            close(pipefd[0]);
                            close(STDOUT_FILENO);
                            dup2(pipefd[1], STDOUT_FILENO); // Use pipefd[1] as stdout

                            FILE *fin= fopen(filename, "r");
                            while(fgets(buf, BUF_SIZE, fin) != NULL){
                                fwrite(buf, 1, strlen(buf), stdout);
                            }
                            fputs("%d", EOF); // End the file. Or else child will stuck in the file 
                            fclose(fin);                    
                            int status;
                            waitpid(pid, &status, 0);    
                            
                        }
                        else{
                            // Child                           
                            close(pipefd[1]);
                            close(STDIN_FILENO);
                            dup2(pipefd[0], STDIN_FILENO); 

                            int n= execvp(cmd[0], cmd);
                            
                            if (n != 0){
                                printf("execvp(3) returns %d.\nERROR: Can't run the command.\n", n);
                                return -1;
                            }                            
                            return 0;
                        }
                    }
                    else if (strcmp(types[0], "2>&1") == 0){
                        printf("Sorry not implemented yet.\n");
                    }
                }
                else {
                    printf("Number of redirects: %d. Sorry, not implemented yet.\n", redirect);
                }
            }        
        }
    }
    return 0;

ERROR:
    return -1;
}
