#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

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

	mknod(PUBLIC, S_IFIFO|0666,0);
loop:
	if( (fdpub = open(PUBLIC, O_RDONLY) ) == -1)
	{
		perror(PUBLIC);
		exit(1);
	}
	while(read(fdpub, (char *)&msg, sizeof(msg) ) >0)
	{
		if( (fd=open(msg.filename,O_RDONLY) ) == -1)
		{
			perror(msg.filename);
			break;
		}
		for( i=0; i<NUMTRIES ; i++)
		{
			if( (fdpriv = open(msg.privfifo, O_WRONLY|O_NDELAY) ) == -1)
					sleep(1);
			else break;
		}
		if( fdpriv == -1)
		{
			perror(msg.privfifo);
			break;
		}
		while( (n=read(fd,line,LINESIZE)) > 0)
				write(fdpriv,line,n);
		close(fd);
		close(fdpriv);
	}
	close(fdpub);
	goto loop;
}
