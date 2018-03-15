/*             Program demonstrating the use of pthread_create ()           * 
 *             Wriiten by Anoop Augustine on 30/08/2001                     *
 ****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

void *thread_function(void *arg);          //thread function  
int userfunction();
char message[] = "Hello World";           

int main()
{
  int retVal;
  pthread_t a_thread;                       //pthread object
  void *thread_result;                      //pointer to result

  retVal = pthread_create(&a_thread,NULL,thread_function,(void *)message);
  if(retVal != 0)
    {
      perror("Thread creation failed\n");
      exit(EXIT_FAILURE);
    }

  printf("Waiting for thread(%d) to finish...\n", retVal);
  sleep(4);
  kill(retVal, SIGUSR1);
  retVal = pthread_join(a_thread,&thread_result); //waiting for the thread
  if(retVal != 0)                                 //to join
    {
      perror("Thread join failed\n");
      exit(EXIT_FAILURE);
    } 

  printf("Thread joined, it returned %s",(char *)thread_result); //print the 
                                                                    //return value    
  printf("Message is now %s",message);
  exit(EXIT_SUCCESS);
}
    
void *thread_function(void *arg)
{
  signal(SIGUSR1, userfunction);

  printf("Thread function is started. Argument was %s\n",(char *)arg);
  pause();
  printf("Thread function is running.\n");
  strcpy(message,"Bye\n");
  pthread_exit("Thank you for the CPU time\n");
}
  
int userfunction()
{
//  printf("caught SIGUSR1\n");
  return 0;
}  

