#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_signal(int sig) {
    printf("Con nhận được tín hiệu SIGUSR1!\n");
}

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Process con
        signal(SIGUSR1, handle_signal);
        printf("Con đang chờ...\n");
        while(1) sleep(1);
    } else {
        // Process cha
        sleep(2);
        kill(pid, SIGUSR1);
        printf("Cha đã gửi tín hiệu\n");
        wait(NULL);
    }
    
    return 0;
}