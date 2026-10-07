#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

int main(int arg,char* argv[])
{
  int pipefd[2];
  pid_t nit;
  pipe(pipefd);
  nit=fork();
  if(nit==0)
  {
    close(pipefd[1]);
    int fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buffer[1024];
    int br;
    while ((br = read(pipefd[0], buffer, sizeof(buffer))) > 0) 
    {
        write(fd, buffer, br);
    }
    close(pipefd[0]);
    exit(0);
  }
  else
  {

    int f=open(argv[1],O_RDONLY);
    close(pipefd[0]);
    char tmp[255];
    int broj=atoi(argv[2]);
    int nesto;
    while((nesto=read(f,tmp,broj))>0)
    {
      write(pipefd[1],tmp,nesto);
    }

    close(pipefd[1]);

  }
}
