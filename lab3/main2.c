#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/errno.h>


// gcc -o task2 main2.c -lrt 
// ./task2


struct datum {
    pid_t pid;
    struct tm currenttime;
    char buffer[512];
};

int main(void) {
    int fd;
    char buffer[512];
    struct datum *datum = NULL;
    time_t currenttime;

    fd = shm_open("lab3-task2", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("object not opened");
        return -1;
    }

    if (ftruncate(fd, sizeof(struct datum)) != 0) {
        perror("problems w/ftruncate");
        printf("Error code: %d\n", errno);
        return -1;
    }

    datum = mmap(NULL, sizeof(struct datum), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (datum == MAP_FAILED) {
        perror("problems w/mmap");
        return -1;
    }

    while (1) {
        printf("Please enter smth:\n");
        //read from str console
        fgets(buffer, 512, stdin);
        //datum info
        msync(datum, sizeof(struct datum), MS_SYNC);
        printf("Pid: %d\n", datum->pid);
        printf("Time: %s\n", asctime(&(datum->currenttime)));
        printf("String: %s\n", datum->buffer);
        //write to datum
        datum->pid = getpid();
        time(&currenttime);
        datum->currenttime = (*localtime(&currenttime));
        strcpy(datum->buffer, buffer);
    }
   return 0;
}