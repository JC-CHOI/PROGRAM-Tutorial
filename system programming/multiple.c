#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	if(fork() == 0)
		execl("/bin/echo","echo","this is","message one",(char *)0);
	if(fork() == 0)
		execl("/bin/echo","ehco","this is","message two",(char *)0);

	printf("parent: waiting for children \n");

	while(wait((char *)0) != -1);

	printf("parent : all children terminated\n");
	exit(0);
}
