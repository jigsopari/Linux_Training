/*
 * using stand I/O libary functions
*/

#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	FILE* fptr = NULL;
	char cName[20], cAddr[20];
	char cAge[5];

	fptr = fopen ("A.txt", "r");
	if (NULL == fptr)
	{
		printf("\nError Opening File");
		exit(1);
	}
	fscanf(fptr,"%s\t%s %s", cName, cAddr, cAge);
	printf("\nData Read From File is :\n");
	printf("%s %s %s\n", cName, cAddr, cAge);
	fclose(fptr);
	return(0);
}
