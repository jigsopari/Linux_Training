/*********************************************************************/
/*                                                                   */
/*    This is the client-server  program   using                     */
/*   pipe  with parent process and child process                     */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#define MAXBUFF 1024

/********* start of client function ************/

client(readfd,writefd)
int readfd;
int writefd;

{
  char buff[MAXBUFF];
  int n;
 /*read the file name from the standard input,
  *write it to the IPC descriptor 
 */
  printf("enter the file name\n");
  if(fgets(buff,MAXBUFF,stdin) ==NULL)
    err_sys("client:filename read error");
  n=strlen(buff);
  if (buff[n-1]== '\n')
     n--;
  /*
  *ignore newline from fgets() 
  */
  if(write(writefd,buff,n) !=n)
     err_sys("client: file name write error");

  /*
  * read the data from the IPC descriptor and 
  * write to standard output
  */

  while((n=read(readfd,buff,MAXBUFF)) > 0)
  if(write(1,buff,n)!=n)                 /*fd 1 =stdout */
     err_sys("client:data read error");
  if(n < 0)
    err_sys("client: data read error"); 
 
}

/********end of client function*********** */ 
                                         

/********start of server function **********/ 

server(readfd,writefd)

int readfd;
int writefd;
{
  char buff[MAXBUFF];
  char errmesg[256], *sys_err_str();
  int  n,fd;
  extern int errno;

  /*
   * Read the file name from the IPC descriptor.
  */

  if(( n = read(readfd, buff, MAXBUFF)) <= 0 )
    err_sys("server:filename read error");
  buff[n]='\0';
  if((fd=open(buff,0))< 0)  
    {
     /* Error Format an error message and send it 
     * back to the client  
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
         *the IPC descriptor. 
        */
        while ( (n= read(fd,buff,MAXBUFF)) > 0)
        if(write(writefd,buff,n )!=n)
           err_sys("server: data write error");
        if (n < 0)
          err_sys("server: read error");
        }

}
/*******end of server function**************/


/*******start of main***********************/
main()
{
  int childpid, pipe1[2], pipe2[2];

  if (pipe(pipe1) < 0 || pipe(pipe2) < 0 )
    err_sys("can't create pipes ");
  if( (childpid = fork()) < 0 )
    {
     err_sys("can't fork");
    }
    else if (childpid > 0 )   /* parent process */
        {
        close(pipe1[0]);
        close(pipe2[1]);
        client(pipe2[0],pipe1[1]);
        while (wait((int *) 0) !=childpid) /* wait for the child process */
        close(pipe1[1]);
        close(pipe2[0]);
        exit (0);
        }
        else 
            {
             close(pipe1[1]);
             close(pipe2[0]);
             server(pipe1[0],pipe2[1]);
             close(pipe1[0]);
             close(pipe2[1]);
             exit(0);
            }
}

/******end of the main ***********/ 

/* display err message and exit */

err_sys(char *s)
{
  printf("%s\n", s);
  exit(1);
}

/*****************    End of the program          *********/

/*-------------------------------------------------------------------*/
