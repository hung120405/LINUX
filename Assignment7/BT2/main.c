#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#define MSG_SIZE 1024

int main(int argc, char const *argv[]) 
{
    char buffer[MSG_SIZE];
    char change_msg[MSG_SIZE];
    int fds1[2], fds2[2];
    int num_read = 0;
    pid_t child1_pid, child2_pid;
    char *msg = "Nice to meet you";

    if(pipe(fds1) < 0) {
        printf("pipe1 failed\n");
        exit(1);
    }
    if(pipe(fds2) < 0) {
        printf("pipe2 failed\n");
        exit(1);
    }

    // Tao TT con 1
    child1_pid = fork();
    if(child1_pid == 0) {
        printf("I am children 1\n");
        close(fds1[1]);
        close(fds2[0]);
        while(1) {
            num_read = read(fds1[0], buffer, MSG_SIZE);
            if(num_read == -1) {
                printf("read failed\n");
                break;
            } else if (num_read == 0) {
                printf("pipe end-of-pipe\n");
                break;
            } else {
                printf("child1: received from parent: %s\n", buffer);
                snprintf(change_msg, MSG_SIZE, "%s too", buffer);
                printf("child1: change msg: %s\n", change_msg);

                write(fds2[1], change_msg, strlen(change_msg));
            }
        }
        close(fds1[0]);
        close(fds2[1]);
        printf("child1: done\n");
        exit(0);
    } else if(child1_pid > 0) { 
        // TT con 2
        child2_pid = fork();
        if(child2_pid == 0) {
            printf("I am children 2\n");
            close(fds1[0]);
            close(fds1[1]);
            close(fds2[1]);

            while(1) {
                num_read = read(fds2[0], change_msg, MSG_SIZE);
                if(num_read == -1) {
                    printf("read failed\n");
                    break;
                } else if (num_read == 0) {
                    printf("pipe end-of-pipe\n");
                    break;
                } else {
                    printf("child2: %s\n", change_msg);
                }
            }
            close(fds2[0]);
            printf("child2: done\n");
            exit(0);
        } else if(child2_pid > 0) {
            // TT cha
            printf("I am parent\n");
            close(fds1[0]);
            close(fds2[0]);
            close(fds2[1]);
            printf("parent: send msg: %s\n", msg);
            write(fds1[1], msg, strlen(msg));
            close(fds1[1]);

            wait(NULL);
            wait(NULL);
            printf("All done\n");
        } else {
            printf("fork child2 failed\n");
            exit(1);
        }
    } else {
        printf("Fork child 1 failed\n");
        exit(1);
    }
    return 0;
}