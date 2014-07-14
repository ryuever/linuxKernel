#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 4096
typedef void Sigfunc(int);

static void sig_int(int signo) {
	int	i, j, n;
	volatile int k = 0;
    char line[MAXLINE];

 /*
  * Tune these loops to run for more than 5 seconds
  * on whatever system this test program is run.
  */
    printf("\nsig_int starting\n");

    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
        perror("read error");
    write(STDOUT_FILENO, line, n);
    /* for (i = 0; i < 300000; i++) */
    /*     for (j = 0; j < 20000; j++) */
    /*         k += i * j; */

    printf("sig_int finished\n");
}

void sig_alrm(int signo){
    printf("in sig_alrm\n");
}

Sigfunc *signal2(int signo, Sigfunc *func){
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

/*     if (signo == SIGALRM) { */
/* #ifdef SA_INTERRUPT */
/*         printf("sa_interrupt\n"); */
/*         act.sa_flags |= SA_INTERRUPT; */
/* #endif */
/*     } else { */
/*         act.sa_flags |= SA_RESTART; */
/*         printf("sa_flags is setted as restart\n"); */
/*     } */
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
    
    unslept = alarm(5);
    sleep(6);
    
    printf("sleep returned: %u\n", unslept);
    exit(0);
}
