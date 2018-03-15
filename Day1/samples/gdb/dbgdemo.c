/*
 * Example program to demonstrate use of gdb
 * B R Sahu
*/

#include <stdio.h>
#include <string.h>

int multiply(int x, int y);

int a;
int b;

int c;

struct tPerData
{
  char name[16];
  int age;
} PerData;


int main(int argc, char *argv[])
{
  a = 4;
  b = 5;

  c = multiply(a,b);
  printf("Res = %d\n", c);

  printf("Name = %s Age = %d\n", PerData.name, PerData.age);
  return 0;
}

int multiply(int x, int y)
{
   int z;

   z = x * y;

   PerData.age = 40;
   strcpy(PerData.name, "Stevens");

   return z;
}

