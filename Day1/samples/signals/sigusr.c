/*
 * SIGUSR1, SIGUSR2
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

static void sig_usr(int);	/* one handler for both the signals */

int main(void)
{
  if (signal(SIGUSR1, sig_usr)== SIG_ERR)
  {
    printf("Cannot catch SIGUSR1\n");
    exit(1);
  }

  if (signal(SIGUSR2, sig_usr)== SIG_ERR)
  {
    printf("Cannot catch SIGUSR2\n");
    exit(1);
  }

  for (; ; )
    pause();
}

static void sig_usr(int signo)	/* argument is signal numer */
{
  if (signo == SIGUSR1)
    printf("received SIGUSR1\n");
  else if (signo == SIGUSR2)
    printf("received SIGUSR2\n");
  else
  {
    printf("received signal %d\n", signo);
    exit(1);
  }
}

