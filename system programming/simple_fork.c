#include <stdio.h>

int main()
{
	int pid =0, ppid =0;

	if((pid=fork()) == -1)
	{
		perror("fork() : ");
		exit(-1);
	}

	if(pid == 0)
	{
		pid = getpid();
		ppid = getppid();
		printf("\tProcess ID : %d,\t Parent Process ID: %d\n",pid,ppid);
		exit(0);
	}
	else
	{
		pid = getpid();
		ppid = getppid();
		printf("Process ID: %d,\tParent Process ID : %d\n",pid,ppid);
	//	wait((int *)0);
	}

	exit(0);
}
