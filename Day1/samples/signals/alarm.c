/******************************************************************/
/*                                                                */
/*  This program demonstrate about signal handling using SIGALRM  */
/*                                                                */ 
/******************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>   
#include <curses.h>

void  handler()
{
  printf("\nhello world\n");
}

int main()
{
  signal(SIGALRM,handler);
  alarm(10);
  printf("waiting for 10 sec timeout, Press ^C to terminate...\n");
  pause();
  return 0;
}

/*---------------------End of the program-----------------------*/
