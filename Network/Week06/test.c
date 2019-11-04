#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <netinet/in.h>

#define BUF_SIZE 800
#define SERVER_PORTNUM 9000
#define QUEUE_SIZE 1

uint32_t reverse_bytes_32(uint32_t bytes){
    uint32_t aux = 0;
    uint8_t byte;
    int i;
    for(i = 0; i < 32; i+=8)    {
        byte = (bytes >> i) & 0xff;
        aux |= byte << (32 - 8 - i);
    }
    return aux;
}

int uint32_t_to_ip(char *buf, uint32_t bytes){  // Assume that the bytes are reversed already, in case of network byte order
    uint32_t part4, part3, part2, part1;
    part4 = bytes & 0x000000ff;
    part3 = (bytes & 0x0000ff00) >> 8;
    part2 = (bytes & 0x00ff0000) >> 16;
    part1 = (bytes & 0xff000000) >> 24;
    sprintf(buf, "%" PRIu32 ".%" PRIu32 ".%" PRIu32 ".%" PRIu32 "", part1, part2, part3, part4);
    return 0;
}

uint16_t reverse_bytes_16(uint16_t bytes){
    uint16_t aux = 0;
    uint8_t byte;
    int i;
    for(i = 0; i < 16; i+=8)    {
        byte = (bytes >> i) & 0xff;
        aux |= byte << (16 - 8 - i);
    }
    return aux;
}

int uint16_t_to_port(char *buf, uint16_t bytes){  // Assume that the bytes are reversed already, in case of network byte order
    sprintf(buf, "%" PRIu16 "", bytes);
    return 0;
}



int main(int argc, char *argv[]){
    uint32_t ip= inet_addr("127.0.0.1");
    uint16_t port= htons(SERVER_PORTNUM);
    uint32_t reverse_ip= reverse_bytes_32(ip);
    uint16_t reverse_port= reverse_bytes_16(port);

    char str_ip[BUF_SIZE], str_port[BUF_SIZE];
    
    uint32_t_to_ip(str_ip, reverse_ip);
    uint16_t_to_port(str_port, reverse_port);
    printf("IP: %s\n", str_ip);
    printf("Port: %s\n", str_port);
}
