#include <stdio.h>     
#include <stdlib.h>     
#include <string.h>     
#include <dirent.h>     
#include <sys/stat.h>   
#include <unistd.h>    
#include <sys/wait.h>   
#include <limits.h>     

void pretrazi(const char *putanja)
{
DIR *dir;
struct dirent *entry;
struct stat st;
char puna_putanja[PATH_MAX];

dir=opendir(putanja);
if(dir==NULL)
{ 
  perror("opendir");
  return;
}
while((entry=readdir(dir))!=NULL){
  snprintf(puna_putanja,PATH_MAX,"%s%s",putanja,entry->d_name);
  if(stat(puna_putanja,&st)==-1)
  {
    perror("stat");
    continue;
  }
  if(S_ISDIR(st.st_mode)){
    pretrazi(puna_putanja);
  }
  else if(S_ISREG(st.st_mode)){
  int len=strlen(entry->d_name);
  if(len>3 && strcmp(entry->d_name+len-3,".sh")==0){
    printf("Izvrsavam: %s\n",puna_putanja);
    pid_t pid=fork();
    if(pid==0)
    {
      execlp("sh","sh",puna_putanja,NULL);
    }
    else{
    wait(NULL);
    }
  }
  }
  closedir(dir);
}
}
int main(int argc, char *argv[])
{
    // Program mora imati tacno jedan argument – putanju direktorijuma
    if (argc != 2) {
        fprintf(stderr, "Upotreba: %s <direktorijum>\n", argv[0]);
        exit(1);
    }

    // Poziv funkcije za pretragu direktorijuma
    pretrazi(argv[1]);

    return 0;
}
