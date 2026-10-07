#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex,mutex1;
int brojac=0;
void* prvanit(void* arg)
{
    char *str=(char*)arg;
    pthread_mutex_lock(&mutex1);
    printf("%s",str);
    printf("%d",brojac);
    pthread_mutex_unlock(&mutex1);
    sleep(1);
}
void* druganit(void* arg)
{
    char *str=(char*)arg;
    pthread_mutex_lock(&mutex);
    printf("%s",str);
    pthread_mutex_unlock(&mutex);
        sleep(1);
}
int main(int argc, char *argv[])
{
  FILE *f1=fopen(argv[1],"r");
  FILE *f2=fopen(argv[2],"r");
  pthread_t nit1,nit2;
  char tekst1[255];
  char tekst2[255];
  pthread_mutex_init(&mutex,NULL);
  pthread_mutex_init(&mutex1,NULL);
  int brojac=0;
  while(fgets(tekst1,255,f1)!=NULL && fgets(tekst2,255,f2)!=NULL)
  {

    pthread_create(&nit1,NULL,prvanit,tekst1);    pthread_join(nit1,NULL);

    pthread_create(&nit2,NULL,druganit,tekst2);    pthread_join(nit2,NULL);

  }
}
