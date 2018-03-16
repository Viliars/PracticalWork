#include<stdio.h>
#include<stdlib.h>
char* cin(FILE*,int*);
int cmpN(char*,long);
void cout(FILE*,char*);
void swap(FILE*,FILE*);
int main(int argc,char* argv[])
{
char* s;
long n;
FILE* f1;
FILE* buf;
int idn=0;
if(argc<2) { printf("ERROR\nNEED DATA\n"); exit(3); }
n=atol(argv[2]);
f1=fopen(argv[1],"r");
buf=fopen("buf.txt","w");
if(!f1) { printf("ERROR\nTO OPEN FILE %s\n",argv[1]); exit(3); }
if(!buf) { printf("ERROR\nTO OPEN FILE buf.txt\n"); exit(3); }
while(!idn) {
	s=cin(f1,&idn);
	if(cmpN(s,n)) cout(buf,s);
	free(s);
}
if(fclose(buf)) { printf("ERROR\nTO CLOSE FILE buf.txt\n"); exit(3); }
if(fclose(f1)) { printf("ERROR\nTO CLOSE FILE %s\n",argv[1]); }
buf=fopen("buf.txt","r");
f1=fopen(argv[1],"w");
if(!f1) { printf("ERROR\nTO OPEN FILE %s\n",argv[1]); exit(3); }
if(!buf) { printf("ERROR\nTO OPEN FILE buf.txt\n"); exit(3); }
swap(buf,f1);
if(fclose(buf)) { printf("ERROR\nTO CLOSE FILE buf.txt\n"); exit(3); }
if(fclose(f1)) { printf("ERROR\nTO CLOSE FILE %s\n",argv[1]); }
return 0;
}


void swap(FILE* f1,FILE* f2)
{
char c;
while((c=fgetc(f1))!=EOF){
fprintf(f2,"%c",c);
}
}

void cout(FILE* fil,char* str){
	fputs(str,fil);
	fputc('\n',fil);
}


char* cin(FILE* fil,int* val)
{
	char g;
	char* str;
	int i=0;
	int k=8;
	str=malloc(k*sizeof(char));
	while(((g=getc(fil))!='\n')&&(g!=EOF))
	{
		str[i++]=g;
		if(i>=k) {
			k+=8;
			str=realloc(str,k*sizeof(char)); }
	}
	if(g==EOF) (*val)=1;
	k++;
	str=realloc(str,k*sizeof(char));
	str[i]='\0';
	return str;
}

int cmpN(char* str,long n){
long i=0;
while(str[i]!='\0'){
	i++;
	if(i>=n) { return 0; }
}
return 1;
}
