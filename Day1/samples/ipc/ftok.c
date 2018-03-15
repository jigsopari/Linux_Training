#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

int main(int argc, char *argv[])
{
  key_t key;

  if (argc != 2)
  {
    printf("Usage is: ftok <pathname>\n");
    exit(1);
  }

  key = ftok(argv[1], 0x57);
  printf("key : %d\n", key);

  exit(0);

}

