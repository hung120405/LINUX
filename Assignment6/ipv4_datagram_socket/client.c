#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE];
    char message[] = "Hello from IPv4 UDP Client!";

    // Tạo socket 
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Sending to IPv4 UDP server...\n");

    // Gửi 
    sendto(client_fd, message, strlen(message), 0, (struct sockaddr*)&server_addr, server_len);
    printf("Message sent: %s\n", message);

    // Nhận
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recvfrom(client_fd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&server_addr, &server_len);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Server response: %s\n", buffer);
    }

    close(client_fd);
    return 0;
}