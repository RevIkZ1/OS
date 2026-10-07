#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
void* broji(void* arg)
{

  int br=*(int*)arg;

  pthread_mutex_lock(&mutex);
  for(int i=br;i>=0;i--)
  {
    printf("%d\n",i);
    sleep(1);
  }
  pthread_mutex_unlock(&mutex);
}
int main(int argc,char *argv[])
{

  pthread_t nit;
  while(1){
  char broj1[20];
  printf("Unesi broj: ");
  scanf("%s",broj1);
  printf("%s\n",broj1);
  if(!strcmp(broj1,"KRAJ"))
    return 0;
  else
  {
  int broj=atoi(broj1);
  pthread_create(&nit,NULL,broji,&broj);
    pthread_join(nit,NULL);
  }
  pthread_join(nit,NULL);
  }
  return 0;
}
