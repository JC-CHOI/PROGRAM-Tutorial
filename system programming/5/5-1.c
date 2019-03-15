#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()

{
	int pid=0,status=0;
	char *argv[] = {"/bin/ls","-l",(char *)0};
	if((pid = fork()) == -1)
	{
		perror("fork() : ");
		exit(-1);
	}

	if(pid == 0)
	{
		execv("/bin/ls",argv);
		exit(0);
	}

	wait(&status);
	
	status = status >> 8;
	if(status == 0)
		printf("exit success\n");
	else if
		printf("exit by signal\n");
	else
		printf("exit failed \n");

	return 0;
}
