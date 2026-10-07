#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
pthread_mutex_t mutex;
int br;
void* od0doN(void* arg)
{
  pthread_mutex_lock(&mutex);
  for(int i=0;i<=br;i++)
  {
    printf("Odbrojavam: %d\n",i);
    sleep(3);
  }
  pthread_mutex_unlock(&mutex);
}
int main(int argc,char *argv[])
{
  int broj;
  pthread_t nit;
  while(1){
  pthread_mutex_lock(&mutex);
  printf("Unesi broj: ");
  scanf("%d", &broj);
  br=broj;
    pthread_mutex_unlock(&mutex);
  if(br==99)
  {
  printf("Kraj");
  return 0;
  }
  else{
  pthread_create(&nit,NULL,od0doN,NULL);
  }
  pthread_join(nit,NULL);
  }
}

