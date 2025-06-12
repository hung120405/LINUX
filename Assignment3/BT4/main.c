#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    
    pid = fork();
    
    if (pid == 0) {
        // Tiến trình con
        printf("Con: PID = %d\n", getpid());
        sleep(1);
        printf("Con: kết thúc với mã 5\n");
        exit(5);
    }
    else {
        // Tiến trình cha
        printf("Cha: chờ con (PID = %d)\n", pid);
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Cha: con kết thúc với mã %d\n", WEXITSTATUS(status));
        }
    }
    
    return 0;
}