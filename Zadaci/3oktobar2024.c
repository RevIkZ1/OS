#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
struct poruka{
  long tip;
  char recenica[255];
  int kraj;
};

int main()
{
  key_t key=ftok("red",65);
  int msgid=msgget(key,0666|IPC_CREAT);
  pid_t p1,p2;
  if(msgid == -1) { perror("msgget"); exit(1); }
  if((p1=fork())==0)
  {
    struct poruka red;
    FILE* f=fopen("velika.txt","r");
    while(fgets(red.recenica,255,f)!=NULL)
    {
      red.tip=1;
      red.kraj=0;
      msgsnd(msgid,&red,sizeof(red),0);
    }
    red.tip=1;
    red.kraj=1;
    msgsnd(msgid,&red,sizeof(red),0);
    fclose(f);
    exit(0);
  }
  if((p2=fork())==0)
  {
    struct poruka red;
    FILE* f=fopen("mala.txt","r");
    while(fgets(red.recenica,255,f)!=NULL)
    {
      red.tip=2;
      red.kraj=0;
      msgsnd(msgid,&red,sizeof(red),0);
    }
    red.tip=2;
    red.kraj=1;
    msgsnd(msgid,&red,sizeof(red),0);
    fclose(f);
    exit(0);
  }
  struct poruka red;
  FILE *f=fopen("velika_mod.txt","w");
  FILE *f1=fopen("mala_mod.txt","w");
  int brojac=0;
  while(1)
  {
    msgrcv(msgid,&red,sizeof(red),0,0);
    if(red.kraj==1)
    {
      brojac++;
      if(brojac==2)
      break;
    }
    if(red.tip==1 && red.kraj==0)
    for(int i=0;i<strlen(red.recenica);i++)
      fprintf(f,"%c",toupper(red.recenica[i]));
    if(red.tip==2 && red.kraj==0)
    for(int i=0;i<strlen(red.recenica);i++)
      fprintf(f1,"%c",tolower(red.recenica[i]));    
  }
  msgctl(msgid, IPC_RMID, NULL);
}
