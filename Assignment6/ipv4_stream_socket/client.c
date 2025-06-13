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
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[] = "hello from ipv4 Client";

    //taoj socket 
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0) {
        perror("socket create failed\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // ket noi
    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("connect failed\n");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connect to ipv4 server\n");

    //gui tin nhan
    send(client_fd, message, strlen(message), 0);
    printf("message sent: %s\n", message);

    //nhan phan hoi
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if(bytes_received > 0) {
        printf("server reponse: %s\n", buffer);
    }
    close(client_fd);
    return 0;
}