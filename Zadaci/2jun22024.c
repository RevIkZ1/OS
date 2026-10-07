#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N;

void* deljivi_sa_7(void* arg)
{
for(int i=0;i<=N;i++)
  if(i%7==0)
  {
      printf("Nit 1 je deljiva sa 7: %d\n",i);
  }
return NULL;
}
void* nije_deljivo_sa_7(void* arg)
{
for(int i=0;i<=N;i++)
  if(i%7!=0)
  {
      printf("Nit 2 nije deljiva sa 7: %d\n",i);
  }
return NULL;
}

int main(int argc, char* argv[])
{
if(argc!=2)
{
return 1;
}
N=atoi(argv[1]);
pthread_t t1,t2;
pthread_create(&t1,NULL,deljivi_sa_7,NULL);
pthread_create(&t2,NULL,nije_deljivo_sa_7,NULL);

pthread_join(t1,NULL);
pthread_join(t2,NULL);
return 0;
}
