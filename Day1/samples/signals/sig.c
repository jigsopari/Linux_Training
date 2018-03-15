/**************************************************************/
/*                                                            */
/*  This program demonstrate about signal handling            */
/*                                                            */ 
/**************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void  main(int, char**);
void  handle_ctrl_c(int);

void terminate(int);

void main(int argc, char** argv)
{
    signal(SIGINT, handle_ctrl_c);
    while (1);
    terminate(0);
}

void  handle_ctrl_c(int sig) 
{
    char ch;
    printf("\a\n"
           "Interrupted from console (control-c detected)\n"
           "Quit program? [Y/N] "
           );
    do{
       ch = getchar();
       if (ch != 'y' && ch != 'n') 
         {
         putchar('\a');
         }
       }while ( ch != 'y' && ch != 'n' );
    putchar(ch);
    putchar('\n');
    if (ch == 'y') 
      {
       terminate(1);
      }
      signal(SIGINT, handle_ctrl_c);
}

void terminate(int exit_code)
{
    printf("Exit Code = %d\n", exit_code);
    exit(exit_code);
}

/*---------------------End of the program-----------------------*/
