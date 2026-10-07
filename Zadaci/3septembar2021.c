#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int otac=1;

void stavioca()
{
  otac=1;
}
void dete()
{
  FILE *f=fopen("datoteka.txt","r");
  char linija[255];
  while(fgets(linija,255,f)!=NULL)
  {
    printf("nikada\n");
    printf("%s\n",linija);
  }
  fclose(f);
  kill(getppid(),SIGUSR2);
}
void tato()
{
  FILE *f=fopen("datoteka.txt","w");
  for(int i=0;i<20;i++)
    fprintf(f,"%d",rand()%10);
  fclose(f);
  otac=0;
}

int main()
{
  pid_t nit1; 
  srand(time(NULL));
  nit1=fork();
  if(nit1 == 0) {
    signal(SIGUSR1, dete);
    while(1) {
        pause(); 

    }
}
  
  for(int i=0;i<20;i++)
  {
    otac=1;
    tato();
    kill(nit1,SIGUSR1);
    signal(SIGUSR2,stavioca);
    while(!otac)
    {
      pause();
    }
  }
  return 0;
}
