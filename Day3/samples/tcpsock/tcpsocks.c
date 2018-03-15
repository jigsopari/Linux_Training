/*******************************************************
 *                                                     *
 *  Linux socket demonstration program                 *
 *  method - server side                               *
 *                                                     *
 *******************************************************/
 
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
  
#define TRUE             1
#define FALSE            0   

extern int errno;

/* define constants */
#define MAX_LEN 10000

/* define global variables */

char msg[MAX_LEN];
int length = 0;
char temp[MAX_LEN];
int s;  /* socket */
int clientsocket;
int socks[2];

int main(int argc, char *argv[], char *env)
{
   int i;
/* initialize */
   printf("Server Socket API Demo Program\n");

   {
   int rc;
   struct sockaddr_in myname;
   struct sockaddr clientaddress;
   int addrlen;
   if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
   {
      printf("Socket error %s\n",strerror(errno));
      exit(1);
   }

/* bind */

   memset(&myname, 0, sizeof(myname));
   myname.sin_family = AF_INET;
   myname.sin_addr.s_addr = INADDR_ANY;
   myname.sin_port =  5001;

   rc = bind(s, (struct sockaddr *)&myname, sizeof(myname));
   if (rc == -1) 
   {
      printf("bind error = %s\n",strerror(errno));
      exit(1);
   }

/* listen */
   rc = listen(s, 2);
   printf("waiting connection\n");

/* accept */
   addrlen = sizeof(clientaddress); 
   clientsocket = accept(s, &clientaddress, &addrlen);
   printf("clientsocket=%d\n",clientsocket);
   printf("accept\n");
   socks[0] = clientsocket;
   }

/* main loop */

   printf("start receive\n");
   {
	   int len;
           len = recv(clientsocket, temp, MAX_LEN, 0);
           temp[len] = 0;
           printf("[");                        
           printf("%s",temp);
           printf("]\n");
   };
   printf("press enter to terminate.\n");
   getchar();

/* finalize */

   {
   int rc;
   rc = close(clientsocket);
   rc = close(s);
   }
   return 0;
}

