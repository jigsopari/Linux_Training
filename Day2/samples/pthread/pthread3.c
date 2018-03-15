/*
 * Program demonstrating the use of pthread_cancel()
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);           //thread function  

int main()
{
  int retVal;
  pthread_t a_thread;                       //pthread object
  void *thread_result;  
  
  retVal = pthread_create(&a_thread,NULL,thread_function,NULL);
  if(retVal != 0)                           //create the thread
     {
      perror("Thread creation failed\n");
      exit(EXIT_FAILURE);
    }
  sleep(3);
  printf("Cancelling thread...\n");
  
  retVal = pthread_cancel(a_thread);
  if(retVal != 0)                            //cancel the thread
     {
      perror("Thread cancelation failed\n");
      exit(EXIT_FAILURE);
    }
  
  printf("Waiting for thread to finish...\n");
  
  retVal = pthread_join(a_thread,&thread_result);   
  if(retVal != 0)                            //wait for the thread to join
     {
      perror("Thread join failed\n");
      exit(EXIT_FAILURE);
    }
  
  printf("Bye!\n");
  exit(EXIT_SUCCESS);
}
    
void *thread_function(void *arg)
{
  int i,retVal;
  
  retVal = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
  if(retVal != 0)                            //set the cancel state
     {
      perror("Thread pthread_setcancelstate failed\n");
      exit(EXIT_FAILURE);
    }
  
  retVal = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
  if(retVal != 0)                            //set the cancel type immediate
     {
      perror("Thread pthread_setcanceltype failed\n");
      exit(EXIT_FAILURE);
    }
  
  printf("Thread function is running\n");
  for(i = 0; i<10 ; i++)                     //wait for cancellation
    {
      printf("Thread is still running (%d)....\n",i);
      sleep(1);
    }
  pthread_exit(NULL);                    
}
 
