/*             Program demonstrating the use of pthread_mutex()             * 
 *             Wriiten by B R Sahu on 23/03/2002                            *
 ****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);          //thread function  
char message[] = "Hello World";           
pthread_mutex_t mutex;

int main()
{
  int retVal;
  pthread_t a_thread;                       //pthread object
  void *thread_result;                      //pointer to result

  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_lock(&mutex);

  retVal = pthread_create(&a_thread,NULL,thread_function,(void *)message);
  if(retVal != 0)
    {
      perror("Thread creation failed\n");
      exit(EXIT_FAILURE);
    }

  printf("Waiting for thread(%d) to finish...\n", retVal);
  sleep(5);
  pthread_mutex_unlock(&mutex);

  retVal = pthread_join(a_thread,&thread_result); //waiting for the thread
  if(retVal != 0)                                 //to join
    {
      perror("Thread join failed\n");
      exit(EXIT_FAILURE);
    } 

  printf("Thread joined, it returned %s",(char *)thread_result); //print the 
                                                                    //return value    
  printf("Message is now %s",message);
  pthread_mutex_destroy(&mutex);
  exit(EXIT_SUCCESS);
}
    
void *thread_function(void *arg)
{
  printf("Thread function is started. Argument was %s\n",(char *)arg);
  pthread_mutex_lock(&mutex);
  printf("Thread function is running.\n");
  strcpy(message,"Bye\n");
  pthread_exit("Thank you for the CPU time\n");
}
 
