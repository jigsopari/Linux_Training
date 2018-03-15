/*
 * Program demonstrating shared memory
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define SHMKEY 1234
#define PERMS  0666

extern int errno;

int main()
{
  char *ptr;
  int shmid;
  
  shmid = shmget(SHMKEY,100,IPC_CREAT|PERMS);   //create the shared
  if(shmid < 0)                                             //memory segment
   {
    printf("Error in getting shared memory, %s",strerror(errno));
    exit(0);
   }
  
  ptr = shmat(shmid,0,0);     //attach it to the 
  if (ptr == 0)                //process
   {
    printf("Error in attaching shared memory, %s",strerror(errno));
    exit(0);
   }
  memcpy(ptr, "hello\n", 6);

  getchar();
  if(shmdt(ptr) < 0)    //detach the shared memory segment 
    printf("Error in detaching shared memory segment, %s\n",strerror(errno));
}

