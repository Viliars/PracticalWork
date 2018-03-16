/* Author: Michael Pritugin 241 gr
Development was cunducted 10.11.2017 */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
/* Q2 , Q4a , Q4b */
#define Q4b

pid_t pid; /* pid child */



void sig(int s){
printf("I am in SIG\n");
#ifdef Q4a
int i=0;
for(;i<300;i++) printf("%d ",i);
#endif
#ifdef Q4b
int i=0;
for(;i<30000;i++) printf("%d ",i);
#endif
}

#ifdef Q3
void ex(int s)
{ exit(0); }
#endif

#ifdef Q4b
void sig2(int s){
printf("\n\n\n\n\n\nI am in SUGUSR2\n\n\n\n\n");
}
#endif

#ifndef Q4b
void send(int s)
{
static int count=0;
count++;
if(count<5) signal(SIGALRM,send);
else { kill(pid,SIGKILL); return; }
kill(pid,SIGUSR1);
alarm(1);
}
#endif

#ifdef Q4b
void send(int s)
{
static int count=0;
count++;
if(count<7) signal(SIGALRM,send);
else { kill(pid,SIGKILL); return; }
if(count!=3) kill(pid,SIGUSR1);
else kill(pid,SIGUSR2);
alarm(1);
}
#endif

int main()
{
if ((pid=fork())==-1) { perror("error fork()"); exit(1); }
/* Q2 */
#ifdef Q2
  if (pid==0)
    {
        signal(SIGUSR1,sig);
	kill(getppid(),SIGALRM);
	while(1) pause();
    }
else
    {
	signal(SIGALRM,send);
	while(wait(NULL)!=-1);
    }
#endif
/* no work!!!!!! Q3 */
#ifdef Q3
  if (pid==0)
    {
        signal(SIGUSR1,ex);
	while(1) pause();
    }
else
    {
	signal(SIGCHLD,);
	kill(pid,SIGUSR1);
	while(1) pause();
    }
#endif

/* Q4a */
#ifdef Q4a
  if (pid==0)
    {
        signal(SIGUSR1,sig);
	kill(getppid(),SIGALRM);
	while(1) pause();
    }
else
    {
	signal(SIGALRM,send);
	while(wait(NULL)!=-1);
    }
#endif
/* Q4b */
#ifdef Q4b
  if (pid==0)
    {
        signal(SIGUSR1,sig);
	signal(SIGUSR2,sig2);
	kill(getppid(),SIGALRM);
	while(1) pause();
    }
else
    {
	signal(SIGALRM,send);
	while(wait(NULL)!=-1);
    }
#endif

return 0;
}
