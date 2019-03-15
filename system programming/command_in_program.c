#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int command(char *cmd)
{
	int chpid;
	int w, status;

	if((chpid = fork()) == 0)
	{
		execlp("/bin/sh","sh","-c",cmd,(char *)0);
		exit(127);
	}

	while((w=wait(&status)) != chpid && w != -1);

	return ((w != -1) ? (status >> 8) : -1);
}

int main()
{
	printf("%d\n",command("date > Date; cat Date"));
	printf("%d\n",command("date -x"));
}
