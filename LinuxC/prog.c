/* Author: Michael Pritugin 241 gr
Development was cunducted 06.11.2017 */

/* 
FD - channel father->son
FD2 - channel son-> father
OK - signal channel father->son
OK2 - signal channel son-father

			########### <-------- OK2 <-------- #########
			#	  #			    #       #
			#	  # <---- FD2 <------------ #	    #	 
			# FATHER  #      		    #  SON  #
			#         # ----> FD -------------> #	    #	
                        #	  #			    #	    #
			########### --------> OK ---------> #########
*/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#define NO_DEBUG

int main(int argc,char* argv[]){
/* variables */
	int fd[2]; /* channel father->son */
	int fd2[2]; /* channel son->father */
	int ok[2],ok2[2]; /* channels for flags */
  int i,j=0;
	char c; /* bufer char */
	char str[110]; /* STRING */
	char str2[110]; /* bufer STRING FOR REVERSE */
	int sig=1; /* flag */
	FILE* f,*buf; /* files */
/* begin */
	if(argc<1) { perror("NO FILE"); exit(2); }
	if((f=fopen(argv[1],"r"))==NULL) { perror("ERROR OPEN FILE"); exit(1); }
	if((buf=fopen("bufer_file.txt","w"))==NULL) { perror("ERROR OPEN FILE BUF"); exit(4); }
/* pipes */
	pipe(fd);
	pipe(fd2);
	pipe(ok);
	pipe(ok2);
/* end of pipes */
	pid_t pid;
	pid=fork();
	if(pid==-1) { perror("ERROR fork()"); exit(3); }
/* father */
if(pid!=0)
{
	close(fd[0]);
	close(fd2[1]);
	close(ok[0]);
	close(ok2[1]);
	while(1)
		{
			fgets(str,101,f);
			/* if end of file */
			if(feof(f)) 
				{ sig=0; write(ok[1],&sig,1); wait(NULL); 
					/* copy BUF FILE -> OUTPUT FILE */
					if(fclose(buf)) { perror("ERROR CLOSE FILE"); exit(3); }
					if(fclose(f)) { perror("ERROR CLOSE FILE"); exit(3); }
					if((buf=fopen("bufer_file.txt","r"))==NULL) { perror("ERROR OPEN FILE BUF"); exit(4); }
					if((f=fopen(argv[1],"w"))==NULL) { perror("ERROR OPEN FILE"); exit(1); }
					while((c=fgetc(buf))!=EOF) fputc(c,f);
					if(fclose(buf)) { perror("ERROR CLOSE FILE"); exit(3); }
					if(fclose(f)) { perror("ERROR CLOSE FILE"); exit(3); }
					remove("bufer_file.txt");
					/* end */
         	return 0; 
				}
			/* sending STR to son */
			write(fd[1],str,101);
			write(ok[1],&sig,1);
			if(feof(f)) { wait(NULL); fclose(buf); return 0; }
			read(ok2[0],&sig,1);
			read(fd2[0],str,101);
			fputs(str,buf);
		}
}
/* son */
else {
	close(fd[1]);
	close(fd2[0]);
	close(ok[1]);
	close(ok2[0]);
	while(1)
		{
			read(ok[0],&sig,1);
			/* if sig=0 -> exit */
			if(sig!=1) { return 0; }
			read(fd[0],str,101);
			i=0;
			/* reverse str */
			while(str[i]!='\n'&&str[i]!='\0') i++; i--;
			for(j=i;j>=0;j--) str2[j]=str[i-j];
			for(j=0;j<=i;j++) str[j]=str2[j];
			/* sending STR to father */
			write(fd2[1],str,101);
			write(ok2[1],&sig,1);
		}
}
return 0;
}
