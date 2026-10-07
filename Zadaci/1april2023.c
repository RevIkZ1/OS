#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;
int buffer[10];

void* parnibrojevi(void* arg)
{
  pthread_mutex_lock(&mutex);
  for(int i=0;i<10;i=i+2)
  {
    buffer[i]=(arc4random_uniform(300));
  }
  pthread_mutex_unlock(&mutex);
}
void* neparnibrojevi(void* arg)
{
  pthread_mutex_lock(&mutex);
  for(int i=1;i<10;i=i+2)
  {
    buffer[i] = (arc4random_uniform(200)) + 300;
  }
  pthread_mutex_unlock(&mutex);
}

int main(int argc,char *argv[])
{
  int broj;
  pthread_t nit1,nit2;
  for(int j=0;j<5;j++)
  {
    int zbir=0;
    pthread_create(&nit1,NULL,parnibrojevi,NULL);
    pthread_create(&nit2,NULL,neparnibrojevi,NULL);
    pthread_join(nit1,NULL);
    pthread_join(nit2,NULL);
    for(int i=0;i<10;i++)
    {
      zbir=buffer[i]+zbir;
      printf("%d\n",buffer[i]);
    }
    if(zbir>2000)
    {
      printf("Jeste veca od 2000: %d\n", zbir);
    }
      else
    {
      printf("Nije veca od 2000: %d\n", zbir);
    }
  }
}
