#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char **argv)
{
	signal(SIGQUIT,SIG_IGN);

	execlp(argv[1],argv[1],(char *)0);
	perror("execlp() : ");
	exit(2);
}
