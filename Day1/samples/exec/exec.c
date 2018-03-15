/*
 * Program demonstrating the use of execl()
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

extern int errno;

int main()
{
  char buf[50];
  int retVal;
  printf("Enter the path of Executable:");
  scanf("%s",buf);
  retVal = execl(buf,NULL);                 //replace the current process
  if(retVal < 0)                            //image with the new procees image
    printf("Error in exec: %s\n",strerror(errno));
  else
    printf("This line will not be printed\n");
  return 0;
}
 
