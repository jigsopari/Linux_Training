/*
 * synchronized I/O
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

char wbuf[] = {"12CDEFGHIJKLMNOP"};

int main()
{
   int fd;
   int nw;
   int arg=0;
   unsigned int fl;

   fd = open("myfile.txt", O_RDONLY);
   printf("fd = %d\n", fd);
   fl=fcntl(fd, F_GETFL, arg);
   printf("fl = %x\n", fl);
   fcntl(fd, F_SETFL, O_RDWR);
   fl=fcntl(fd, F_GETFL, arg);
   printf("fl = %x\n", fl);
   write(fd, wbuf, 16);
   close(fd);

   return 0;
}

