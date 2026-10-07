#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* stampanje(void* arg)
{
  int broj=*(int*)arg;
  printf("%d",broj);
  int sleep1=3;
  for(int i=0;i<broj;i++)
  {
        pthread_mutex_unlock(&mutex);
   if(i%7!=0)
    {
      pthread_mutex_lock(&mutex);
      printf("Druga nit broj:%d\n",i);
      pthread_mutex_unlock(&mutex);
    }
    }
}
int main(int argc,char *argv[])
{
  int broj;
  pthread_t threadID;
  broj=atoi(argv[1]);
  int sleep1=3;
  pthread_mutex_init(&mutex,NULL);
  pthread_create(&threadID,NULL,stampanje,&broj);
  printf("%d\n",broj);
  for(int i=0;i<broj;i++)
  {
      pthread_mutex_lock(&mutex);
      if(i%7==0)
      { 
      printf("Prva nit broj:%d\n",i);
      pthread_mutex_unlock(&mutex);
      }
    }
  return 0;
}
