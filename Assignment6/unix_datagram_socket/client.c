#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_SOCKET_PATH "/tmp/unix_datagram_socket"
#define CLIENT_SOCKET_PATH "/tmp/unix_datagram_client"
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE];
    char message[] = "Hello from Unix Datagram Client!";

    // Xóa client socket file cũ nếu có
    unlink(CLIENT_SOCKET_PATH);

    client_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, CLIENT_SOCKET_PATH, sizeof(client_addr.sun_path) - 1);
    
    if (bind(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        perror("Client bind failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    printf("Sending to Unix Datagram server...\n");

    // Gửi message
    sendto(client_fd, message, strlen(message), 0,
           (struct sockaddr*)&server_addr, server_len);
    printf("Message sent: %s\n", message);

    // Nhận phản hồi
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recvfrom(client_fd, buffer, BUFFER_SIZE - 1, 0,
                                  (struct sockaddr*)&server_addr, &server_len);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Server response: %s\n", buffer);
    }

    close(client_fd);
    unlink(CLIENT_SOCKET_PATH);  
    return 0;
}