#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

long velicina=-1;
char minFile[1024];

void processdir(char* imefajla, int brojfajlova, int brojlinija)
{
  if(dubina>maxdubina)
    return;
  DIR* dp;
  struct dirent* dirp;
  struct stat statbuf;
  int result;
  if((dp=opendir(imefajla))==NULL)
  {
    return;
  }
  while((dirp=readdir(dp))!=NULL)
  {
    if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
      continue;
    char tmp[1024];

    printf("%s\n",tmp);
    strcat(tmp, "/");
    strcat(tmp, dirp->d_name);
    if ((result = stat(tmp, &statbuf)) == -1)
    {
      //printf("Neuspesno citanje podataka o objektu: %s\n", tmp);
      continue;
    }
    
    if(S_ISREG(statbuf.st_mode))
    {
      int broj=strlen(dirp->d_name);
      if(strcmp(dirp->d_name+broj-4,".txt")==0 && statbuf.st_size>1024)
      {
        if(velicina==-1||statbuf.st_size<velicina)
        {
          velicina=statbuf.st_size;
          strcpy(minFile,tmp);
        }
      }
    }
    if(S_ISDIR(statbuf.st_mode))
    {
      processdir(tmp,dubina+1,maxdubina);
    }
  }
  closedir(dp);
}

int main(int argc, char* argv[])
{
  int maxdubina=atoi(argv[2]);
  
  processdir(argv[1],0,maxdubina);
  if(velicina!=-1)
    printf("Najmanja datoteka je: %s i %ld bajta\n",minFile,velicina);
  else
    printf("Toga nema");
  return 0;
}
