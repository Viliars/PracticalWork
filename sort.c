/* Author: Michael Pritugin 241 gr
Development was cunducted from 28.10.2017 to 29.10.2017
Program "sort" betta version

Possible parameters:
+n: sort since n of a line
-m: merge all files
-o: using output file
-r: upside-down

Possible mistakes:
#3: error opening of the file
#2: error of closing of the file   
#1: file deletion error */

/* lib */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* MODE`s bytes */
#define PAR_R (1<<3)
#define PAR_N (1<<2)
#define PAR_M (1<<1)
#define PAR_O (1)
/* MODE`s mask */
#define MOD_R(a) (((a)>>3)&1)
#define MOD_N(a) (((a)>>2)&1)
#define MOD_M(a) (((a)>>1)&1)
#define MOD_O(a) ((a)&1)

/* debuf setting */
#define NO_DEBUG

/*prototypes*/
int cmp (const char* ,const char* );
void sort (char*, int , int );

/* main */
int main(int argc,char* argv[])
{
FILE* buf; /* bufer file for parament -m */
char c; /* for getchar() if -m is present */
FILE* f; /* bufer file */
int j=1; /* first counter */
char* str; /* string */
int mode=0; /* mode of sort */
int i=1; /* second counter */
int out=0; /* index output file */
int first; /* index first file */
int n=0; /* number in +n */

/* create MODE */
/* MODE=rnmo */
while(i<argc)
{
  if(argv[i][0]=='-')
    switch(argv[i][1])
     {
	case 'i': { printf("Author: Michael Pritugin 241 gr\n");
		  printf("Development was cunducted from 28.10.2017 to 29.10.2017\n");
		  printf("Program Sort betta version\n\nPossible parameters:\n");
		  printf("+n: sort since n of a line\n");
		  printf("-m: merge all files\n");
		  printf("-o: using output file\n");
		  printf("-r: upside-down\n\n");
		  printf("Possible mistakes:\n");
		  printf("#3: error opening of the file\n");
		  printf("#2: error of closing of the file\n");
		  printf("#1: file deletion error\n"); return 0; }
	case 'r': {mode|=PAR_R; break;}
	case 'm': {mode|=PAR_M; break;}
	case 'o': {mode|=PAR_O; i++; out=i; break; }
     }
  else if(argv[i][0]=='+') { str=malloc(sizeof(char)*(j-1));
                              while(argv[i][j]!='\0') { str=realloc(str,sizeof(char)*j);
                              str[j-1]=argv[i][j]; j++; } str=realloc(str,sizeof(char)*(j+1)); 
                              str[j]='\0'; n=atoi(str); mode|=PAR_N; free(str);}
  else { first=i; break; }
  i++;
}
/* end */

#ifdef DEBUG
printf("%s\n",argv[first]);
#endif

/* used sort */
	while(i<argc) { sort(argv[i],mode,n); i++;}
/* end sort */

#ifdef DEBUG
i=first;
while(i<argc) printf("%s\n",argv[i++]);
#endif
i=first;
/* -m */
if ( (buf = fopen("sort_output.txt","w")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
while(i<argc) { 
	if ((f = fopen(argv[i++],"r")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
	while((c=fgetc(f))!=EOF) fputc(c,buf);
	if(fclose(f)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
}
if(fclose(buf)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
/* -o */
if(MOD_O(mode)) 
{
	if ((buf = fopen("sort_output.txt","r")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
	if ((f = fopen(argv[out],"w")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
	while((c=fgetc(buf))!=EOF) fputc(c,f);
	if(fclose(f)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
	if(fclose(buf)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
}
else 
{
	if ((buf = fopen("sort_output.txt","r")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
	while((c=fgetc(buf))!=EOF) putchar(c);
	if(fclose(buf)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
}
if(remove("sort_output.txt")) { perror("FILE DELETION ERROR"); exit(1); }

#ifdef DEBUG
printf("%d %d %d %d\n",MOD_R(mode),n,MOD_M(mode),MOD_O(mode));
if(out!=0) printf("%s\n",argv[out]);
#endif

return 0;
}


/* direct cmp , if -r is absent */
int cmp_direct(const char* a1,const char* a2)
{
 int size1,size2,i=0;
   while(a1[i]!='\0') i++; size1=i;
    i=0;
   while(a2[i]!='\0') i++; size2=i;
     if(size1>size2) return 0;
     if(size1<size2) return 1;
    for(i=0;i<size1;i++) if(a1[i]>a2[i]) return 0;
 return 1;
}

/* invers cmp , if -r is present */
int cmp_invers(const char* a1,const char* a2)
{
 int size1,size2,i=0;
   while(a1[i]!='\0') i++; size1=i;
    i=0;
   while(a2[i]!='\0') i++; size2=i;
     if(size1>size2) return 1;
     if(size1<size2) return 0;
    for(i=0;i<size1;i++) if(a1[i]>a2[i]) return 1;
 return 0;
}

void sort (char* file,int mode,int n){
/* function cmp */
int (*cmp)(const char*,const char*)=NULL;
/* --------------------- */
  int k, i, j, kol;
  int count=1;
  char a1[1000]; 
  char a2[1000];
  FILE *f, *f1, *f2;
  FILE *buf,*bufer;
  kol = 0;
/* init  CMP */
if(MOD_R(mode)) cmp=cmp_invers; else cmp=cmp_direct;
/* prep for N */
   if ( (f = fopen(file,"r")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
   if ( (buf = fopen("buf.txt","w")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
   if ( (bufer = fopen("bufer.txt","w")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
   while(count<n) { 
     fscanf(f,"%s",a1); 
      fprintf(buf,"%s\n",a1);
       count++;
      }
      while ( !feof(f) ) {
      a1[0]='\0';
      fscanf(f,"%s",a1);
      fprintf(bufer,"%s\n",a1);
      }
    if(fclose(f)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
	if(fclose(buf)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
	if(fclose(bufer)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
   /* end */
  if ( (f1 = fopen("bufer.txt","r")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
  else {
    while ( !feof(f1) ) {
      fscanf(f1,"%s",a1);
      kol++;
#ifdef DEBUG
printf("%s\n",a1);
#endif
    }
    if(fclose(f1)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
  }
    kol--;
#ifdef DEBUG
   printf("kol=%d\n",kol);
#endif
   kol--;
  k = 1;
  /* BEGIN sort */
  while ( k < kol ){
    if((f = fopen("bufer.txt","r")) == NULL) { perror("ERROR OPEN FILE"); exit(3); }
    if((f1 = fopen("sort_buf1","w")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
    if((f2 = fopen("sort_buf2","w")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
    if ( !feof(f) ) fscanf(f,"%s",a1);
    while ( !feof(f) ){
      for ( i = 0; i < k && !feof(f) ; i++ ){
        fprintf(f1,"%s\n",a1);
        fscanf(f,"%s",a1);
      }
      for ( j = 0; j < k && !feof(f) ; j++ ){
        fprintf(f2,"%s\n",a1);
        fscanf(f,"%s",a1);
      }
    }
    /* first closes */
    if(fclose(f2)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
    if(fclose(f1)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
    if(fclose(f)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
     /* END closes */
    if((f = fopen("bufer.txt","w")) == NULL) { perror("ERROR OPEN FILE"); exit(3); }
    if((f1 = fopen("sort_buf1","r")) == NULL) { perror("ERROR OPEN FILE"); exit(3); }
    if((f2 = fopen("sort_buf2","r")) == NULL) { perror("ERROR OPEN FILE"); exit(3); }
    if ( !feof(f1) ) fscanf(f1,"%s",a1);
    if ( !feof(f2) ) fscanf(f2,"%s",a2);
      while ( !feof(f1) && !feof(f2) ){ /* 1 part */
      i = 0;
      j = 0;
         while ( i < k && j < k && !feof(f1) && !feof(f2) ) {
           if ( cmp(a1,a2) ) {
             fprintf(f,"%s\n",a1);
             fscanf(f1,"%s",a1);
             i++;
             }
           else {
             fprintf(f,"%s\n",a2);
             fscanf(f2,"%s",a2);
             j++;
             }
         }
      while ( i < k && !feof(f1) ) {
        fprintf(f,"%s\n",a1);
        fscanf(f1,"%s",a1);
        i++;
      }
      while ( j < k && !feof(f2) ) {
        fprintf(f,"%s\n",a2);
        fscanf(f2,"%s",a2);
        j++;
      }
    } /* end 1 part */

/* ......................... */
    while ( !feof(f1) ) {
      fprintf(f,"%s\n",a1);
      fscanf(f1,"%s",a1);
    }
    while ( !feof(f2) ) {
      fprintf(f,"%s\n",a2);
      fscanf(f2,"%s",a2);
    }
   /* second closes */
    if(fclose(f2)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
    if(fclose(f1)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
    if(fclose(f)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
    k *= 2;
  }
#ifdef DEBUG
printf("Where am I?\n");
#endif
/* merge fail BUF and BUFER */
 if ( (buf = fopen("buf.txt","a")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
  if ( (bufer = fopen("bufer.txt","r")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
   while ( !feof(bufer) ) {
      a1[0]='\0';
      fscanf(bufer,"%s",a1);
       fprintf(buf,"%s\n",a1);
    }
  if(fclose(bufer)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
  if(fclose(buf)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }

/* swap FILE and BUF */
    if ( (buf = fopen("buf.txt","r")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
     if ( (f = fopen(file,"w")) == NULL ) { perror("ERROR OPEN FILE"); exit(3); }
   while ( !feof(buf) ) {
         a1[0]='\0';
      fscanf(buf,"%s",a1);
       fprintf(f,"%s\n",a1);
    }
    if(fclose(f)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
    if(fclose(buf)==EOF) { perror("ERROR CLOSE FILE"); exit(2); }
/* delete BUFER`s files */
if(remove("buf.txt")) { perror("FILE DELETION ERROR"); exit(1); }
if(remove("bufer.txt")) { perror("FILE DELETION ERROR"); exit(1); }
if(remove("sort_buf1")) { perror("FILE DELETION ERROR"); exit(1); }
if(remove("sort_buf2")) { perror("FILE DELETION ERROR"); exit(1); }
} /*end SORT */


