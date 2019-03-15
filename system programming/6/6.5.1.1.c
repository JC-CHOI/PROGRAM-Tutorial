#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
	int pid =0,status =0;

	if( (pid = fork()) == -1)
	{
		perror("fork() : ");
		exit(1);
	}
	else if( pid ==0 )
	{
		execlp("rcv_signal","rcv_signal",(char *)NULL);
		perror("execlp() :");
	}
	else if( pid > 0 )
	{
		sleep(2);
		kill(pid, SIGINT);
		printf("[parent] : send SIGINT\n");

		wait(&status);
		printf("[parent] : child process is killed by parent \n");
	}

	exit(0);
}
