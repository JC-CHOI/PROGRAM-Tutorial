#include <stdio.h>
#include <pthread.h>
#define NTHREADS 10
int counter =0;

void *thread_function(void *dummyptr)
{
		printf("thread number %ld\n",pthread_self());
		counter++;
}
void main()
{
		pthread_t thread_id[NTHREADS];
		int i,j;
		for(i=0; i<NTHREADS;i++)
		{
				pthread_create(&thread_id[i],NULL,thread_function,NULL);
		}
/*		for(j=0; j<NTHREADS;j++)
		{
				pthread_join(thread_id[j],NULL);
		}*/
		printf("final counter value:%d\n",counter);
}

