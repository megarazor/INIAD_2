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
        int pid_grand= fork();
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
                }
                else if (redirect == 2){
                    if (((strcmp(types[0], ">") == 0 || strcmp(types[0], ">>") == 0)) && (strcmp(types[1], "<") == 0)){
                        char tmp[5];
                        strcpy(tmp, types[0]);
                        strcpy(types[0], types[1]);
                        strcpy(types[1], tmp);
                    }
                    if ((strcmp(types[0], "<") == 0) && (strcmp(types[1], ">") == 0 || strcmp(types[1], ">>") == 0)){
                        
                        // Get redirect destinations (file input and output)
                        char filename_in[BUF_SIZE]="", filename_out[BUF_SIZE]="";
                        int j;
                        for(j= 0; j < i - 1; j++){
                            if (strcmp(cmd[j], "<") == 0){
                                strcpy(filename_in, cmd[j + 1]);
                            }
                            if (strcmp(cmd[j], ">") == 0 || strcmp(cmd[j], ">>") == 0){
                                strcpy(filename_out, cmd[j + 1]);
                            }
                        }
                        cmd[i - 2]= NULL; // Erase redirects and filenames from command
                        cmd[i - 3]= NULL;
                        cmd[i - 4]= NULL;
                        cmd[i - 5]= NULL;

                        int pipefd[2];
                        if(pipe(pipefd) != 0){
                            fprintf(stderr, "pipe(2) failed.\n");
                            goto ERROR;
                        }

                        int pid= fork();
                        if (pid < 0){
                            fprintf(stderr, "ERROR: fork() failed.\n");
                            goto ERROR;
                        }
                        else if (pid > 0){
                            // Parent
                            // printf("REACH HERE1.\n");
                            close(pipefd[0]);
                            close(STDOUT_FILENO);
                            dup2(pipefd[1], STDOUT_FILENO); // Use pipefd[1] as stdout
                            FILE *fin= fopen(filename_in, "r");
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
                            // printf("REACH HERE child.\n");
                            close(STDOUT_FILENO);
                            close(STDIN_FILENO);
                            dup2(pipefd[0], STDIN_FILENO);
                            dup2(pipefd[1], STDOUT_FILENO);
                            // char buf[BUF_SIZE];
                            // while(fgets(buf, BUF_SIZE, stdin)){
                            //     printf(buf);
                            // }
                            // printf("\n");
                            // printf("REACH HERE child.\n");

                            execvp(cmd[0], cmd);
                            char tmp_buf[BUF_SIZE];
                            char content[BUF_SIZE]= "";
                            while(fgets(tmp_buf, BUF_SIZE, stdout) != NULL){
                                strcat(content, tmp_buf);
                            }
                            printf("Content: %s\n", content);
                            // Call one more child to write output of excvp(2)
                            
                            int pid_2= fork();
                            if (pid_2 < 0){
                                fprintf(stderr, "ERROR: fork() failed.\n");
                                goto ERROR;
                            }
                            // else if (pid_2 > 0){
                            //     printf("REACH HERE EPICLY\n");
                            //     close(pipefd[0]);
                            //     close(STDOUT_FILENO);
                            //     dup2(pipefd_2[1], STDOUT_FILENO);
                            //     fwrite(content, 1, strlen(content), stdout);
                            //     fputs("%d", EOF);
                                
                            //     int status_2;
                            //     waitpid(pid_2, &status_2, 0);
                            // }
                            else if(pid_2 == 0) {
                                // Child of child
                                printf("REACH HERE.\n");
                                close(pipefd[1]);
                                close(STDIN_FILENO);
                                dup2(pipefd[0], STDIN_FILENO);

                                FILE *fout;
                                if(strcmp(filename_out, ">") == 0)
                                    fout= fopen(filename_out, "w");
                                else
                                    fout= fopen(filename_out, "a");
                                if (fout == NULL){
                                    fprintf(stderr, "ERROR: Can't open file %s.\n", filename_out);
                                    goto ERROR;
                                }

                                char buf[BUF_SIZE];
                                printf("Writing to %s...\n", filename_out);
                                while(fgets(buf, BUF_SIZE, stdin) != NULL){
                                    printf(buf);
                                    fwrite(buf, 1, strlen(buf), fout);
                                }
                                fputs("%d", EOF);
                                fclose(fout);
                            }                         
                        }
                    }
                }
            }        
        }
    }
    return 0;

ERROR:
    return -1;
}
