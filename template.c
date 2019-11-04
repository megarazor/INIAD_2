#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

int main ()
{
    int pipefd[2];
    pipe(pipefd);
    if(pipe(pipefd) != 0){
        fprintf(stderr, "pipe(2) failed.\n");
        return 1;
    }

    pid_t pid= fork();
    if (pid < 0){
        printf("Error\n");
        return 1;
    }
    else if (pid > 0){
        close(pipefd[0]);
        close(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);

        int status;
        waitpid(pid, &status, 0);
    }
    else {
        close(pipefd[1]);
        close(STDIN_FILENO);
        dup2(pipefd[0], STDIN_FILENO);

        int pipefd_2[2];
        pipe(pipefd_2);
        if(pipe(pipefd_2) != 0){
            fprintf(stderr, "pipe(2) failed.\n");
            return 1;
        }
        pid_t pid_2= fork();
        if (pid_2 < 0){
            printf("Error\n");
            return 1;
        }
        else if (pid_2 > 0){
            close(pipefd_2[0]);
            close(STDOUT_FILENO);
            dup2(pipefd[1], STDOUT_FILENO);

            int status;
            waitpid(pid, &status, 0);
        }
        else {
            


    }
}