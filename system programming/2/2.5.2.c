#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#define MAXLENGTH 256

void copyfile();

int main(int argc,char **argv)
{
	if(argc < 3)
	{
		fprintf(stderr,"Usage : %s in_file out_file \n",argv[0]);
		exit(-1);
	}
	copyfile(argv[1],argv[2]);

	exit(0);
}

void copyfile(char *source_file,char *target_file)
{
	int size =0;
	int fd1 =0, fd2 =0;
	char buf[MAXLENGTH];

	fd1 = open(source_file,O_RDONLY);
	fd2 = open(target_file,O_WRONLY | O_CREAT | O_TRUNC,0666);

	memset(buf,0,sizeof(buf));

	while((size = read(fd1, buf, MAXLENGTH)) >0)
		write(fd2,buf,size);

	close(fd1);
	close(fd2);
}
