#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int);
int count ;
int main()
{
	signal(SIGINT,signal_handler);
	signal(SIGQUIT,signal_handler);

	while(1){}
}
void signal_handler(int sig)
{
	if(sig == SIGINT)
	{
		printf("control c pressed \n");
		count++;
	}
	if(sig == SIGQUIT)
	{
		printf("control + c = [%d]\n",count);
		exit(0);
	}
}

