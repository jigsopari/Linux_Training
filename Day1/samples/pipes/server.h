/**********************************************************************/
/*              This function demonstrate the use of FIFO             */ 
/*               server side function                             */
/**********************************************************************/

#include <stdio.h>
#define MAXBUFF 1024 

/*************start of server function ***************************/

server(readfd,writefd)
int readfd;
int writefd;
{
  char buff[MAXBUFF];
  char errmesg[256], *sys_err_str();
  int  n,fd;
  extern int errno;
  /*
  *Read the file name from the IPC descriptor.
  */
 
  if(( n = read(readfd, buff, MAXBUFF)) <= 0 )
    err_sys("server:filename read error");
  buff[n]='\0';
    if((fd=open(buff,0))< 0)
      {
      /* Error Format an error message and send it back 
      * to the  client
      */
      sprintf(errmesg, ":can't open %s\n", err_sys());
      strcat(buff,errmesg);
      n=strlen(buff);
      if(write (writefd,buff,n) !=n)
        err_sys("server: errmesg write error");
      }
       else
          {
          /* read the data from the file and write to
          * the IPC descriptor. 
          */
          while ( (n= read(fd,buff,MAXBUFF)) > 0)
          if(write(writefd,buff,n )!=n)
            err_sys("server: data write error");
          if (n < 0)
            err_sys("server: read error");
          }
}

/*-------------------------end fo the function------------------*/





