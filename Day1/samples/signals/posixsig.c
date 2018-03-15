/*
 * program to demonstrate the use of posix signal
 *
*/

#define _POSIX_SOURCE 1

/* System Headers */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* Macros */
#define TIMEOUT 30
#define TRUE 1
#define FALSE 0

/* File scope variables */
volatile int flag; 	/* The keyword volatile warns the
			 * compiler that the variable flag
			 * may change in a way that is not
			 * predictable by the compiler.
			*/
/* External variables */
/* NONE */
/* External functions */
/* NONE */
/* Structures and Unions */
/* Signal Catching Functions */

/*
 * The ding() function catches the SIGALRM signal and
 * merely sets flag to FALSE.
*/
void ding()
{
flag = FALSE;
return;
}

/*
 * The gettext function reads a line from the user's
 * console. If the line is not typed within TIMEOUT
 * seconds, the gettext() function aborts the read and
 *
 * returns zero.
*/
int gettext(char *buffer,int bufsize)
{
  struct sigaction act,oact;
  int nchars;

  act.sa_handler = ding; /* Call ding() when the
			* alarm goes off
			*/
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if (sigaction(SIGALRM,&act,&oact) != 0)
	 printf("Panic!!!\n");
    flag = TRUE;
  (void)alarm(TIMEOUT);
  nchars = read(STDIN_FILENO,buffer,bufsize);
  (void)alarm(0); /* Cancel outstanding SIGALRM (if any) */
  /* Restore previos signal handler for SIGALRM */
  if (sigaction(SIGALRM,&oact,NULL) != 0)
	 printf("Panic!!!\n");
  if (flag) return(nchars);
  return(0);
}

int main(int argc, char *argv[])
{
  char buffer[40];
  int bufsize=20;

  gettext(buffer, bufsize);
}
