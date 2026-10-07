#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
struct poruka {
    long tip;
    char recenica[255];
};

int main()
{
  key_t key=ftok("red",65);
  pid_t nit1,nit2;
  int msgid=msgget(key,0666|IPC_CREAT);
  if(msgid==-1)
  {
    exit(1);
  }
  if(fork()==0)
  {
   struct poruka rec;
   while(1)
    {
      msgrcv(msgid,&rec,sizeof(rec.recenica),1,0);

      if(strcmp(rec.recenica,"KRAJ")==0)
      {
        break;
      }
      else
        printf("%s\n",rec.recenica);
      rec.tip=2;
      msgsnd(msgid,&rec,sizeof(rec.recenica),0);
    }
    exit(0);
  }
  while(1)
  {
    struct poruka rec;
    rec.tip=1;
    printf("Skeniraj rec: ");
    scanf("%s",rec.recenica);
    if(strcmp(rec.recenica,"KRAJ")==0)
    {
      msgsnd(msgid,&rec,sizeof(rec.recenica),0);
      wait(NULL);
      break;
    }
    else
    {
      msgsnd(msgid,&rec,sizeof(rec.recenica),0);
    }
    msgrcv(msgid,&rec,sizeof(rec.recenica),2,0);
  }
  msgctl(msgid,IPC_RMID,NULL);
}
