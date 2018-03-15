/*
 * program to demonstrate mlock
*/

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

#define MEMSIZE 32*1024*1024

int main()
{
  char *memory;

  printf("Hello\n");
  memory=malloc(MEMSIZE);
  mlock(memory, MEMSIZE);
  getchar();
  munlock(memory, MEMSIZE);
  free(memory);
  return 0;
}

