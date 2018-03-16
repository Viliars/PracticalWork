/* Author: Michael Pritugin 241 gr
Development was cunducted 10.11.2017 */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>

#define NO_DEBUG

/* variables */
 pid_t pid1;
 pid_t pid2;
 int begin,end;
 int fd[2];
 int sig;

void RW1(int sig)
{
signal(SIGUSR1,RW1);
read(fd[0],&sig,sizeof(int));
			sig++;
			if(sig>end) { printf("pid=%d : %d END\n",getpid(),sig); close(fd[0]); close(fd[1]); kill(getppid(),SIGUSR2); while(1) pause(); }
			printf("pid=%d : %d\n",getpid(),sig);
			write(fd[1],&sig,sizeof(int));
kill(pid2,SIGUSR1);
}


void RW2(int sig)
{
signal(SIGUSR1,RW2);
read(fd[0],&sig,sizeof(int));
			sig++;
			if(sig>end) { printf("pid=%d : %d END\n",getpid(),sig); close(fd[0]); close(fd[1]); kill(getppid(),SIGUSR2); while(1) pause(); }
			printf("pid=%d : %d\n",getpid(),sig);
			write(fd[1],&sig,sizeof(int));
kill(getppid(),SIGUSR1);
}

void RWF(int sig)
{
signal(SIGUSR1,RWF);
			read(fd[0],&sig,sizeof(int));
			sig++;
			if(sig>end) { printf("pid=%d : %d END\n",getpid(),sig); 
			close(fd[0]); close(fd[1]);
			kill(pid1,SIGKILL);
			kill(pid2,SIGKILL);
			while(wait(NULL)!=-1); exit(0); }
			
			printf("pid=%d : %d\n",getpid(),sig);
			write(fd[1],&sig,1);
kill(pid1,SIGUSR1);
}

void KILL_CH(int s){
 close(fd[0]); close(fd[1]);
 kill(pid1,SIGKILL);
 kill(pid2,SIGKILL);
 while(wait(NULL)!=-1); exit(0);
}


int main(int argc,char* argv[]){
/* begin */
	if(argc<2) { perror("NO ARGUMENTS"); exit(2); }
	begin=atoi(argv[1]);
	end=atoi(argv[2]);
	if(begin>end) { perror("ERROR INPUT DATA"); exit(3); }
	sig=begin;
/* pipes */
	pipe(fd);
/* end of pipes */
	pid2=fork();
	if(pid2==-1) { perror("ERROR fork()"); exit(3); }
/* son2 */
if(pid2==0)
{
	signal(SIGUSR1,RW2);
	while(1) pause();
}
else {
	pid1=fork();
	if(pid1==-1) { perror("ERROR fork()"); exit(3); }
/* son1 */
if(pid1==0)
  {
       signal(SIGUSR1,RW1);
	while(1) pause();
  }
/* father */
else
  {
	signal(SIGUSR1,RWF);
	signal(SIGUSR2,KILL_CH);
	write(fd[1],&sig,sizeof(int));
	printf("pid=%d : %d BEGIN\n",getpid(),sig);
	kill(pid1,SIGUSR1);
	while(1) pause();
	
  }
}
return 0;
}
