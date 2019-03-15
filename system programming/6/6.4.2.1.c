#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#define LOOP_COUNT 10

void sigint_signalhandler(int);

int main()
{
	int i=0;
	struct sigaction act, old_act;

	act.sa_handler = sigint_signalhandler;

	sigfillset(&act.sa_mask);

	sigaction(SIGINT,&act,&old_act);

	for(i=1; i<=LOOP_COUNT; i++)
	{
		printf("loop count [%d]\n",i);
		sleep(1);
	}

	sigaction(SIGINT,&old_act,(struct sigaction *)NULL);
	sleep(10);
	exit(0);
}
void sigint_signalhandler(int sig)
{
	if(sig == SIGINT)
		printf("SIGINT Receive!!\n");
}
