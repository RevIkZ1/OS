#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
struct faj{
  char fajlovi[255];
  int velicina;
};
int i=0;
struct faj sorter[255];
void uporedi(char* imefajla)
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
    char tmp[1024];

    strcpy(tmp, imefajla);
    strcat(tmp, "/");
    strcat(tmp, dirp->d_name);
    if (( result = stat(tmp, &statbuf)) == -1)
    {
      continue;
    } 

    if(S_ISREG(statbuf.st_mode))
    {
      char* privremeno;
      if(statbuf.st_size>102400)
      {
        sorter[i].velicina=statbuf.st_size;
        strcpy(sorter[i].fajlovi,dirp->d_name);
        i++;
      }
    }
    if(S_ISDIR(statbuf.st_mode))
    {
      uporedi(tmp);
    }
    }
}
int main(int argc, char* argv[])
{
  
  uporedi(argv[1]);
  printf("Toga nema");
  for(int j=0;j<i;j++)
          for(int z=j+1;z<i;z++)
            if(sorter[j].velicina>sorter[z].velicina)
            {
              struct faj tm=sorter[z];
              sorter[z]=sorter[j];
              sorter[j]=tm;
            }
  for(int j=0;j<i;j++)
    printf("Naziv: %s\nVelicina: %d\n",sorter[j].fajlovi,sorter[j].velicina);
  return 0;
}
