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
int globzbir=0;
int zbirovi(int n) {
    int zbir = 0;
    if (n < 0) n = -n;
    while (n > 0) {
        zbir += n % 10;
        n /= 10;
    }
    printf("Zbir: %d\n",zbir);
    globzbir+=zbir;
    return zbir;
}


int main()
{
  key_t key=ftok("red",65);
  int msgid=msgget(key,0666|IPC_CREAT);
  pid_t p1;
  p1=fork();
  if(p1==0)
  {
    FILE *f=fopen("upisivanje.txt","w");
    struct poruka broj;
    while(1)
    {
      msgrcv(msgid,&broj,sizeof(int),1,0);
            if(broj.broj==0)
      break;
      printf("Broj koji je poslat: %d\n",broj.broj);

      fprintf(f,"Zbir brojeva je: %d %d",zbirovi(broj.broj),globzbir);
    }
    fclose(f);
    exit(0);
  }
  else
  {
    while(1)
    {
    struct poruka broj;
    printf("Unesi broj: ");
    broj.tip=1;
    scanf("%d",&broj.broj);

    if(broj.broj==0)
    {
      msgsnd(msgid,&broj,sizeof(broj.broj),0);
      msgctl(msgid, IPC_RMID, NULL);
      return 0;
    }
    else if((broj.broj>=100 && broj.broj<=999)||(broj.broj<=-100 && broj.broj>=-999))
    {
      msgsnd(msgid,&broj,sizeof(broj.broj),0);
    }
    else{
          printf("Nije unet odg broj\n");
    }
    }
  }
}
