#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

pthread_cond_t cv;
pthread_mutex_t lock;

void *thread(void *v)
{
	printf("[%ud] type unlock to unlock me \n",(int)pthread_self());
	pthread_mutex_lock(&lock);
	//printf("before wait\n");
	//sleep(10);
	pthread_cond_wait(&cv,&lock);

	printf("[%ld]i've been unlocked\n",pthread_self());
	pthread_mutex_unlock(&lock);
	return NULL;
}
void main()
{
	char cmd[1024];
	pthread_t *t;

	printf("type lock to run a thread that locks and wait\n");
	printf("type unlock to unlock the same thread.\n");

	while(fscanf(stdin,"%s",cmd) != EOF)
	{
			if(strcmp(cmd,"lock") ==0)
			{
					t = (pthread_t *)malloc(sizeof(pthread_t));
					pthread_create(t,NULL,thread,NULL);
			}
			else if(strcmp(cmd,"unlock") == 0)
			{
					pthread_mutex_lock(&lock);
					pthread_cond_signal(&cv);
					pthread_mutex_unlock(&lock);
			}
	}
}
