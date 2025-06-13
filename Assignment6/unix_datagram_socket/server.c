#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_datagram_socket"
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Xóa socket file cũ nếu có
    unlink(SOCKET_PATH);

    server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Unix Datagram Server listening on %s\n", SOCKET_PATH);

    // Nhận dữ liệu từ client
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recvfrom(server_fd, buffer, BUFFER_SIZE - 1, 0,
                                  (struct sockaddr*)&client_addr, &client_len);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received: %s\n", buffer);

        // Gửi phản hồi
        char response[] = "Hello from Unix Datagram Server!";
        sendto(server_fd, response, strlen(response), 0,
               (struct sockaddr*)&client_addr, client_len);
        printf("Response sent!\n");
    }

    close(server_fd);
    unlink(SOCKET_PATH);  
    return 0;
}