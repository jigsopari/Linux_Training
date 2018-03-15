/*
 * makefile example: main.c 
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
  int c;
  int a=5;
  int b=4;

  c = multiply(a, b);
  printf("a = %d b = %d c = %d\n", a, b, c);

  return 0;
}
 

