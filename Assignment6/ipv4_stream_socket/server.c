#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    //tao socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("Socket create failed\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //bind
    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Bind socket failed\n");
        exit(EXIT_FAILURE);
    }
    //listen
    if(listen(server_fd, 5) < 0) {
        perror("Listen failed\n");
        exit(EXIT_FAILURE);
    }
    printf("TCP server listening on port %d\n", PORT);
    //accept
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if(client_fd < 0) {
        perror("accept failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Client connected from %s\n", inet_ntoa(client_addr.sin_addr));
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if(bytes_received > 0) {
        printf("Received: %s\n", buffer);

        //gui phan hoi
        char reponse[] = "Hello from ipv4 server";
        send(client_fd, reponse, strlen(reponse), 0);
    }    

    close(client_fd);
    close(server_fd);
}