#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc,char **argv)
{
		if(argc<2)
		{
				printf("usage : %s command\n",argv[0]);
				exit(1);
		}

		signal(SIGQUIT,SIG_IGN);

		execlp(argv[1],argv[1],(char *)0);
		perror("ececlp() :");
		exit(2);
}
