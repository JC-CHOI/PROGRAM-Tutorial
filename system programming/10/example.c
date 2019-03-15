#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
void *threadFunc(void *arg)
{
	char *s = (char *)arg;
	printf("%s",s);

	return (void *)strlen(s);
}
int main(int argc,char **argv)
{
	pthread_t t1;
	int res,s;

	if(pthread_create(&t1,NULL,threadFunc,"Hello world\n") != 0)
		printf("pthread_create error\n");

	printf("Message from main()\n");

	if(pthread_join(t1,(void *)&res) != 0)
		printf("pthread_join error\n");

	printf("Thread returned %d\n",(int)res);
	exit(EXIT_SUCCESS);
}
