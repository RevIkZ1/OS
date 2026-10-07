#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct poruka{
  long tip;
  int broj;
};
int brojac=0;
int main()
{
  key_t key=ftok("red",65);
  int msgid = msgget(key, 0666 | IPC_CREAT);
  pid_t p1;
  p1=fork();
  if(p1==0)
  {
    struct poruka brojevi;
    while(1)
    {
      msgrcv(msgid, &brojevi, sizeof(int), 1, 0);

      if(brojevi.broj==0)
      {
        printf("Ukupno unetih brojeva: %d",brojac);
        break;
      }
      else{
        printf("Znak %c\n",brojevi.broj);
        brojac++;
      }
    }
  }
  else
  {
    while(1)
    {
      struct poruka broj;
      broj.tip=1;
      printf("Unesi broj:");
      scanf("%d",&broj.broj);
      printf("\n");
      fflush(stdin);
            fflush(stdout);
      if(broj.broj==0)
      {
          msgsnd(msgid,&broj,sizeof(broj.broj),0);
          msgctl(msgid, IPC_RMID, NULL);
          return 0;
      }
      else{
      msgsnd(msgid,&broj,sizeof(broj.broj),0);
      }
      sleep(1);
    }
  }
}
