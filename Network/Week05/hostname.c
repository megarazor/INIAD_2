#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

const int BUF_SIZE= 256;
const int IP_SIZE= 64;
//const char SERVER_IP[]= "127.0.0.1";
const unsigned short SERVER_PORTNUM= 8000;
//const char MESSAGE[]= "GET / HTTP/1.1\n\n";

void error_handler(const char *message){
    fprintf(stderr, "%s", message);
    exit(1);
}

int hostname_to_ip(char *hostname , char *ip)
{
	struct hostent *dumb;
	struct in_addr **addr_list;
	int i;	
	if ((dumb = gethostbyname(hostname)) == NULL){
		herror("gethostbyname() failed\n");
		return 1;
	}
	addr_list= (struct in_addr**) dumb->h_addr_list;
	for(i= 0; addr_list[i] != NULL; i++){
		strcpy(ip, inet_ntoa(*addr_list[i]));
		return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {
    while (1){
        char SERVER_IP[IP_SIZE];
        char SERVER_HOSTNAME[IP_SIZE];
        printf("Server hostname: ");
        fgets(SERVER_HOSTNAME, IP_SIZE, stdin);
        SERVER_HOSTNAME[strlen(SERVER_HOSTNAME) - 1]= '\0'; // Delete the last '\n' character
        hostname_to_ip(SERVER_HOSTNAME, SERVER_IP);
        printf("Server IP: %s\n", SERVER_IP); 

        int sock;
        if ((sock= socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
            error_handler("socket() failed");
        }

        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family= AF_INET;
        server_addr.sin_addr.s_addr= inet_addr(SERVER_IP);
        server_addr.sin_port= htons(SERVER_PORTNUM);

        if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
            error_handler("connect() failed.\n");
        }

        char MESSAGE[BUF_SIZE];
        // Input message with stdin, looped
        printf("Your message: ");
        fgets(MESSAGE, BUF_SIZE, stdin);
        strcat(MESSAGE, "\n\n"); // Add "\n\n" to the end of MESSAGE to match HTTP format

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
    }
    exit(0);
}
