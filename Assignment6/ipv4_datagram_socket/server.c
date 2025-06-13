#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() 
{
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_fd < 0){
        perror("Socket create failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("ipv4 server listening on port %d\n", PORT);

    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recvfrom(server_fd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_addr, &client_len);
    if(bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("received form %s:%d: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
        char response[] = "hello from ipv4 UDP server";
        sendto(server_fd, response, strlen(response), 0, (struct sockaddr*)&client_addr, client_len);
        printf("response done\n");
    }
    close(server_fd);
    return 0;
    
}
