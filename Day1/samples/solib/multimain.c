#include <stdio.h>

extern int multiply(int a, int b);

int main()
{
  int r;

  r = multiply(4,5);
  printf("Result = %d\n", r);

  return 0;
}

