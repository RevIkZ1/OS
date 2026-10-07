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
  p1=fork();

  if(p1==0)
  {
    FILE *f=fopen("prva.txt","r");
    struct poruka msg;
    msg.tip=1;
    while(fgets(msg.recenica,255,f)!=NULL)
    msgsnd(msgid,&msg,sizeof(msg.recenica),0);
    fclose(f);
    exit(0);
  }
    p2=fork();
  if(p2==0)
  {
  FILE *f=fopen("druga.txt","r");
    struct poruka msg;
    msg.tip=2;
    while(fgets(msg.recenica,255,f)!=NULL)
    msgsnd(msgid,&msg,sizeof(msg.recenica),0);
    fclose(f);
    exit(0);
  }
  struct poruka msg;
  FILE *f1=fopen("prva.txt","w");
  FILE *f2=fopen("druga.txt","w");
  int zavrseno=0;
  while(zavrseno<2)
  {
    if(msgrcv(msgid,&msg,sizeof(msg.recenica),0,IPC_NOWAIT)!=-1)
    {
      if (msg.tip == 1) {

                for (int i = 0; msg.recenica[i]; i++)
                    msg.recenica[i] = toupper(msg.recenica[i]);

                fputs(msg.recenica, f1);
            }

            if (msg.tip == 2) {

                for (int i = 0; msg.recenica[i]; i++)
                    msg.recenica[i] = tolower(msg.recenica[i]);

                fputs(msg.recenica, f2);
            }
    }
    else{
    if (waitpid(p1, NULL, WNOHANG) > 0) {
                p1 = -1;
                zavrseno++;
            }
            if (waitpid(p2, NULL, WNOHANG) > 0) {
                p2 = -1;
                zavrseno++;
            }
    }
  }
}
