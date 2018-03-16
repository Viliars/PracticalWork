/* Author: Michael Pritugin 241 gr
Development was cunducted from 04.11.2017 to 05.11.2017

Possible mistakes:
#4: ERROR CLOSE OUTPUT FILE
#3: OPEN OUTPUT FILE
#2: NO OUTPUT FILE
#1: error fork() */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/wait.h>
#define NO_DEBUG
int main(int argc, char * argv[])
{
  pid_t pid; /* pid child */
  char* ex="exit\n"; /* string of exit */
  int fd[2]; /* channel input-output */
  int ok[2]; /* channel mode */
  char str[41]; /* stirng */
  int mode; /* flag mode */
  int i=0; /* counter */
  FILE* out; /* output file */
if(argc<1) { perror("NO OUTPUT FILE"); exit(2); }
if((out=fopen(argv[1],"w"))==NULL) { perror("ERROR OPEN OUTPUT FILE"); exit(3); }
/* create 2 channels */
	pipe(fd);
	pipe(ok);
/* fork */
	if ((pid=fork())==-1) { perror("error fork()"); exit(1);}
/* child */
	if (pid==0)
		{
 	    close(ok[1]); close(fd[0]);
		mode=1;
		while(mode)
		{
			fgets(str, 42, stdin);
#ifdef DEBUG
printf("%s",str);
#endif
			write(fd[1], str, 42);
			read(ok[0],&mode, sizeof(int));
		i=0;
		if (mode) while(i++<10) fputc('+',out); fflush(out);
		}
		if(fclose(out)) { perror("ERROR CLOSE OUTPUT FILE"); exit(4); }
		return 0;
	}
/* parent */
	else
           {
		close(ok[0]); close(fd[1]);
			while(1)
			{
				read(fd[0],str,42);
#ifdef DEBUG
printf("%s",str);
#endif
				if (mode=strcmp(str,ex)) { i=0; while(str[i]!='\n') fputc(str[i++],out);}
 					fflush(out);
				write(ok[1],&mode, sizeof(int));	
				if (!mode) { wait(NULL); return 0; }
			}
			
		}
return 0;
}
