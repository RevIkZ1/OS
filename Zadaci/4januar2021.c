#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void processdir(char* imefajla, int n, int m)//n velicina, m broj karaktera cele putanje
{
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
    char tmp[100];
    strcpy(tmp, imefajla);
    strcat(tmp, "/");
    strcat(tmp, dirp->d_name);
    if ((result = stat(tmp, &statbuf)) == -1)
    {
      continue;
    }
    
    if(S_ISREG(statbuf.st_mode))
    {
      if(statbuf.st_size<=n && strlen(tmp)<=m)
      {
        printf("Velicina fajla %ld\n i naziv %s\n",statbuf.st_size,tmp);
      }
    }
    if(S_ISDIR(statbuf.st_mode))
    {
      processdir(tmp,n,m);
    }
  }
  
  closedir(dp);
}
int main(int argc, char* argv[])
{
  int n=atoi(argv[2]);
  int m=atoi(argv[3]);
  processdir(argv[1],n,m);
  return 0;
}
