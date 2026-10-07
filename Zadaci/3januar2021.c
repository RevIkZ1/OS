#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>


int brojac = 0;

void handler_roditelj(int sig) {
    if (sig == SIGUSR2) brojac++;
}

void handler_dete(int sig) {

}

int main()
{
  pid_t p1,p2;
      fflush(stdout);
          fflush(stdin);
  signal(SIGUSR2, handler_roditelj);
  if((p1=fork())==0)
  {
    signal(SIGUSR1, handler_dete);

    for(int j=0;j<2;j++){
    pause();
    FILE *f=fopen("brojevi.txt","w");
    for(int i=0;i<10;i++)
    fprintf(f,"%d",rand()%10);
    fclose(f);
    kill(getppid(), SIGUSR2);
    }
    fflush(stdout);
    exit(0);
  }
  if((p2=fork())==0)
  {
    signal(SIGUSR1, handler_dete);


    for(int j=0;j<2;j++){
        pause();
        FILE *f1=fopen("slova.txt","w");
    for(int i=0;i<10;i++)
    {
      fprintf(f1,"%c",'a' + (rand() % 26));
    }
    fclose(f1);
    kill(getppid(), SIGUSR2);
    }
    fflush(stdout);
    exit(0);
  }

  sleep(1);
  while(1)
  {
    brojac = 0;
    kill(p1,SIGUSR1);
    kill(p2,SIGUSR1);
    while (brojac < 2) {
    pause(); 
    }
    brojac = 0;
    FILE *f=fopen("brojevi.txt","r");
    FILE *f1=fopen("slova.txt","r");
    int broj,cf1;
    while((cf1=fgetc(f1))!=EOF)
    {
      printf("%c",cf1);
    }
    while((broj=fgetc(f))!=EOF)
    {
      printf("%c ",broj);
    }
    printf("\n--- Kraj kruga ---\n");
    fflush(stdout);
    fclose(f);
    fclose(f1);
    sleep(1);
  }
  return 0;
}
