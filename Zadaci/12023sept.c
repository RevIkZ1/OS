#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int buffer[10];
pthread_mutex_t mutex;
int spremno=0;
int gotovo=0;
void* funkcija(void* arg)
{
  while(gotovo==0)
  {
    pthread_mutex_lock(&mutex);
    if(spremno==0)
    {
      for(int i=0;i<10;i++)
      {
        buffer[i]=rand()%200;
        printf("Broj: %d\n",buffer[i]);
        }
      spremno=1;
    }
    pthread_mutex_unlock(&mutex);
  }
}

int main()
{
    srand(time(NULL));
pthread_mutex_init(&mutex, NULL);
  pthread_t threadID;
  pthread_create(&threadID,NULL,funkcija,NULL);
  int zbir=0;
  while(zbir<1000)
  {
    zbir=0;
    pthread_mutex_lock(&mutex);
    if(spremno==1)
    {
      for(int i=0;i<10;i++)
        zbir+=buffer[i];
      spremno=0;
    }
    if(zbir>1000)
    {
      printf("Zbir je veci%d",zbir);
      gotovo=1;
    }
    pthread_mutex_unlock(&mutex);
  }

  pthread_join(threadID,NULL);
}
