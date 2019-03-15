#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
int main()
{
	int childret = 0;
	int wait_return;

	wait_return = wait(&childret);

	perror("perror : ");
	printf("wait_return : %d\n",wait_return);
}
