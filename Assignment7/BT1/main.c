#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>

#define MSG_SIZE 20

char *msg = "I am Hung";

int main(int argc, char const *argv[]) 
{
    char buffer[MSG_SIZE];
    int num_read = 0;
    int fds[2];
    pid_t child_pid;

    if(pipe(fds) < 0) {
        printf("pipe unsuccessfully\n");
        exit(1);
    }

    child_pid = fork();
    if(child_pid == 0) {
        printf("I am reader\n");
        close(fds[1]);
        while(1){
            num_read = read(fds[0], buffer, MSG_SIZE);
            if(num_read == -1) {
                printf("read failed\n");
            } else if(num_read == 0) {
                printf("pipe end-of-pipe\n");
                break;
            } else {
                printf("msg: %s\n", buffer);
            }
        }
        close(fds[0]);
        exit(0);
    } else if(child_pid > 0) {
        printf("I am writer\n");
        close(fds[0]);
        write(fds[1], msg, MSG_SIZE);
        close(fds[1]);
    } else {
        printf("fork failed\n");
        exit(1);
    }
    return 0;
}
