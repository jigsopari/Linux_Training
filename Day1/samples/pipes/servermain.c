/******************************************************************/
/*         This program demonstrate the use of FIFO               */
/*         in the server side program                             */
/*                                                                */
/******************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>
#include "server.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define PERMS 0666
#define MAXBUFF 1024

extern int errno;    
main()
{
  int readfd,writefd;

  /*
  Create the FIFOs,  open them one for 
  reading and one for writing 
  */

  if ( (mknod(FIFO1, S_IFIFO | PERMS, 0)< 0) && (errno !=EEXIST))
    err_sys("cant create fifo: %s",FIFO1);
  if ( (mknod(FIFO2, S_IFIFO | PERMS, 0)< 0) && (errno !=EEXIST))
   {
    unlink(FIFO1);
    err_sys("cant create fifo: %s",FIFO2);
   }
  if ( (readfd=open(FIFO1,0)) < 0 )
    err_sys("servr:can't open read fifo: %s", FIFO1);
  if ( (writefd=open(FIFO2,1)) < 0 ) 
    err_sys("server:can't open write fifo: %s", FIFO2);
  server(readfd,writefd);
  close(readfd);
  close(writefd);
  exit(0);
}
/*print error message and exit*/

err_sys(char *s)
{
  printf("%s\n", s);
  exit(1);
}

/*-----------------------End of the program--------------------*/  
 
