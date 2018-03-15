/*
 *  Program demonstrating the use of pthread attributes
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);           //thread function  
char message[] = "Hello World";           
int thread_finished = 0;

int main()
{
  int retVal;
  pthread_t a_thread;                       //pthread object
  pthread_attr_t thread_attr;               //pthread attribute object  
  
  retVal = pthread_attr_init(&thread_attr); //Create the attribute
  if(retVal != 0)                         
    {
      perror("Attribute creation failed\n");
      exit(EXIT_FAILURE);
    }
  
  retVal = pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
  if(retVal != 0)                            //set the detached attribute  
    {
      perror("Setting detached attribute failed\n");
      exit(EXIT_FAILURE);
    }
 
  retVal = pthread_create(&a_thread,NULL,thread_function,(void *)message);
  if(retVal != 0)                            //create the thread
     {
      perror("Thread creation failed\n");
      exit(EXIT_FAILURE);
    }
  
  pthread_attr_destroy(&thread_attr);         //destroy the attribute object

  while(!thread_finished)                       
    {
      printf("Waiting for second thread to say it is finished...\n");
      sleep(1);
    }
  
  printf("Bye!\n");
  exit(EXIT_SUCCESS);
}
    
void *thread_function(void *arg)
{
  printf("Thread function is running. Argument was %s\n",(char *)arg);
  sleep(4);
  printf("Second thread finished, setting the flag and exiting now\n");
  thread_finished = 1;                         //set the finish flag and exit
  pthread_exit(NULL);                    
}

