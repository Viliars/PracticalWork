#include<stdio.h>
#include<stdlib.h>

void createFile(char*,int);
void mergeFile(char*,char*,char*);

int main(int argc,char* argv[])
{
if(argc<4) { printf("ERROR\nNEED NAME OF FILE\n"); exit(3); }
createFile(argv[1],20);
createFile(argv[2],15);
mergeFile(argv[1],argv[2],argv[3]);
return 0;
}

void mergeFile(char* input1,char* input2,char* output)
{
  int a,b;
  int ia=0,ib=0;
	FILE* finput1=fopen(input1,"r");	
	FILE* finput2=fopen(input2,"r");
	FILE* foutput=fopen(output,"w");
	if(!finput1) { printf("SYSTEM ERROR\nTO OPEN FILE %s\n",input1); exit(3); }
	if(!finput2) { printf("SYSTEM ERROR\nTO OPEN FILE %s\n",input2); exit(3); }
	if(!foutput) { printf("SYSTEM ERROR\nTO OPEN FILE %s\n",output); exit(3); }


	if(fscanf(finput1,"%d",&b)==EOF) ib++;
	if(fscanf(finput2,"%d",&a)==EOF) ia++;
	while(1)
	{
		if((ia>0)||(ib>0)) break;
		if(a>=b) { fprintf(foutput,"%d ",b); if(fscanf(finput1,"%d",&b)==EOF) ib++; 
			 }
		else { fprintf(foutput,"%d ",a); if(fscanf(finput2,"%d",&a)==EOF) ia++;	
		     }
	}
	if(ia>0) 
	{
		fprintf(foutput,"%d ",b);
		while(fscanf(finput1,"%d",&b)!=EOF) fprintf(foutput,"%d ",b);
	}
	if(ib>0)
	{
		fprintf(foutput,"%d ",a);
		while(fscanf(finput2,"%d",&a)!=EOF) fprintf(foutput,"%d ",a);
	}
	if(fclose(finput1)) { printf("SYSTEM ERROR\nTO CLOSE FILE %s\n",input1); exit(3); }
	if(fclose(finput2)) { printf("SYSTEM ERROR\nTO CLOSE FILE %s\n",input2); exit(3); }
	if(fclose(foutput)) { printf("SYSTEM ERROR\nTO CLOSE FILE %s\n",output); exit(3); }
}	
 
void createFile(char* name,int n)
{
        static int ind;
	int i;
	FILE* f1; 
	{
		f1=fopen(name,"w");
		if(!f1) { printf("SYSTEM ERROR\nTO OPEN FILE %s\n",name); exit(3); }
		if(n>0) 
		{
			for(i=0;i<n;i++)
			if(i%2==ind) fprintf(f1,"%d ",i);
		}
		if(fclose(f1)) { printf("SYSTEM ERROR\nTO CLOSE FILE %s\n",name); exit(3); } 
	}
	ind++;

}
