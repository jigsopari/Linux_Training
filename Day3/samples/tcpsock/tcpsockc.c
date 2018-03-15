/*
  Linux socket demonstration program, 
  client side
 */

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

/* define constants */
#define SERV_HOST_ADDR  "127.0.0.1" 
#define TRUE            1
#define FALSE           0   
#define MAX_LEN 	10000

extern int errno;

/* define global variables */
char msg[MAX_LEN]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

int length = 26;
int s; /* socket */
int clientsocket;
int socks[2];

int main(int argc, char *argv[], char *env)
{
    int rc;
    struct sockaddr_in myname;

/* initialize */

    printf("Client Socket API Demo Program\n");

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	 printf("socket error: %s\n", strerror(errno));
         exit(1);
    }
/* sockoption */

    memset(&myname, 0, sizeof(myname));
    myname.sin_family = AF_INET;
    myname.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    myname.sin_port =  5001;

/* connect */

    rc = connect(s, (struct sockaddr *)&myname, sizeof(myname));
    if (rc == -1) {
         printf("connect():error = %s\n", strerror(errno));
	 exit(1);
    }

/* main loop */

    printf("Sending Message\n");
    rc = send(s, msg, length, 0);

    if (rc == -1) {
         printf("send error = %s\n", strerror(errno));
    }
    printf("press enter to terminate.\n");
    getchar();

/* finalize */
    rc = close(s);
}

