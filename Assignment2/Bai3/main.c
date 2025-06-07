#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  // system calls
#include<fcntl.h>   // flag 
#include<sys/stat.h> // file status
#include<time.h>
int main() {
    char filename[] = "hello.txt";
    char text[] = "Hello Hung!";

    int fd;
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644); 
    if (fd < 0) {
        printf("open() %s failed\n", filename);
        return 1;
    }

    write(fd, text, strlen(text));
    close(fd);
    printf("Da tao file %s va ghi du lieu thanh cong\n", filename);

    struct stat info;
    if (stat(filename, &info) < 0) {
        printf("stat() %s failed\n", filename);
        return 1;
    }
    printf("Thong tin ve file %s:\n", filename);
    //Tên file
    printf("Ten file: %s\n", filename); 
    //Loại file
    printf("Loai file: ");
    if(S_ISREG(info.st_mode)) {
        printf("File thuong\n");
    } else if (S_ISDIR(info.st_mode)) {
        printf("Thu muc\n");
    } else {
        printf("Loai khac\n");
    }
    //Thời gian chỉnh sửa lần cuối
    printf("Thoi gian chinh sua lan cuoi: %s", ctime(&info.st_mtime));
    //Kích thước file
    printf("Kich thuoc file: %ld bytes\n", info.st_size);

    return 0;
}