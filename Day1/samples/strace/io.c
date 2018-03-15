/*
 * program to be traced by strace
 */

int main()
{
  int fd;
  int nr;
  char buf[100];

  fd=open("io.c", 0644);
  nr = read(fd,buf,20);
  buf[nr]=0;
  printf("%s\n", buf);
  close(fd);

  return 0;
}

