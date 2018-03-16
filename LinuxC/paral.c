/*
Michael Pritugin 241gr
25.10.2017 */
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

/*SETTINGS*/
#define B

/*my MACRO*/
#define high(a) ((a>>8)&0xFF)
#define low(a) ((a)&0xFF)

int main(int argc,char* argv[])
{
pid_t p1,p2;
int st;
int st1,st2;
int system_st1,system_st2;
int pid1,pid2;
if(argc<6) { printf("ERROR\n"); exit(EXIT_FAILURE); }
#ifdef A
if((p1=fork())==-1) {perror("fork"); exit(3); }
if(p1==0)
{
execl(argv[1],argv[1],argv[2],argv[3],NULL);
perror("prog1");
}
else {
if((p2=fork())==-1) { wait(&st); perror("fork"); exit(3); }
if(p2==0)
{
execl(argv[4],argv[4],argv[5],argv[6],NULL); }
perror("prog2"); 
}
pid1=wait(&st);
if(WIFEXITED(st)!=0) { st1=high(st); system_st1=low(st); }

pid2=wait(&st);
if(WIFEXITED(st)!=0) { st2=high(st); system_st2=low(st); }
#endif
#ifdef B
if((p1=fork())==-1) { perror("fork"); exit(3); }
if(p1==0)
{
execl(argv[1],argv[1],argv[2],argv[3],NULL); }
else {
pid1=wait(&st);
if(WIFEXITED(st)!=0) { st1=high(st); system_st1=low(st); }
if((p2=fork())==-1) { perror("fork"); exit(3); }
if(p2==0)
{
execl(argv[4],argv[4],argv[5],argv[6],NULL); }
else 
{pid2=wait(&st);
if(WIFEXITED(st)!=0) { st2=high(st); system_st2=low(st); }
}
}
#endif
printf("..............\n");
if(system_st1==0) 
printf("PID = %d :\nStatus = %d\n",pid1,st1);
else printf("PID = %d :\nStatus = SYSTEM_ERROR\n",pid1);
if(system_st2==0)
printf("PID = %d :\nStatus = %d\n",pid2,st2);
else printf("PID = %d :\nStatus = SYSTEM_ERROR\n",pid2);
return 0;
}

