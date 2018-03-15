/*
 *
 * SourceName    : orphan.c                                       
 *
 * Description   : This program demonstrates how an orphan process is
 *                 created.
 *
 * Notes :                                                               
 *               To Compile The Program  : #gcc -o orphan orphan.c
 *               To Execute The Program  : #./orphan
*/

#include<stdio.h>

/* Start of main()   */
int main()
{
	int pid,i;

	pid=fork();
	if(pid==0)
	{
	  printf("I Am The Child. My Process ID Is: %d\n",getpid());
	  printf("My Parent Process Id Is         : %d\n",getppid());
	  sleep(20);        /*  Child is put to sleep so that the
				parent terminates  */
             
	  printf("I Am The Child Again. My Process ID Is: d\n",getpid());
	  printf("My Present Parent Process Id Is       : %d\n",getppid());
	  printf("Child Terminates......\n");
	}
	else
	{
	  sleep(5);
	  printf("I Am The Parent. My Process ID Is: %d\n",getpid());
	  printf("My Parent's Process Id Is        : %d\n",getppid());
	  printf("Parent Terminates....\n\n");
	}
}
