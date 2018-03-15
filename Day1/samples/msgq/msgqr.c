/*
 * sample program to show the usage of message queue - msgrcv
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
int msgqid;

#define KEY            1234L
#define PERMS          0666
#define MAXMESGDATA    1024
#define MESGHDRSIZE    (sizeof(Mesg) - MAXMESGDATA)   //length of mesg_len  
                                                      //and mesg_type
typedef struct {                                 
  int mesg_len;                    //message length
  long mesg_type;                  //message type, must be greater than 0
  char mesg_data[MAXMESGDATA];     //message
}Mesg;
 

int main()
{
   Mesg mesg;                                //message structure 
   int n;

   if((msgqid = msgget(KEY,0)) < 0)          //create the message queue
      printf("server :: can't get message queue, %s",strerror(errno));

   mesg.mesg_type = 1L;                     //send messages of this type 
   mesg.mesg_len = strlen(mesg.mesg_data) + MESGHDRSIZE;


   n = msgrcv(msgqid,(char *)&(mesg.mesg_type),MAXMESGDATA,
                 mesg.mesg_type,0);
   if(n <= 0)
   {
        printf("message receive error, %s\n",strerror(errno));
        exit(1);
   }
   else
        printf("Received: %s\n",mesg.mesg_data);

  exit(0);
}
