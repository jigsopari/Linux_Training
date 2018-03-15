/*************************************************************************
 *                                                                       *
 *   SourceName         : udp_server.c                                   *
 *   Programmer         : B R Sahu                                       *
 *   Date               : 20/11/2003                                     *
 *-----------------------------------------------------------------------*
 *   Description                                                         *
 *   Sample UDP Server Program                                           *
 *   Notes                                                               *
 *   How To Compile : On command prompt give"gcc -o server udp_server.c",*
 *                                                                       *  
 ************************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h> 

#define LOCAL_SERVER_PORT 1500
#define MAX_MSG 100

int main(int argc, char *argv[]) 
{

    int sd, rc, n, cliLen;
    struct sockaddr_in cliAddr, servAddr;
    char msg[MAX_MSG];

    /* socket creation */
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd<0) 
    {
    	printf("Failed to open socket \n");
    	exit(1);
    }

    /* bind local server port */
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(LOCAL_SERVER_PORT);
    rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr));
    if(rc<0) 
    {
    	printf(" Failed to bind port number %d \n", LOCAL_SERVER_PORT);
        exit(1);
    }

    printf(" Server waiting for data on port %u\n", LOCAL_SERVER_PORT);

    while(1) 
    {
        memset(msg,0x0,MAX_MSG); /* setting the buffer to 0 */

        /* function for receiving messages */
        cliLen = sizeof(cliAddr);
        n = recvfrom(sd, msg, MAX_MSG, 0, 
			       (struct sockaddr *) &cliAddr, &cliLen);

        if(n<0) 
	{
            printf("Failed to receive data \n");
            continue;
        }
      
        /* display received message */
        printf("From %s: Message is : %s \n", inet_ntoa(cliAddr.sin_addr), msg);
    
      }/* end of while loop */

    return 0;
}


