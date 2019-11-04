#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

int main ()
{
    int c= 0;
    int printed= 0;
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
        // char input[BUF_SIZE]= "Message\n";
        // printf("Input: %s\n", input);
        FILE *fin= fopen("a", "r");
        char buf[BUF_SIZE], whole[BUF_SIZE]= "";
        while(fgets(buf, BUF_SIZE, fin) != NULL){
            strcat(whole, buf);
        }
        printf("Whole: %s\n", whole);

        // close(pipefd[0]);
        // close(STDOUT_FILENO);
        // dup2(pipefd[1], STDOUT_FILENO);

        char child_ret[BUF_SIZE];
        int ret= 10;

        // printf("%s", whole);
        // printf("%d", EOF);
        

        waitpid(pid, &ret, 0);
        c= ret;
        // return 0;
        // printf("Return from child: %d\n", ret);

        // printf("Returned from child: %s\n", child_ret);

        // FILE *fout= fopen("out", "w");
        // fwrite(child_ret, 1, strlen(child_ret), fout);
        // fclose(fout);
        // return 0;
    }
    else {
        printf("HERE\n");
        return 3;
        printf("HERE 2\n");
        char failed[7]= "failed";
        return failed;
        close(pipefd[1]);
        close(STDIN_FILENO);
        dup2(pipefd[0], STDIN_FILENO);

        char buf[BUF_SIZE], content[BUF_SIZE]= "";
        int i= 0;
        while(!EOF){
            int n= fgets(buf, BUF_SIZE, stdin);
            if (n){
                printf("Read: %s", buf);
                strcat(content, buf);
                printed++;
            }
            i++;
            if(i == 3){
                return "failed";
            }
        }
        return "failed";
        strcat(content, " - processed by child\n");

        return content;
    }
    printf("c: %d\n", c);
    printf("Printed: %d\n", printed);
}