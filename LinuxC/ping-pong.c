/* Author: Michael Pritugin 241 gr
Development was cunducted 06.11.2017 */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#define NO_DEBUG

int main(int argc,char* argv[]){
/* variables */
	int fd1[2],fd2[2],fd3[2]; /* channels */ 
  int i,j=0;
	char c; /* bufer char */
	char str[110]; /* STRING */
	char str2[110]; /* bufer STRING FOR REVERSE */
	int begin,end;
	int sig;
/* begin */
	if(argc<2) { perror("NO ARGUMENTS"); exit(2); }
	begin=atoi(argv[1]);
	end=atoi(argv[2]);
	if(begin>end) { perror("ERROR INPUT DATA"); exit(3); }
	sig=begin;
/* pipes */
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
/* end of pipes */
	pid_t pid1;
	pid_t pid2;
	pid1=fork();
	if(pid1==-1) { perror("ERROR fork()"); exit(3); }
/* son1 */
if(pid1==0)
{
	close(fd1[1]);
	close(fd2[0]);
	close(fd3[0]);
	close(fd3[1]);
	while(1)
		{
			read(fd1[0],&sig,sizeof(int));
			if(sig!=-1) sig++;
			if(sig>end) { printf("pid=%d : %d END\n",getpid(),sig); 
			sig=-1; write(fd2[1],&sig,sizeof(int)); read(fd1[0],&sig,sizeof(int)); write(fd2[1],&sig,sizeof(int));
			close(fd2[1]); close(fd1[0]); return 0; }
			if(sig==-1) { write(fd2[1],&sig,sizeof(int)); close(fd2[1]); close(fd1[0]); return 0; }
			printf("pid=%d : %d\n",getpid(),sig);
			write(fd2[1],&sig,sizeof(int));
		}
}
else {
	pid2=fork();
	if(pid2==-1) { perror("ERROR fork()"); exit(3); }
/* son2 */
if(pid2==0)
  {
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[1]);
	close(fd3[0]);
	while(1)
		{
			read(fd2[0],&sig,sizeof(int));
			if(sig!=-1) sig++;
			if(sig>end) { printf("pid=%d : %d END\n",getpid(),sig);  
			sig=-1; write(fd3[1],&sig,sizeof(int)); read(fd2[0],&sig,sizeof(int)); write(fd3[1],&sig,sizeof(int));
		        close(fd2[0]); close(fd3[1]); return 0; }
			if(sig==-1) { write(fd3[1],&sig,sizeof(int)); close(fd2[0]); close(fd3[1]); return 0; }
			printf("pid=%d : %d\n",getpid(),sig);
			write(fd3[1],&sig,1);
		}
  }
/* father */
else
  {
	close(fd1[0]);
	close(fd2[1]);
	close(fd2[0]);
	close(fd3[1]);
	write(fd1[1],&sig,sizeof(int));
	printf("pid=%d : %d BEGIN\n",getpid(),sig);
	while(1)
		{
			read(fd3[0],&sig,sizeof(int));
			if(sig!=-1) sig++;
			if(sig>end) { printf("pid=%d : %d END\n",getpid(),sig); 
			sig=-1; write(fd1[1],&sig,sizeof(int)); close(fd1[1]); close(fd3[0]); while(wait(NULL)!=-1); return 0; }
			if(sig==-1) { write(fd1[1],&sig,sizeof(int)); close(fd1[1]); close(fd3[0]); while(wait(NULL)!=-1); return 0; }
			printf("pid=%d : %d\n",getpid(),sig);
			write(fd1[1],&sig,1);
		}
  }
}
return 0;
}
