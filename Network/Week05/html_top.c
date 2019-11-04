#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

const int BUF_SIZE= 256;
const char SERVER_IP[]= "127.0.0.1";
const unsigned short SERVER_PORTNUM= 8000;
const char MESSAGE[]= "GET / HTTP/1.1\n\n";

void error_handler(const char *message){
    fprintf(stderr, "%s", message);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sock;
    if ((sock= socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        error_handler("socket() failed.\n");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family= AF_INET;
    server_addr.sin_addr.s_addr= inet_addr(SERVER_IP);
    server_addr.sin_port= htons(SERVER_PORTNUM);

    if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        error_handler("connect() failed.\n");
    }

    int message_size= strlen(MESSAGE);
    int total_sent_size;
    for (total_sent_size= 0; total_sent_size < message_size; ){
        int sent_size;
        if ((sent_size= send(sock, &MESSAGE[total_sent_size], message_size - total_sent_size, 0)) < 0){
            error_handler("send() failed.\n");
        }
        total_sent_size+= sent_size;
    }

    char buf[BUF_SIZE];
    int received_bytes= 0, total_received_bytes= 0;
    printf("Received messages: ");
    while(1){
        if ((received_bytes= recv(sock, buf, sizeof(buf) - 1, 0)) < 0){
            error_handler("recv() failed.\n");
        }
        else if (received_bytes == 0) {
            break;
        }
        total_received_bytes+= received_bytes;
        buf[received_bytes]= '\0';
        printf("%s", buf);
    }
    printf("\n");

    close(sock);
    exit(0);
}
