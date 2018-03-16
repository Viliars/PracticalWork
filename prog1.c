#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
int i=0;
printf("my arguments are: %s %s\n",argv[1],argv[2]);
while(i<9){
	printf("my pid = %d\n",getpid());
        i++;
}
exit(7);
}


