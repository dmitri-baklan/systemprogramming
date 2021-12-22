#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t child = fork();
    if (child == 0) {
        printf("\nChild:\n");
        printf("Pid: %d\n", getpid());
        printf("Ppid: %d\n", getppid());
        printf("Gid: %d\n", getgid());
        printf("Sid: %d\n", getsid(0));
        printf("Uid: %d\n", getuid());
        printf("child process is stoped\n");
    } else {
        printf("\nParent:\n");
        printf("Pid: %d\n", getpid());
        printf("Ppid: %d\n", getppid());
        printf("Gid: %d\n", getgid());
        printf("Sid: %d\n", getsid(0));
        printf("Uid: %d\n", getuid());
        printf("Child process pid: %i\n", child);
        wait(NULL);
        printf("parent process is stoped\n");
    }
    return 0;
}
