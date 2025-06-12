#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]) 
{
    // Lấy biến môi trường
    char* choice = getenv("CMD_CHOICE");
    if (choice == NULL) {
        printf("Thiết lập biến môi trường: export CMD_CHOICE=1 (ls) hoặc CMD_CHOICE=2 (date)\n");
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Tiến trình con
        printf("Chạy lệnh sau 2 giây...\n");
        sleep(2);
        
        if (choice[0] == '1') {
            execlp("ls", "ls", "-l", "-h", NULL);
        } else if (choice[0] == '2') {
            execlp("date", "date", NULL);
        } else {
            execlp("ls", "ls", "-l", NULL);
        }
        printf("Exec thất bại!\n");
    } else {
        // Tiến trình cha đợi con
        wait(NULL);
        printf("Hoàn thành!\n");
    }
    
    return 0;
}