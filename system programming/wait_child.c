#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#define EXIT_CODE 12


int main(int argc, char **argv)
{
	int pid,ret,status;

	if((pid=fork())==0)
	{
		printf("child :pid = %d ppid = %d exit_code=%d\n",getpid(),getppid(),EXIT_CODE);
		exit(EXIT_CODE);
	}

	printf("parent : waitng for child = %d\n",pid);
	ret = wait(&status);

	printf("parent: return value = %d, ",ret);
	printf(" child's staus = %x",status);
	printf(" and shifted=%x\n",(status >> 8));

	exit(0);
}
		
