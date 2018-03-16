/* Author: Michael Pritugin 241 gr
Development was cunducted 08.11.2017 */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#define NO_DEBUG

int main(int argc,char* argv[]){
/* variables */
	int fd[2]; /* channel */ 
  int i,j=0;
	char str[200]; /* STRING */
	char str2[110]; /* bufer STRING FOR REVERSE */
/* pipe */
	pipe(fd);
/* end of pipes */
	pid_t pid;
	pid=fork();
	if(pid==-1) { perror("ERROR fork()"); exit(3); }
/* son1 */
if(pid!=0)
{
	close(fd[1]);
	j=read(fd[0],str2,200);
	wait(NULL);
	printf("\nLength STR=%d\n",j);
	printf("%s\n",str2); 
}
else
  {
	close(fd[0]);
	write(fd[1],"This is a test str, hello my father\nLuk,i am your father\nNOOOOOOOOOOOOOOOOOOO!!!!!",120);
	for(i=0;i<20;i++)
	printf("%d ",i);
	write(fd[1],"This is second str",30);
  }
return 0;
}
