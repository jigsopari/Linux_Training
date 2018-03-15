/*
 * simple thread - create and join
*/

#include <pthread.h>
#include <stdio.h>
#include <signal.h>

/* print x's to stderr. The parameter is unused. Does not return */

void* print_xs(void* unused)
{
  int i;
  pthread_t tid;

  printf("Thread Enter...\n");
  tid = pthread_self();
  printf("thread id = %u\n", tid);
  for (i = 0; i < 100; i++)
  {
    sleep(1);
    fputc('x', stderr);
  }
  printf("\n");
  printf("Thread Exit...\n");
  return NULL;
}

/* The main program */
int main()
{
  pthread_t thread_id;
  int i;
  /* Create a new thread. The new thread will run the print_xs function */
  pthread_create(&thread_id, NULL, &print_xs, NULL);
  printf("thread id = %u\n", thread_id);
  for (i = 0; i < 10; i++)
  {
    fputc('y', stderr);
    sleep(1);
  }
  printf("Waiting for the thread...\n");
  pthread_join(thread_id, NULL);
  printf("joined\n");
  return 0;
}
