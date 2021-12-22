#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char* argv[])
{
    FILE *fp= NULL;
    pid_t process_id = 0;
    pid_t sid = 0;

    process_id = fork();

    if (process_id < 0)
    {
        printf("fork failed!\n");
        exit(1);
    }

    if (process_id > 0)
    {
        printf("process_id of child process %d \n", process_id);
        exit(0);
    }

    sid = setsid();
    if(sid < 0)
    {
        exit(1);
    }

    chdir("/");
    int size = getdtablesize();
    for (int i = 0; i < size; i++)
    {
        close(i);
    }
    printf("1");
    open("/dev/null", O_RDONLY, stdin);
    open("/dev/null", O_WRONLY, stdout);
    open("/dev/null", O_WRONLY, stderr);
    printf("before doc");
    if((fp = fopen ("Log.txt", "w+"))!=NULL){
        printf("open");
    }

    fprintf(fp, "Pid: %d\n", getpid());
    fprintf(fp, "Ppid: %d\n", getppid());
    fprintf(fp, "Gid: %d\n", getgid());
    fprintf(fp, "Sid: %d\n", getsid(0));
    fprintf(fp, "Uid: %d\n", getuid());
    while (1)
    {
        sleep(1);
        fprintf(fp, "endurance time in an infinite loop\n");
        fflush(fp);
    }
    fclose(fp);
    return (0);
}