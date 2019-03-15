#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
int main()
{
	int childret = 0;

	if(fork() == 0)
		exit(23);

	wait(&childret);

	childret = childret>>8;

	printf("0x[%x]\n",childret);
}
