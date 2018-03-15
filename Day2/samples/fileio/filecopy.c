/*--------------------------------------------------------------*/
/* The following example copies one file to another.			*/
/* The second file is an uppercase version of the first file    */
/* Written by B R Sahu on 27/06/2002                            */
/*--------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main()

{
  int  hFile;
  int  hTempFile;
  int  retVal;
  int  i=0;
  int  IsUlet ,Islet;
  char buffer[4096];
  char buffer1[4096];
  char *ptr;
  char *ptr1;

  ptr=buffer;
  ptr1=buffer1;

  /*--- open the existing file------*/

  hFile=open("sleepdemo.c",O_RDONLY);

  if  (hFile< 0)
      printf("Error in opening the file\n");

  /*---Create an temporary file-------*/

  hTempFile= creat("Temp",400);
  if (hTempFile <0)
     printf("Error in creating the file\n");

  /*--------Read from the file --------------*/

  do
  {
    retVal =read(hFile,buffer,1);
    if (retVal <0)
        printf("Unable to read\n");
    Islet=isalpha(*ptr);              /* Check whether alphabet     */
    if(Islet!=0)
    {
       IsUlet = isupper(*ptr);        /*Check for case             */
       if (IsUlet==0)
           *ptr1 = toupper(*ptr);     /* convert to uppercase letter */
       else
           *ptr1=*ptr;
    }
  else
  {
    *ptr1=*ptr;
  }

  retVal= write(hTempFile,buffer1,1); /* write to the temporary file*/
  if (retVal < 0)
     printf("Error in writing\n");
  i++;
  }while(i<=4096);

  close(hTempFile);  /*Close the temp file */
  close(hFile);      /* Close the original file */

}
