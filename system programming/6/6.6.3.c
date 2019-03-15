#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

void handler(int);
	int i;

int main()
{
	struct itimerval it;
	struct itimerval ot;
	struct itimerval tt;
	int remain_time1,remain_time2;
	char *buf;

	it.it_value.tv_sec = 10;
	it.it_value.tv_usec = 0;
	
	it.it_interval.tv_sec = 5;
	it.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL,&it,NULL) == -1)
	{
		perror("setitimer");
		exit(1);
	}
	getitimer(ITIMER_REAL,&ot);
	buf = malloc(100000);
	getitimer(ITIMER_REAL,&tt);
	
	remain_time1 = ot.it_value.tv_sec - tt.it_value.tv_sec;
	remain_time2 = ot.it_value.tv_usec - tt.it_value.tv_usec;

	printf("%d sec, %d msec \n",(int)remain_time1,(int)remain_time2);
	
	it.it_value.tv_sec = remain_time1;
	it.it_value.tv_usec = remain_time2;

	signal(SIGALRM,handler);

	setitimer(ITIMER_REAL,&it,NULL);
	for(i=0; 1;i++)
	{;}

	return 0;
}

void handler(int sig)
{
	printf(" i = [%d]\n",i);
	exit(0);
}
	

				
