/*             Program demonstrating the use of thread semaphore            * 
 *             Wriiten by B R Sahu on 23/03/2002                            *
 ****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *arg);          //thread function  
char message[] = "Hello World";           
sem_t  sem;

int main()
{
  int retVal;
  pthread_t a_thread;                       //pthread object
  void *thread_result;                      //pointer to result

  sem_init(&sem, 0, 0);

  retVal = pthread_create(&a_thread,NULL,thread_function,(void *)message);
  if(retVal != 0)
    {
      perror("Thread creation failed\n");
      exit(EXIT_FAILURE);
    }

  printf("Waiting for thread(%d) to finish...\n", retVal);
  sleep(8);
  sem_post(&sem);

  retVal = pthread_join(a_thread,&thread_result); //waiting for the thread
  if(retVal != 0)                                 //to join
    {
      perror("Thread join failed\n");
      exit(EXIT_FAILURE);
    } 

  printf("Thread joined, it returned %s",(char *)thread_result); //print the 
                                                                    //return value    
  printf("Message is now %s",message);
  sem_destroy(&sem);
  exit(EXIT_SUCCESS);
}
 
void *thread_function(void *arg)
{
  printf("Thread function is started. Argument was %s\n",(char *)arg);
  sem_wait(&sem);
  printf("Thread function is running.\n");
  strcpy(message,"Bye\n");
  pthread_exit("Thank you for the CPU time\n");
}
 
