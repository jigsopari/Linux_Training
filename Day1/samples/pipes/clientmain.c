/***********************************************************/
/*                                                         */
/*       This program demonstrate the use of FIFO          */
/*       in client side                                    */
/*                                                         */
/***********************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>
#include "client.h"
 
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define PERMS 0666
#define MAXBUFF 1024
extern int errno;    
main()
{
  int readfd, writefd;

  /* Open the FIFOs we assume the server has 
   * already created them. 
  */
  if((writefd = open(FIFO1,1)) <0)
     err_sys("client: cant't open write fifo: %s",FIFO1);  
  if ( ( readfd =open(FIFO2 ,0)) < 0)
     err_sys("client: can't open read filo: %s",FIFO2);
  client(readfd,writefd);
  close(readfd);
  close(writefd);

  /* Delete the FIFOs, now that 
   * we are finished 
  */
  if(unlink(FIFO1)<0)
     err_sys("client:can't unlink %s",FIFO1);
  if(unlink(FIFO2)<0) 
     err_sys("client:can't unlink %s",FIFO2);
   exit(0);
} 
   
/********** end of main *****************/

/* display err message and exit*/   
  err_sys(char *s)
{
  printf("%s\n", s);
  exit(1);
}

/*---------------End of the program-------------------*/

