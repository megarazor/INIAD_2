#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int hello(int sockfd)
{
    FILE* fp;
    char buf[64];
    char msgs[32] = "Type your name, please: ";
    char name[512];
    int n;

    fp = fdopen(sockfd, "r+");
    if (!fp) {
        close(sockfd);
        return -1;
    }

    fwrite(msgs, 1, strlen(msgs), fp);
    fflush(fp);
    fgets(name, sizeof(name), fp);
    n = strlen(name);

    name[n-1] = '\0';
    sprintf(buf, "Hello %s, nice to meet you!\n", name);

    fwrite(buf, 1, strlen(buf), fp);
    fflush(fp);
    fclose(fp);

    return 0;
}

int main()
{
    /* IPv4 only */
    struct sockaddr_in srv, cli;
    socklen_t cli_size;
    int fd, sockfd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        return 1;
    }

    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = INADDR_ANY;
    srv.sin_port = htons((unsigned short)12345);

    if (bind(fd, (struct sockaddr*)&srv, sizeof(srv)) == -1) {
        return 2;
    }
    if (listen(fd, 5) == -1) {
        return 3;
    }

    for (;;) {
        cli_size = sizeof(cli);
        sockfd = accept(fd, (struct sockaddr*)&cli, &cli_size);
        if (sockfd == -1) {
            return 5;
        }

        hello(sockfd);
    }

    return -1;
}