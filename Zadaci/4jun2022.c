#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>

void uradi(char* imefajla,int dubina)
{
  if(dubina>3)
    return;
  DIR* dp;
  struct dirent* dirp;
  struct stat statbuf;
  int result;
  if((dp=opendir(imefajla))==NULL)
    return;
  while((dirp=readdir(dp))!=NULL)
  {
    if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
      continue;
    char tmp[1024];
    strcpy(tmp, imefajla);
    
    strcat(tmp, "/");
    strcat(tmp, dirp->d_name);
    //strcat(tmp, imefajla);
    //printf("%s\n",tmp);
    if ((result = stat(tmp, &statbuf)) == -1)
    {
      //printf("nesto");
      continue;
    }
    //printf("nesto");
    if(S_ISREG(statbuf.st_mode))
    {
      printf("%s\n",dirp->d_name);
      bool nesto = strstr(dirp->d_name, "log");
      printf("%d\n",nesto);
      if(strstr(dirp->d_name,"log")!=0 && statbuf.st_size<15360)
      {
        char rec[1000];
        sprintf(rec,"rm %s",dirp->d_name);
        system(rec);
      }
    }
    if(S_ISDIR(statbuf.st_mode))

      uradi(imefajla,dubina+1);
  }
  closedir(dp);
}
int main(int argc, char* argv[])
{
  
  uradi(argv[1],0);

  return 0;
}
