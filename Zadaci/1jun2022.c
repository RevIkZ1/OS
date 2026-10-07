#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int buffer[255];
int brojac=0;

void* funkcija(void* arg)
{
  int sorter=0;
  for(int i=0;i<brojac;i++)
  {
    for(int j=i+1;j<brojac;j++)
    {
      if(buffer[i]<buffer[j])
      {
        sorter=buffer[i];
        buffer[i]=buffer[j];
        buffer[j]=sorter;
      }
    }
  }
  return NULL;
}

int main()
{
  FILE *fp;
  pthread_t threadID;
  fp=fopen("podaci.txt","r");
  while(fscanf(fp,"%d",&buffer[brojac])==1)
  {
    brojac++;
  }
  pthread_create(&threadID,NULL,funkcija,NULL);
  pthread_join(threadID, NULL);
  for(int i=0;i<brojac;i++)
  { 
    printf("Redosled: %d\n",buffer[i]);
  }
}
