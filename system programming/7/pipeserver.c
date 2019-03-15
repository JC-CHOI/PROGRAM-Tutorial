#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <sys/wait.h>
#include <unistd.h>

#define PUBLIC "Public"
#define LINESIZE 512
#define NUMTRIES 3

struct message
{
	char privfifo[15];
	char filename[100];
};

int main(int argc, char **argv)
{
	int fdpub, fdpriv, fd;
	struct message msg;
	int n, i;
	char line[LINESIZE];

	char buf[LINESIZE];
	mknod(PUBLIC, S_IFIFO|0666,0);
loop:
	if( (fdpub = open(PUBLIC, O_RDONLY) ) == -1)
	{
		perror(PUBLIC);
		exit(1);
	}
	sleep(5);
	system("ls -l");
	while((n=read(fdpub, buf, sizeof(buf)) ) >0)
			write(1,buf,n);
	
	close(fdpub);
	goto loop;
}
