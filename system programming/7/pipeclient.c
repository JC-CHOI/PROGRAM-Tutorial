#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

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
	char filename[100];

	strcpy(filename, argv[1]);
//	sprintf(msg.privfifo, "Fifo %d",getpid());
	if( (fd = open(filename,O_RDONLY)) == -1)
	{
		perror(filename);
		exit(0);
	}
	while( (n=read(fd,line,LINESIZE)) > 0)
	{
		if ((fdpub = open(PUBLIC, O_WRONLY)) == -1)
		{
			perror(PUBLIC);
			exit(2);
		}
		write(fdpub, line, n);


	}
	close(fd);
	close(fdpub);
	exit(0);
}
