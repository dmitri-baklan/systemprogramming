#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


//  gcc main1.c
//  ./a.out
//  terminal: kill -1 pid


FILE *fp;

void signal_handler(int signo, siginfo_t *sinfo, void *ucontext);

int main() {
    // writing to log.txt
    int i=0;
    fp = fopen("./log.txt", "a+t");
    printf("Running..\n");
    fprintf(fp, "PID: %i\n", getpid());
    fflush(fp);
    //init  each member of struct w/0 
    struct sigaction act;
    struct sigaction old;

    act.sa_handler = NULL; //ykazatel`
    // assign the new handler
    act.sa_sigaction = signal_handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = SA_RESETHAND & SA_SIGINFO;
    //set act 4 signal
    sigaction(SIGHUP, &act, &old);
    while (1) {
        printf("(%d): Inside infinite loop =)",i);
        sleep(5);
        fprintf(fp, "sleeping\n");
        fflush(fp);
        i++;
    }
    return 0;
}

void signal_handler(int signo, siginfo_t *sinfo, void *ucontext) {
    fprintf(fp, "Signal number being deliver: %i\n", sinfo->si_signo);
    fprintf(fp, "Signal code: %i\n", sinfo->si_code);
    fprintf(fp, "Signal value: %i\n", sinfo->si_value);
    fprintf(fp, "Errno association w/signal: %i\n", sinfo->si_errno);
    fprintf(fp, "Process ID: %i\n", sinfo->si_pid);
    fprintf(fp, "Real user ID: %i\n", sinfo->si_uid);
    fprintf(fp, "Address at which fault occurred: %i\n", sinfo->si_addr);
    fprintf(fp, "Exit value: %i\n", sinfo->si_status);
    fprintf(fp, "Band event for SIGPOLL/SIGIO: %ld\n", sinfo->si_band);
    fflush(fp);
}