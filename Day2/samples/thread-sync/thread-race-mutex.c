/* An example program to create a Linux thread - protect race condition  */

#include <pthread.h>
#include <stdio.h>

#define N	1000000000
int count = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void* print_xs (void* unused)
{
    int i;

    for (i=0; i < N; i++)
    {
        pthread_mutex_lock( &mutex1 );
        count++; 
        pthread_mutex_unlock( &mutex1 );
    }

    return 0;
}

int main (int argc, char *argv[])
{
    pthread_t thread_id;
    int i;

    pthread_create (&thread_id, NULL, &print_xs, NULL);
    for (i=0; i < N; i++)
    {
        pthread_mutex_lock( &mutex1 );
        count++;
        pthread_mutex_unlock( &mutex1 );
    }
    pthread_join (thread_id, NULL);
    printf("%d\n", count);

    return 0;
}
