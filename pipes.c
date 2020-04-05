
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define BUFFER_SIZE 50

int main(int para,char* files[])
{
int fd[2];
pid_t p_child;

char rbuff[BUFFER_SIZE];

pipe(fd);

if(para != 3)
{
printf("Please make sure that you have entered 2 parameters\n");
exit(1);
}
int fopen = open(files[1],0);
int copyfile = open(files[2],O_RDWR|O_CREAT|O_APPEND,0777);
if(fopen == -1||copyfile == -1)
{
printf("There is some ERROR\nFile is not found\n");
exit(1);
}
p_child = fork();
if(p_child == 0)
{
close(fd[1]);
while(read(fd[0],rbuff,sizeof(rbuff))>0);
{
write(copyfile,rbuff,strlen(rbuff)-1);
}
close(fd[0]);
close(copyfile);
}
else
{
close(fd[0]);
while(read(fopen,rbuff,sizeof(rbuff))>0);
{
write(fd[1],rbuff,sizeof(rbuff));
memset(rbuff,0,BUFFER_SIZE);
}
close(fd[1]);
close(fopen);
wait(NULL);
}
}

