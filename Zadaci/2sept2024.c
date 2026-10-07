#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 1000

int main(int argc, char *argv[]){
int pipefd[2];
pid_t child_pid;
if(pipe(pipefd)==-1){
perror("pipe");
return 1;
}
child_pid=fork();
if(child_pid==-1){
perror("fork");
return 1;
}
if(child_pid=0){
close(pipefd[1]);
int dest_fd=open(argv[2],O_WRONLY | O_CHEEAT | O_TRUNC, 0666);
if (dest_fd==-1)
{
perror("open destination file");
return 1;
}
char buffer[BUFFER_SIZE];
int bytes_read;
long long byte_count=0;
srand(time(NULL));
while((bytes_read=read(pipefd[0],buffer,BUFFER_SIZE))>0){
write(pipefd[1],buffer,bytes_read);
}
}else{
close (pipefd[0]);
int src_fd=open(argv[1], O_RDONLY);
if (src_fd==-1){
perror("open source file");
return 1;
}
char buffer[BUFFER_SIZE];
int bytes_read;
while((bytes_read=read(src_fd,buffer,BUFFER_SIZE))>0){
write(pipefd[1],buffer,bytes_read);
}
close(pipefd[1]);
close(src_fd);
wait(NULL);
}
return 0;
}


