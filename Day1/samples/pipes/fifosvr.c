/*************************************************************/
/*                                                           */
/*     This program demonstrates the use of FIFO in          */
/*     Server side program                                   */
/*                                                           */
/*************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <stdio.h>

extern int errno;

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define PERMS 0666

#define MAXBUFF 1024

/*****************start of client function*************/
 
client(readfd,writefd)
int readfd;
int writefd;
 
{
  char buff[MAXBUFF];
  int n;
 
 /*read the file name from the standard input,
 *write it to the IPC discriptor 
 */

 if(fgets(buff,MAXBUFF,stdin) ==NULL)
   err_sys("client:filename read error");
  n=strlen(buff);

 if(buff[n-1]== '\n')
   n--;                     /*ignore newline from fgets() */

 if(write(writefd,buff,n) !=n)
   err_sys("client: file name write error");

 /*read the data from the IPC descriptor and
  *write to standard output
 */
 
 while((n=read(readfd,buff,MAXBUFF)) > 0)
  if(write(1,buff,n)!=n)              /*fd 1 =stdout */
   err_sys("client:data read error");
 if(n < 0)
   err_sys("client: data read error");
 
}

/**********   end of client function    ****************/
                                                     
                                                     
/**********  start of server function   ****************/

server(readfd,writefd)
int readfd;
int writefd;
{
char buff[MAXBUFF];
char errmesg[256], *sys_err_str();
int n,fd;
extern int errno;
 
/*Read the file name from the IPC descriptor.*/

  if(( n = read(readfd, buff, MAXBUFF)) <= 0 )
    err_sys("server:filename read error");
  buff[n]='\0';
  if((fd=open(buff,0))< 0)
  {
    /* Error Format an error message and send it back to 
     * the   client  
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
    *the IPC discriptor. 
    */
    while ( (n= read(fd,buff,MAXBUFF)) > 0)
    if(write(writefd,buff,n )!=n)
      err_sys("server: data write error");
    if(n < 0)
      err_sys("server: read error");
   }
}

   /*******  end of server function     ****************/


   /*******     start of main           ****************/

main()
{
  int childpid, readfd, writefd;

  if( (mknod(FIFO1, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST))
     err_sys("can't create file 1: %s", FIFO1);
  if( (mknod(FIFO2, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST))
    {
     unlink(FIFO1);
     err_sys("can't create file 2: %s", FIFO2);
    }
   if( (childpid = fork()) <0 )
     {
      err_sys("cant fork ");
     }
     else if(childpid >0)
     {
         if ( (writefd=open(FIFO1,1))<0)
           err_sys("parent: can't open write fifo");
         if ( (readfd=open(FIFO2,0))<0)
           err_sys("parent: can't open read fifo");   
         client(readfd,writefd);
         while (wait ((int *) 0) != childpid)  /*wait for child */
         close(readfd);
         close(writefd);
         if (unlink(FIFO1) < 0 )
           err_sys("parent: can't unlink %s", FIFO1);
         if (unlink(FIFO2) < 0 )  
           err_sys("parent: can't unlink %s", FIFO2);
          exit(0);
     }
     else 
     {
       if ( (readfd = open(FIFO1, 0)) < 0)
            err_sys("server: can't open read fifo: %s", FIFO1);
       if ( (writefd = open(FIFO2, 1)) < 0)
            err_sys("server: can't open read fifo: %s", FIFO2);
       server(readfd, writefd);
       close(readfd);
       close(writefd);
       exit(0);
     }

}

/* display err message and exit */

err_sys(char *s)
{
  printf("%s\n", s);
  exit(1);
}

/***************end of the main****************/

/*--------------------------------------------------------------*/

