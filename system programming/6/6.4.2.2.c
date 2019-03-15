#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

#define LOOP_COUNT 10

int main()
{
	int i=0;
	struct sigaction act, old_act;

	act.sa_handler = SIG_IGN;
	sigfillset(&act.sa_mask);
	sigaction(SIGINT,&act,&old_act);

	for(i=1;i<=LOOP_COUNT;i++)
	{
			printf("loop count [%d]\n",i);
			sleep(1);
	}
	sigaction(SIGINT,&old_act,(struct sigaction *)NULL);
	exit(0);
}
