#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

void signalhandler(int);

int main()
{
	int size =0;
	char temp[100];

	signal(SIGINT,signalhandler);
	signal(SIGQUIT,signalhandler);

	for(;;)
	{
		size = read(0,temp,100);
	   	write(1,temp,size);
	}
	exit(0);
}
void signalhandler(int sig)
{
	if(sig==SIGINT)
	{
			printf("process terminate!!\n");
			exit(1);
	}
	else if(sig == SIGQUIT)
	{
			printf("process continue\n");
	}
}

