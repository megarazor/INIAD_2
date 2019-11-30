#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 1024
#define ARG_SIZE 64

int main(int argc, char* argv[]){
    if (argc != 1){
        fprintf(stderr, "shell takes no arguments.\n");
        return -1;
    }

    struct addrinfo hints, *res = NULL, *r;
    const char* portname = "10023";
    int sockfd, er;

    /* Resolve addresses */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6; /* AF_INET6(IPv6) or AF_INET(IPv4) */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; /* address for bind(2) */
    er = getaddrinfo(NULL, portname, &hints, &res);
    if (er != 0) goto error;

    /* Try to connect to any one of the addresses got */
    for (r = res; r != NULL; r = r->ai_next) {
        sockfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
        if (sockfd < 0) continue;

        er = bind(sockfd, r->ai_addr, r->ai_addrlen);
        if (er < 0) {
            close(sockfd);
            sockfd = -1;
            continue;
        }

        /* Successfully connected */
        break;
    }
    if (sockfd < 0) goto error;

    freeaddrinfo(res);
    res = NULL;

    er = listen(sockfd, 5);
    if (er < 0) goto error;
    struct sockaddr_storage addr;
    socklen_t addrlen;
    int clientfd;

    addrlen = sizeof(addr);
    er = accept(sockfd, (struct sockaddr*)&addr, &addrlen);
    if (er < 0) goto error;

    clientfd = er;
    printf("Client connected.\n");

    for (int loop= 0;; loop++){
        printf("Loop: %d\n", loop);

        // Shell interface
        er = write(clientfd, "> ", sizeof("> "));
        if (er < 0) goto error;

        // Connect input to client's input
        if (loop == 0){
            close(STDIN_FILENO);
            dup2(clientfd, STDIN_FILENO);
        }

        // Reading command input from client
        char buf[BUF_SIZE];
        char *save;
        char *token;
        char *cmd[ARG_SIZE];
        int i= 0;
        int len= read(STDIN_FILENO, buf, sizeof(buf));
        buf[len]= '\0';
        printf("Client input: %s\n", buf);

        // Reading tokens
        token= strtok_r(buf, " ", &save);
        cmd[i++]= token;
        while (token != NULL){
            token= strtok_r(NULL, " ", &save);
            cmd[i++]= token;
        }
        cmd[i - 2][strlen(cmd[i - 2]) - 1]= '\0';
        cmd[i - 1]= NULL;
    
        pid_t pid= fork();
        if (pid < 0){
            fprintf(stderr, "fork() failed.\n");
            goto error;
        }
        else if (pid > 0){
            // Parent
            int status;
            waitpid(pid, &status, 0);
        }
        else{
            // Child
            // Connect output to client side
            close(STDOUT_FILENO);
            dup2(clientfd, STDOUT_FILENO);

            int n= execvp(cmd[0], cmd);
            if (n != 0){
                write(STDOUT_FILENO, "ERROR: Can't run the command.\n", sizeof("ERROR: Can't run the command.\n"));
                goto error;
            }
            return 0;
        }
    }
    printf("Client disconnected.\n");
    close(clientfd);
error:
    if (res) freeaddrinfo(res);
    if (sockfd >= 0) close(sockfd);
    return -1;
}
