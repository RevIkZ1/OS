#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct{
int number;
pthread_mutex_t mutex;
pthread_cond_t cond;
} thread_data;

void *countdown_thread(void *arg){
thread_data *data=(thread_data *)arg;
while(1){
pthread_mutex_lock(&data->mutex);
pthread_cond_wait(&data->cond, &data->mutex);
if(data->number==999)
{
pthread_mutex_unlock(&data->mutex);
break;
}
for(int i=0;i<=data->number;i++){
printf("countdown: %d\n",i);
sleep(2);
}
pthread_mutex_unlock(&data->mutex);
}
pthread_exit(NULL);
}

int main(){
pthread_t thread;
thread_data data;
data.number=0;
pthread_mutex_init(&data.mutex,NULL);
pthread_cond_init(&data.cond,NULL);
pthread_create(&thread,NULL,countdown_thread,&data);
while(1){
printf("Enter number(999 is exit):");
scanf("%d",&data.number);
pthread_mutex_lock(&data.mutex);
pthread_cond_signal(&data.cond);
pthread_mutex_unlock(&data.mutex);
if(data.number==999)
{
break;
}
}
pthread_join(thread,NULL);
pthread_mutex_destroy(&data.mutex);
pthread_cond_destroy(&data.cond);
return 0;
}
