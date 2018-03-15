/*
 * shared library containing a function
 * gcc -c -fPIC dlfun.c
 * gcc -shared -o libtest.so dlfun.o
*/

#include <stdio.h>

int my_function()
{
  printf("Message from Dynamic Library Function\n");

  return 0;
}

