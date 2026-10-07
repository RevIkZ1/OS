#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

int main()
{
int pipefd[2];
pid_t nit;
pipe(pipefd);
nit=fork();
if(nit==0)
{
  close(pipefd[1]);
  printf("Jel uslo");
  char putanja[255];
  char rec[255];
    printf("Jel uslo");
  int byt1=read(pipefd[0],putanja,255);
  int byt2=read(pipefd[0],rec,255);
  close(pipefd[0]);
  FILE *f=fopen(putanja,"r");
  char linija[255];
  int brojac=0;
  printf("Jel uslo");
  while(fgets(linija,255,f)!=NULL)
  {
    if(strstr(linija,rec)!=NULL)
    {
      printf("%d\n",brojac);
    }
    brojac++;
  }
}
else
{
  close(pipefd[0]);
  char putanja[255];
  char rec[255];
  printf("Unesi putanju do fajla:");
  scanf("%s",putanja);
  printf("Unesi rec:");
  scanf("%s",rec);
  printf("%s",putanja);
  printf("%s",rec);
  write(pipefd[1],putanja,255);
  write(pipefd[1],rec,255);
  close(pipefd[1]);
  printf("Cekanja");
  wait(NULL);
}
}
