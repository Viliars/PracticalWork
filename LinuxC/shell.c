/* Author: Michael Pritugin 241 gr
Development was cunducted from 12.11.2017 to 17.11.2017

MY SHELL

Value mode:
1) <
2) >
3) >>
4) &

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define N_DEBUG

/* for MODE`s BITE */
#define MODE_1(a) ((a)&1)
#define MODE_2(a) ((a)&2)
#define MODE_3(a) ((a)&3)
#define MODE_4(a) ((a)&4)
/* put bits mode */
#define PUT_1(a) ((a)|=1)
#define PUT_2(a) ((a)|=2)
#define PUT_3(a) ((a)|=3)
#define PUT_4(a) ((a)|=4)

#define PROVERKA(a) (((a)!='>')&&((a)!='&')&&((a)!='<')&&((a)!='\0'))

/* function that read from vector */
char** get_str(char* s){
#ifdef DEBUG
printf("I am at get_str\n");
#endif
  int i = -1, n = 0, len = strlen(s) + 1;
  char **str = malloc(sizeof(char*));
  *str = malloc(len);
  while(s[++i] != '\0')
	if(s[i] != ' ' && ((i == 0)?1:(s[i - 1] == ' ')))
	{
	  sscanf(s + i, "%s", str[n]);
	  str[n] = realloc(str[n], strlen(str[n]) + 1);
	  n++;
	  str = realloc(str, sizeof(char*)*(n + 1));
	  str[n] = malloc(len);
	}
free(str[n]);
str[n] = NULL;

#ifdef DEBUG
printf("I am close get_str\n");
#endif
return str;
}



/* ....................................................... MAIN ................................................................*/
int main(){
#ifdef DEBUG
printf("BEGIN\n");
#endif
  pid_t pid; /* pid */
  int **fd; /* channels */
  int i,count;
  char *buf; /* string for name of INPUT*/
  char **list, **str; /* string[] */
  char* ptr; /* string for name of OUTPUT */
  int iterator, mode; /* counter */
  int cin = dup(0); /* bufer for stdin */
  int cout = dup(1); /* bufer for stdout */
  FILE *f; /* if > or < */
  signal(SIGINT, SIG_IGN);
  list = malloc(sizeof(char*));
  *list = malloc(16);
/* zapusk infinity while */
  while(1){
	i = 0;
	iterator = 0;
	mode = 0;
	dup2(cin, 0);
	dup2(cout, 1);

/* ............................................................ TASK 1 ..................................................................................... */
	while((list[iterator][i++] = getchar()) != '\n')
	{
		if(!(i%16)) list[iterator] = realloc(list[iterator], i + 16);
		if(list[iterator][i-1] == '|')
		{
			list[iterator][i-1] = '\0';
			iterator++;
			i = 0;
			list = realloc(list, sizeof(char*)*(iterator + 1));
			list[iterator] = malloc(16);
		}
	}
list[iterator][i - 1] = '\0';
  i = 0;

/* END OF TASK 1 */

int prec;
/* if comand==exit||info */
if(iterator==0)  for(prec=0;prec<=iterator;prec++) {  if(strcmp(list[prec],"exit")==0) { 
printf("\n ......................................... EXIT ................................................\n"); exit(0); } 
if(strcmp(list[prec],"info")==0)
	 { printf("Author: Michael Pritugin 241 gr\n");
	   printf("Development was cunducted from 12.11.2017 to 17.11.2017\n");
	   printf("Program MyShell betta version\n\n");
	   printf("Possible mistakes:\n");
	   printf("#1: error FORK\n"); 
	   printf("#2: error NO INPUT FILE \n");
	   printf("#3: error OPEN FILE\n");
	   printf("#4: error CLOSE FILE \n");
		  exit(0);
		} } 

	/*............................................................. TASK 2 .................................................. */
  while(PROVERKA(list[iterator][i])) i++;
	count = i;
	while(list[iterator][i] != '\0')
	{
		if(list[iterator][i] == '<' && !(MODE_1(mode)))
		{
	
		  int j = i + 1;
		  buf = malloc(16);
		  while((buf[j-i-1] = list[iterator][j]) != '>' && buf[j-i-1] != '&' && buf[j-i-1] != '\0') if(!(++j % 16)) buf = realloc(buf, j + 16);
			buf[j-i-1] = '\0';
			buf = get_str(buf)[0];
			/* mode 1 create */
			PUT_1(mode);
#ifdef DEBUG
printf("MODE_1 = %d\n",MODE_1(mode));
#endif
			i = j;
		} else if(list[iterator][i] == '>' && !(MODE_2(mode)))
			{
			  int j = i + 1;
			  ptr = malloc(16);
			  while((ptr[j-i-1] = list[iterator][j]) != '<' && ptr[j-i-1] != '&' && ptr[j-i-1] != '\0') if(!(++j % 16)) ptr = realloc(ptr, j + 16);
			  ptr[j-i-1] == '\0';
			  ptr = get_str(ptr)[0];
		     	  /* mode 2 create */
			  PUT_2(mode);
#ifdef DEBUG
printf("MODE_2 = %d\n",MODE_2(mode));
#endif
			  i = j;
			} else
			{
				if(list[iterator][i] == '&' && !(MODE_4(mode))) PUT_4(mode); i++;
			}
		}
	/* END OF TASK 2 */

/* ........................................................ TASK 3 ............................................................................*/
		
		/* run if mode 2*/
		if(MODE_2(mode)){
#ifdef DEBUG
printf("MODE #2 - YES\n");
#endif
                        /* MODE 3 TUUUUUUUUUUUUUUUUUUUUUUUUUT */
			if(ptr[0] == '>')
				if((f = fopen(ptr+1,"a"))==NULL) { perror("ERROR OPEN FILE"); exit(3); }
			else
				if((f = fopen(ptr,"w"))==NULL) { perror("ERROR OPEN FILE"); exit(3); }
			dup2(fileno(f),1);
			if(fclose(f)!=0) { perror("ERROR CLOSE FILE"); exit(4); }
			free(ptr);
		}

	/* run if mode 1 */
		if(MODE_1(mode)){
#ifdef DEBUG
printf("MODE #1 - YES\n");
#endif
			/* proverka na sushestvovanie faila */
			/* 0 - fail sushestvuet */
			if(access(buf, 0)==-1) { perror("NO FILE INPUT"); exit(2); }
			if((f = fopen(buf,"r"))==NULL) { perror("ERROR OPEN FILE"); exit(3); }
                        dup2(fileno(f), 0);
			if(fclose(f)!=0) { perror("ERROR CLOSE FILE"); exit(4); }
			free(buf);
		}
		/* run if 4 mode */
		if(MODE_4(mode)){
#ifdef DEBUG
printf("MODE #4 - YES\n");
#endif
			if((pid = fork()) == -1) { perror("ERROR FORK"); exit(1); }
			if(pid){
				wait(NULL);
				continue;
			}
			if((pid = fork()) == -1) { perror("ERROR FORK"); exit(1); }
			if(pid) exit(0);
                        /* close signal SIGINT in CHILD*/
			signal(SIGINT, SIG_IGN);
			FILE *nul = fopen("/dev/null", "r");
			dup2(fileno(nul), 0);
		}
/* END OF TASK 3 */
/* TASK 4 */
		list[iterator][count] = '\0';
		iterator++;
		fd = malloc(sizeof(int*)*iterator);
		for(i = 0; i < iterator; i++){
			/* created int[2] for Iterator channels */
			fd[i] = malloc(2*sizeof(int));
			/* pipe channel */
			pipe(fd[i]);
#ifdef DEBUG
printf("I am in last FOR\n");
#endif
			if((pid = fork()) == -1) { perror("ERROR FORK"); exit(1); }
			if(!pid){
				if(i != 0) {
					/* swap stdin or stdout with channel */
					dup2(fd[i - 1][0], 0);
					close(fd[i - 1][0]);
				}
				if(i != iterator - 1)
					/* swap stdin or stdout with channel */
					dup2(fd[i][1], 1);
				close(fd[i][0]);
				close(fd[i][1]);
				str = get_str(list[i]);
				if(execvp(str[0], str) == -1) perror("Invalid command\n");
				/* if execvp dont run */
				exit(3);
			}
			if(i != 0) close(fd[i - 1][0]);
			close(fd[i][1]);
		}
		close(fd[i-1][0]);
#ifdef DEBUG
printf("I am waiting my children\n");
#endif
		/* wait all children */
		for(i = 0; i < iterator; i++)
			wait(NULL);
#ifdef DEBUGH
printf("I waited all my children\n");
#endif
		if(MODE_4(mode)) exit(0);
	}
/* END OF TASK 4 */
#ifdef DEBUG
printf("NORMAL END\n");
#endif
	return 0;
}
/* ................................................ END ............................................................*/
