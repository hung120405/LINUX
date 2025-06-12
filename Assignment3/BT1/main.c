#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 

int main(int argc, char* argv[]) {
    pid_t pid;
    int a = 0;
    printf("Gia tri khoi tao cua a: %d\n", a);
    pid = fork();
    
    if (0 == pid) {    // Child process
        printf("\nIm the child process, a: %d\n", a);
        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
        exit(0);  
    } else if (pid > 0) {   // Parent process
        printf("\nIm the parent process, a: %d\n", ++a);  
        printf("My PID is: %d, my child PID is: %d\n", getpid(), pid);
        wait(NULL); 
    } else {
        printf("ERROR\n");
        return 1;
    } 
    
    return 0;
}