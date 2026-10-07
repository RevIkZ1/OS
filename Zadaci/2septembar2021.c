#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int main()
{
  pid_t nit;
  int pd[2];
  srand(time(NULL));
  if (pipe(pd) == -1)
  {
    printf("Greska prilikom kreiranja prvog datavoda!\n");
  return -1;
  }
  nit=fork();
  if(nit==0)
  {
    close(pd[1]);
    for(int i=0;i<10;i++)
    {
      int broj;
      read(pd[0],&broj,sizeof(int));
      printf("Broj svakako %d\n",broj);
      if(broj%2==1)
        printf("Broj: %d\n",broj);
      else
        printf("PARAN BROJ\n");
    }
    close(pd[0]);
    exit(0);
  }
  close(pd[0]);
  for(int i=0;i<10;i++)
  {
    int broj=rand()%100;
    write(pd[1],&broj,sizeof(int));
  }
  wait(NULL);
  close(pd[1]);
}
