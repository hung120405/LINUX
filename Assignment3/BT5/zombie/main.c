#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Tiến trình con
        printf("Con: PID=%d kết thúc\n", getpid());
        exit(0);
        
    } else if (pid > 0) {
        // Tiến trình cha
        printf("Cha: PID=%d tạo con PID=%d\n", getpid(), pid);
        printf("Cha ngủ 10 giây không wait()\n");
        sleep(10);  
        printf("Cha kết thúc\n");
        
    } else {
        printf("fork failed");
        return 1;
    }
    
    return 0;
}