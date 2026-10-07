#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
int nesto=0;
int main(int argc,char *argv[])
{
int pipefd[2];
int pipefd1[2];
pid_t child_pid;
if(pipe(pipefd)==-1)
  {
  perror("pipe");return 0;
  }
if(pipe(pipefd1)==-1)
  {
  perror("pipe");return 0;
  }
child_pid=fork();
if(child_pid==0)
{
  close(pipefd[1]);
  close(pipefd1[0]);
  int brojevi[10];
  int brojac=0;
  int r=read(pipefd[0],brojevi,sizeof(brojevi));
  int vratibrojeve[10];

  for(int i=0;i<10;i++)
  {
    if(brojevi[i]%3==0)
    {
      vratibrojeve[brojac]=brojevi[i]+25;
      brojac++;
      nesto++;
    }
  }
  int vracenibrojevi[brojac];
    for(int i=0;i<brojac;i++)
  {
    vracenibrojevi[i]=vratibrojeve[i];
    printf("%d\n",vracenibrojevi[i]);
  }
  close(pipefd[0]);
  printf("%ld\n",sizeof(vracenibrojevi));
  int b=write(pipefd1[1],vracenibrojevi,sizeof(vracenibrojevi));
  close(pipefd1[1]);
}
else{
close(pipefd[0]);
close(pipefd1[1]);
int brojevi[10];
int vracenibrojevi[2];
for(int i=0;i<10;i++)
{
  brojevi[i]=(rand()%101)+200;
}

int r=write(pipefd[1],brojevi,sizeof(brojevi));
sleep(1);
int b=read(pipefd1[0],vracenibrojevi,sizeof(vracenibrojevi));
printf("Sta bre: %ld",sizeof(vracenibrojevi));
printf("%d",vracenibrojevi[0]);
for(int i=0;i<sizeof(vracenibrojevi)/4;i++)
{
  printf("Dada: %d\n",vracenibrojevi[i]);
}
close(pipefd[1]);
close(pipefd1[0]);
}
}
