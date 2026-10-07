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
  int pipefd1[2],pipefd2[2];
  pipe(pipefd1);
  pipe(pipefd2);
  pid_t nit;
  srand(time(NULL));
  nit=fork();
  if(nit==0)
  {
    int broj;
    close(pipefd1[1]);
    close(pipefd2[0]);
    for(int i=0;i<5;i++)
    {
    int byt=read(pipefd1[0],&broj,sizeof(int));
    printf("Druga nit: %d\n",broj);
    if(broj%2==0)
    {
      write(pipefd2[1],&broj,sizeof(int));
    }
    }
    close(pipefd2[1]);
    close(pipefd1[0]);
    exit(0);
  }
  int broj=0;
  int br;
  close(pipefd1[0]);
  close(pipefd2[1]);
  for(int i=0;i<5;i++)
  {
    br=rand()%100;
    write(pipefd1[1],&br,sizeof(int));
    printf("Main: %d\n",br);

    int bro;
    if(br%2==0)
    {
      int byt=read(pipefd2[0],&bro,sizeof(int));
      broj++;
    }
  }
  wait(NULL);
  close(pipefd1[1]);
  close(pipefd2[0]);
  printf("Ukupan broj: %d",broj);
}

