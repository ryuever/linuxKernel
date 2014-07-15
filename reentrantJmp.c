#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>

#define MAXLINE 4096
typedef void Sigfunc(int);
static jmp_buf env_alrm;

static void sig_int(int signo) {
    volatile int i, j, n;
    volatile int k = 0;
    char line[MAXLINE];

    printf("\nsig_int starting\n");

    for (i = 0; i < 6; i++){
        sleep(1);
        printf("in for statement\n");
    }
        
    printf("sig_int finished\n");
}

void sig_alrm(int signo){
    printf("in sig_alrm\n");
    longjmp(env_alrm, 1);
}

Sigfunc *signal2(int signo, Sigfunc *func){
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    act.sa_flags |= SA_RESTART;
    //    act.sa_flags |= SA_INTERRUPT;
    printf("in func signal2\n");
    if (sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler); 
}

int main(void){
    unsigned int unslept;

    if (signal2(SIGINT, sig_int) == SIG_ERR)
        perror("signal(SIGINT) error");
    if (signal2(SIGALRM, sig_alrm) == SIG_ERR)
        perror("signal(SIGALRM) error");
    
    if (setjmp(env_alrm) == 0){
        unslept = alarm(5);
    }
    sleep(6);
    
    printf("sleep returned: %u\n", unslept);
    exit(0);
}
