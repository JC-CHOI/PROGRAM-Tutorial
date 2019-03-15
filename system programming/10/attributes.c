#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
void* threadFunc(void *arg)
{
	char *s = (char *)arg;
	printf("%s",s);
	return (void *)strlen(s);
}
int main(int argc,char **argv)
{
	pthread_t thr;
	pthread_attr_t attr;
	int s;

	if(pthread_attr_init(&attr) != 0)
			printf("error\n");
	if(pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED) != 0)
			printf("error\n");
	if(pthread_create(&thr,&attr,threadFunc,(void *)1) != 0)
			printf("error\n");
	if(pthread_attr_destory(&attr) != 0)
			printf("error\n");
}
