#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>


struct poruka{
  long tip;
  int broj;
};

int funkcija(int broj)
{
  int zbir=0;
  if(broj<0)
    broj=-broj;
  while(broj>0)
  {
    zbir+=broj%10;
    broj=broj/10;
  }
  return zbir;
}
int main()
{
  fflush(stdout);
  fflush(stdin);
  
  key_t key=ftok("red",65);
int msgid = msgget(key, 0666);
if(msgid != -1)
    msgctl(msgid, IPC_RMID, NULL);  // briše stari red

/* sada napravi NOVI red */
msgid = msgget(key, 0666 | IPC_CREAT);
  pid_t p1;
  if((p1=fork())==0)
  {
    struct poruka msg;

    for(int i=0;i<10;i++)
    {
        msgrcv(msgid,&msg,sizeof(int),1,0);
      printf("Zbir brojeva je: %d\n",funkcija(msg.broj));

      }
  }
  else
  {
    struct poruka msg;

    for(int i=0;i<10;i++)
    {
      msg.tip=1;
      printf("Unesi broj:");
      scanf("%d",&msg.broj);
      msgsnd(msgid,&msg,sizeof(int),0);
      sleep(1);
    }
    msg.broj=0;
          msgsnd(msgid,&msg,sizeof(int),0);


  }
}
