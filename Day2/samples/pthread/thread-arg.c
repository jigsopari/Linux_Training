/*
 * example prog to create thread, pass argument and return result 
*/

#include <pthread.h>
#include <stdio.h>

void* char_print (void* parameters)
{
  int *p;
  int x;

  p = (int *) parameters;

  printf("%d\n", *p);

  x = 20;
  pthread_exit(&x);

}

int main ()
{
  pthread_t thread1_id;
  void* result;

  int x=30;

  pthread_create (&thread1_id, NULL, &char_print, &x);
  /* Make sure the first thread has finished. */
  pthread_join (thread1_id, &result);
  printf("%d\n", *(int *)result);
  /* Now we can safely return. */
  return 0;
}

