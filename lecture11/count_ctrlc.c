#include <stdio.h>     /* standard I/O functions                         */
#include <unistd.h>    /* standard unix functions, like getpid()         */
#include <signal.h>    /* signal name macros, and the signal() prototype */

/* first, define the Ctrl-C counter, initialize it with zero. */
int ctrl_c_count = 0;
#define	CTRL_C_THRESHOLD	3

/* the Ctrl-C signal handler */
void catch_int(int sig_num)
{
    sigset_t mask_set;	/* used to set a signal masking set. */
    sigset_t old_set;	/* used to store the old mask set.   */

    /* re-set the signal handler again to catch_int, for next time */
    signal(SIGINT, catch_int);
    /* mask any further signals while we're inside the handler. */
    sigfillset(&mask_set);
    sigprocmask(SIG_SETMASK, &mask_set, &old_set);
    
    /* increase count, and check if threshold was reached */
    ctrl_c_count++;
    if (ctrl_c_count >= CTRL_C_THRESHOLD) {
	char answer[30];

	/* prompt the user to tell us if to really exit or not */
	printf("\nRealy Exit? [y/N]: ");
	fflush(stdout);
	fgets(answer, sizeof(answer), stdin);
	if (answer[0] == 'y' || answer[0] == 'Y') {
	    printf("\nExiting...\n");
	    fflush(stdout);
	    exit(0);
	}
	else {
	    printf("\nContinuing\n");
	    fflush(stdout);
	    /* reset Ctrl-C counter */
	    ctrl_c_count = 0;
	}
    }
  /* no need to restore the old signal mask - this is done automatically, */
  /* by the operating system, when a signal handler returns.              */  
    
}

int main(int argc, char* argv[])
{
    /* set the Ctrl-C signal handler */
    signal(SIGINT, catch_int);

    /* enter an infinite loop of waiting for signals */
    for ( ;; )
	pause();

    return 0;
}

