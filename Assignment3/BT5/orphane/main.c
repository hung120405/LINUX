#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // children process
        printf("Con: PID=%d, PPID=%d\n", getpid(), getppid());
        sleep(3);
        printf("Con sau khi cha chết: PID=%d, PPID=%d\n", getpid(), getppid());
        exit(0);
        
    } else if (pid > 0) {
        // parent process
        printf("Cha: PID=%d tạo con PID=%d\n", getpid(), pid);
        sleep(1);
        printf("Cha kết thúc\n");
        exit(0);
        
    } else {
        printf("fork failed");
        return 1;
    }
    
    return 0;
}