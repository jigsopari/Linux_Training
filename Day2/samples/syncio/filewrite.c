/*
 * synchronized I/O
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

char wbuf[] = {"ABCDEFGHIJKLMNOP"};

int main()
{
   int fd;
   int nw;

   fd = open("myfile.txt", O_CREAT|O_WRONLY|O_TRUNC|O_DSYNC, S_IWUSR);
   printf("fd = %d\n", fd);
   nw = write(fd, wbuf, 10);
   if (nw < 0)
     perror("File I/O: ");
   close(fd);

   return 0;
}

