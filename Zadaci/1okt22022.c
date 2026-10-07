#include <stdio.h>      // printf, fgets
#include <stdlib.h>     // atoi, exit
#include <string.h>     // strcmp
#include <pthread.h>    // pthread_create, pthread_join
#include <unistd.h>     // sleep

int broj;
pthread_mutex_t mutex;

void* odbrojavanje(void* arg)
{
  int lokalni_broj;
  pthread_mutex_lock(&mutex);
  lokalni_broj=broj;
  pthread_mutex_unlock(&mutex);
  
  for(int i=lokalni_broj;i>=0;i--)
  {
    printf("%d\n",i);
    sleep(1);
  }
  return NULL;
}
int main()
{
  pthread_t nit;
  char unos[100];
  pthread_mutex_init(&mutex,NULL);
  while(1)
  {
    printf("Unesi ceo broj ili KRAJ: ");
    fgets(unos,sizeof(unos),stdin);
    //unos[strcspn(unos,"\n")]=0;
    if(strcmp(unos,"KRAJ")==0)
    break;
      broj=atoi(unos);
    pthread_create(&nit,NULL,odbrojavanje,NULL);
  pthread_join;
  }
  return 0;
}
