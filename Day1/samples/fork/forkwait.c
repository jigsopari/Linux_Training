/*
 *   Program demonstrating the use of fork() and wait()
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int childpid;
  int rc, status;

  if((childpid = fork()) > 0)              //if return value greater than zero
    {                                      //it is parent process 
      printf("I am in Parent Process\n");
      printf("Self process id=%d,Child process id=%d\n",getpid(),childpid);
      rc = wait(&status);                  //wait for the child to terminate 
      printf("rc = %d status = %d\n", rc, WEXITSTATUS(status));
      printf("Parent Process exits..\n");
    }
  else if(childpid == 0)                   //child process
   {
     printf("I am in Child Process\n");
     printf("Parent process id=%d,Child process id=%d\n",getppid(),getpid());
     printf("Child Process exits..\n"); 
     exit(300);
   }
  return 0;
}

