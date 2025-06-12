#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>

#define MSG_SIZE 1024

int main(int argc, char const *argv[]) 
{
    char buffer[MSG_SIZE];
    int fds[2];
    int num_read = 0;
    pid_t child_pid;
    char *msg = "I am Hung";

    if(pipe(fds) < 0) {
        printf("pipe failed\n");
        exit(1);
    }
    child_pid = fork();
    if(child_pid == 0) {
        printf("I am children\n");
        close(fds[1]);
        num_read = read(fds[0], buffer, MSG_SIZE - 1);
        if(num_read == -1) {
            printf("read failed\n");
        } else if(num_read == 0) {
            printf("pipe end-of-pipe\n");
        } else {
            buffer[num_read] = '\0';
            printf("Child: %s\n", buffer);
            int char_count = strlen(buffer);
            printf("child: dem: %d\n", char_count);
        }
        close(fds[0]);
        printf("Child: done\n");
        exit(0);
    } else if(child_pid > 0) {
        printf("I am parent\n");
        close(fds[0]);
        write(fds[1], msg, strlen(msg));
        close(fds[1]);
        wait(NULL);
        printf("All done\n\n");
    } else {
        printf("fork failed\n");
        exit(1);
    }
    return 0;
}