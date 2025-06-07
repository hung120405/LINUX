#include<stdio.h>
#include<string.h>  // for strlen
#include<stdlib.h>  // for atoi: chuyển string thành int
#include<unistd.h>  // for read, write, close
#include<fcntl.h>   // for open, các flag O_RDWR, O_CREAT

int main(int argc, char *argv[]) {
    if(argc != 5) {
        printf("Cach dung: %s filename num-bytes [r/w] \"Hello\"\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    int num_bytes = atoi(argv[2]);  // chuyển "5" thành 5
    char *mode = argv[3];
    char *text = argv[4];

    int fd;
    int num_write, num_read;
    char buffer[num_bytes + 1]; 
    fd = open(filename, O_RDWR | O_CREAT, 0644); // Mở file với quyền đọc và ghi, tạo nếu không tồn tại
    if (fd < 0) {
        printf("open() %s failed\n", filename);
        return 1;
    } 
    if (strcmp(mode, "r") == 0) {
        num_read = read(fd, buffer, num_bytes);
        if(num_read >= 0) {
            buffer[num_read] = '\0'; // Đảm bảo chuỗi kết thúc bằng null
            printf("Doc duoc %d bytes tu %s: %s\n", num_read, filename, buffer);
        } else {
            printf("read() failed\n");
        }
    } else if (strcmp(mode, "w") == 0) {
        num_write = write(fd, text, strlen(text));
        if(num_write >= 0) {
            printf("Ghi duoc %d bytes vao %s: %s\n", num_write, filename, text);
        } else {
            printf("write() failed\n");
        }
    } else {
        printf("Mode khong hop le. Su dung 'r' de doc hoac 'w' de ghi.\n");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
    
}