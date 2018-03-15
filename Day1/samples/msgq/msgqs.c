/*
 * sample program to show the usage of message queue - msgsnd
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
                                                
   if((msgqid = msgget(KEY,PERMS|IPC_CREAT)) < 0)     //create the message queue
      printf("server: can't get message queue, %s",strerror(errno));

   strcpy(mesg.mesg_data, "HELLO WORLD");
   mesg.mesg_type = 1L;                   //send messages of this type 
   mesg.mesg_len = strlen(mesg.mesg_data) + MESGHDRSIZE;

   if(msgsnd(msgqid,(char *)&(mesg.mesg_type),mesg.mesg_len,0) != 0)
   {
      printf("message send error, %s\n",strerror(errno));
      exit(1);
   }

   exit(0);
}
