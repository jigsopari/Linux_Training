#include <stdio.h>

int main()
{
   char buf[BUFSIZ];

   char bufr[8];

   setvbuf(stdout, buf, _IONBF, BUFSIZ);
   printf("Hello");
   read(0,bufr, 4);

   return 0;
}

