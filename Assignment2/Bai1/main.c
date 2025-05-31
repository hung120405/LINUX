#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main(void) {
    int fd; // File descriptor - so nguyen duong
    int num_write;
    char buffer[12] = "hello world\n";
    fd = open("hello.txt", O_APPEND | O_RDWR);
    if (fd < 0) {
        printf("open() hello.txt failed\n");
        return 1;
    }
    lseek(fd, 0, SEEK_SET);
    num_write = write(fd, buffer, strlen(buffer));
    printf("write %d bytes to hello.txt\n", num_write);
    close (fd);
    return 0;
}