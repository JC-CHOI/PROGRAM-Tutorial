#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char **argv)
{
	int child1, child2;
	int pid, status;

	if((child1 = fork()) == 0)
		execl("/bin/date","date",(char *)0);
	if((child2 = fork()) == 0)
		execl("/bin/date","date","-x",(char *)0);

	printf("parent : waiting for children \n");

	while((pid = wait(&status)) != -1)
	{
		if(child1 == pid)
			printf("parent : first child : %d\n",(status >>8));
		else if(child2 == pid)
			printf("parent : second child : %d\n",(status >>8));
	}

	printf("parent : all children terminated \n");
	exit(0);
}
