/*
 * Example of signal sets and sigprocmask
*/

#include <stdio.h>
#include <signal.h>

static void sig_quit(int);

int main(void)
{
  sigset_t newmask, oldmask, pendmask;

  if (signal(SIGQUIT, sig_quit) == SIG_ERR)
  {
    printf("can't catch SIGQUIT");
    exit(0);
  }

  /*
   * Block SIGQUIT and save current signal mask.
   */
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGQUIT);
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
  {
    printf("SIG_BLOCK error");
    exit(0);
  }

  sleep(5);		/* SIGQUIT here will remain pending */

  if (sigpending(&pendmask) < 0)
  {
    printf("sigpending error");
    exit(0);
  }

  if (sigismember(&pendmask, SIGQUIT))
    printf("SIGQUIT pending\n");

  /*
   * Reset signal mask which unblocks SIGQUIT
   */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
  {
    printf("SIG_SETMASK error");
    exit(0);
  }
  printf("SIGQUIT unblocked\n");
  
  sleep(5);		/* SIGQUIT here will terminate with core file */
  exit(1);

}

static void sig_quit(int signo)
{
  printf("caught SIGQUIT\n");
  if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
  {
    printf("can't reset SIGQUIT");
    exit(0);
  }
}

