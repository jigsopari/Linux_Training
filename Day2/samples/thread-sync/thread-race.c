/* An example program to create a Linux thread - race condition */

#include <pthread.h>
#include <stdio.h>

#define N	1000000000
int count = 0;
void* print_xs (void* unused)
{
    int i;
    for (i=0; i < N; i++)
        count++; 
    return 0;
}

int main (int argc, char *argv[])
{
    pthread_t thread_id;
    int i;

    pthread_create (&thread_id, NULL, &print_xs, NULL);
    for (i=0; i < N; i++)
        count++; 
    pthread_join (thread_id, NULL);
    printf("%d\n", count);

    return 0;
}
