#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


//ZADATAK SA DELJIVOM MEMORIJOM

union semun{
 int val;
 struct semid_ds *buf;
 ushort *array;
};
int main()
{
  pid_t nit;
  int memid;
 
  int sem1,sem2;
  union semun arg;
    char bafer[255];
      char *memorija;
  arg.val = 1;
  sem1 = semget(10001, 1, IPC_CREAT | 0666);
  semctl(sem1,0,SETVAL,arg);
  arg.val = 0;
  sem2 = semget(10002, 1, IPC_CREAT | 0666);
  semctl(sem2,0,SETVAL,arg);
  memid=shmget(10000,255*sizeof(char),IPC_CREAT|0666);
  struct sembuf lock = {0, -1, 0};
  struct sembuf unlock = {0, 1, 0};
  memorija = (char *)shmat(memid, NULL, 0);
  nit=fork();
  if(nit==0)
  {

   while(1)
    {
      semop(sem2,&lock,1);
      printf("HAHA %s",memorija);
      if(strcmp(memorija,"KRAJ")==0)
        exit(0);
      semop(sem1,&unlock,1);
    }
  }else{
  while(1)
  {
    semop(sem1,&lock,1);
    printf("Unesi tekst: ");
    fgets(bafer,255,stdin);
    bafer[strcspn(bafer,"\n")]=0;
    strcpy(memorija,bafer);
    semop(sem2,&unlock,1);
    printf("%s",memorija);
    if(strcmp(bafer,"KRAJ")==0)
      break;

    }
        sleep(1); 
        shmdt(memorija);
        shmctl(memid, IPC_RMID, NULL);
        semctl(sem1, 0, IPC_RMID);
        semctl(sem2, 0, IPC_RMID);
  }
  return 0;
}
