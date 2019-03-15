#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

void sigint_signalhandler(int);

int main()
{
	int size =0;
	char temp[100];

	signal(SIGINT,sigint_signalhandler);

	for(;;)
	{
		size = read(0,temp,100);
		write(1,temp,size);
	}
}
void sigint_signalhandler(int sig)
{
	if(sig == SIGINT)
	{
		printf("SIGINT Receive\n");
		exit(1);
	}
}
