#include <stdio.h> 
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h> 
#include <string.h> 
#include <ctype.h> 
#include <sys/wait.h> 
struct poruka{ long tip; char recenica[255]; };
int main()
{ key_t key=ftok("red",65);
  int msgid=msgget(key,0666|IPC_CREAT);
  pid_t p1,p2;
  if((p1=fork())==0)
  {
    FILE *f=fopen("sredjena.txt","a");
    struct poruka msg;
    while(1){
      msgrcv(msgid,&msg,sizeof(msg.recenica),1,0);
      for(int i=0;i<strlen(msg.recenica);i++){
        fprintf(f,"%c",tolower(msg.recenica[i]));
        fflush(f);
      }
    }
    fclose(f);
    exit(0);
  }
  if((p2=fork())==0)
  {
    FILE *f=fopen("sredjena.txt","a");
    struct poruka msg;
    while(1)
    {
      msgrcv(msgid,&msg,sizeof(msg.recenica),2,0);
      for(int i=0;i<strlen(msg.recenica);i++){
        fprintf(f,"%c",toupper(msg.recenica[i]));
        fflush(f);
      }
    }
    fclose(f);
    exit(0);
  }
  FILE *f=fopen("poruka.txt","r");
  struct poruka msg; 
while(fgets(msg.recenica,255,f)!=NULL)
  {
      msg.recenica[strcspn(msg.recenica,"\n")]=0; // uklanja \n
      msg.tip=1;
      msgsnd(msgid,&msg,strlen(msg.recenica)+1,0);
      msg.tip=2;
      msgsnd(msgid,&msg,strlen(msg.recenica)+1,0);
  }
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
  char recenica[255];
};

int main(){
  key_t key=ftok("red",65);
  int msgid=msgget(key,0666|IPC_CREAT);
  pid_t p1,p2;
  if((p1=fork())==0)
  {
    FILE *f=fopen("sredjena.txt","a");
    struct poruka msg;
    while(1){
      msgrcv(msgid,&msg,sizeof(msg.recenica),1,0);
      for(int i=0;i<strlen(msg.recenica);i++){
        fprintf(f,"%c",tolower(msg.recenica[i]));
      }
    }
    fclose(f);
    exit(0);
  }
  if((p2=fork())==0)
  {
    FILE *f=fopen("sredjena.txt","a");
    struct poruka msg;
    while(1)
    {
      msgrcv(msgid,&msg,sizeof(msg.recenica),2,0);
      for(int i=0;i<strlen(msg.recenica);i++){
        fprintf(f,"%c",toupper(msg.recenica[i]));
      }
    }
    fclose(f);
    exit(0);
  }
  FILE *f=fopen("poruka.txt","r");
  struct poruka msg;
  while(fgets(msg.recenica,255,f)!=NULL)
  {
      msg.recenica[strcspn(msg.recenica,"\n")]=0; // uklanja \n
      msg.tip=1;
      msgsnd(msgid,&msg,strlen(msg.recenica)+1,0);
      msg.tip=2;
      msgsnd(msgid,&msg,strlen(msg.recenica)+1,0);
  }
  fclose(f);
  return 0;
}
fclose(f);
return 0; }

