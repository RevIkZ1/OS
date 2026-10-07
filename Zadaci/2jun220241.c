#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
int broj=0;
int main(int argc,char *argv[])
{
  int pipeputanja[2];
  int piperec[2];
  int pipebroj[2];
  pid_t nit1,nit2;
  pipe(pipeputanja);
    pipe(piperec);
  pipe(pipebroj);
  if((nit1==fork())==0)
  { 
  for(int i=0;i<argc-2;i++)
  {
    close(pipeputanja[1]);
    close(piperec[1]);
    char putanja[255];
    char rec[255];
    int byt1=read(pipeputanja[0],&putanja,255);
    int byt2=read(piperec[0],&rec,255);
    FILE *f=fopen(putanja,"r");
    char linija[255];
    int brojac=0;
    printf("Ovo je rec: %s\n",rec);
    printf("Ovo je putanja: %s\n",putanja);
    printf("koji put: %d\n",i);
    //while(fgets(linija,255,f)!=NULL)
    {
      //if(strstr(linija,rec)!=NULL)
      {
        //write(pipefd23[1],&brojac,sizeof(int));
      }
     // brojac++;
    }
   // brojac=-1;
  //  write(pipefd23[1],&brojac,sizeof(int));
  }
  exit(0);
  }
  if((nit1==fork())==0)
  {
    /*close(pipefd23[1]);
    int br;
    int byt3=read(pipefd23[0],&br,sizeof(int));
    if(br==-1)
    {
      printf("Brojac je stigao do: %d",broj);
      return 0;
    }
    broj+=br;
    close(pipefd23[0]);*/
  }
  char putanja[255];
  strcpy(putanja,argv[1]);
  for(int i=2;i<argc;i++)
  {
    close(pipeputanja[0]);
    close(piperec[0]);
    char rec[255];
    strcpy(rec,argv[i]);
    printf("Upis reci %s\n",rec);
    write(pipeputanja[1],putanja,255);
    write(piperec[1],rec,255);
    close(pipeputanja[1]);
    close(piperec[1]);

    wait(NULL);
    wait(NULL);
  }
}
