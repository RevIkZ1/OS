#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void processdir(char* imefajla, int n, int m)//n broj fajlvoa, m broj redova
{
  DIR* dp;
  struct dirent* dirp;
  struct stat statbuf;
  printf("kurcina");
  int result;
  if((dp=opendir(imefajla))==NULL)
  {
    return;
  }
  int brojac=0;
  while(brojac<n && (dirp=readdir(dp))!=NULL)
  {
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
      char recenica[100];
      FILE *f=fopen(tmp,"r");
      int i=0;
      while(fgets(recenica,100,f)!=NULL && i<m)
      {
        printf("%s",recenica);
        i++;
      }
      brojac++;
      fclose(f);
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
