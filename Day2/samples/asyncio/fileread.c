/*
 * asynchronous I/O
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <aio.h>
struct aiocb aiocbp; /* asynchronous I/O control block */

char rbuf[64];

int main()
{
   int fd;
   int nr;

   fd = open("myfile.txt", O_RDONLY);
   printf("fd = %d\n", fd);
   aiocbp.aio_fildes = fd;
   aiocbp.aio_buf = rbuf;
   aiocbp.aio_nbytes = 16;

   nr = aio_read(&aiocbp);
   if (nr < 0)
     perror("File I/O: ");
   sleep(1);
   nr = aio_return(&aiocbp);
   printf("aio_return: rbuf=%s nr=%d\n", rbuf, nr);
   close(fd);

   return 0;
}

