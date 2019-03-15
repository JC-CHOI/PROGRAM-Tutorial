#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *thread(void *arg)
{
		char *ret;
		printf("thread() entered with argument '%s'\n",(char *)arg);
		if((ret = (char *)malloc(20)) == NULL)
		{
			perror("malloc() error");
			exit(2);
		}
		strcpy(ret,"This is a Test");
		pthread_exit(ret);
}
void main()
{
		pthread_t thid;
		void *rt;

		if(pthread_create(&thid,NULL,thread,"thread 1") != 0)
		{
				perror("pthread_create() error");
				exit(1);
		}
		if(pthread_join(thid,&rt) != 0)
		{
				perror("pthread_create() error");
				exit(3);
		}
		printf("thread exited with '%s'\n",(char *)rt);
		free(rt);
}

