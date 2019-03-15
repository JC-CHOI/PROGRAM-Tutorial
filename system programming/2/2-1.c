#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void copy_reverse(char *source, char *target)
{
	int offset;
	int size =0;
	int fd1,fd2;

	char c;

	if((fd1 = open(source,O_RDONLY)) < 0)
	{
		perror(source);
		return;
	}
	
	if((fd2 = open(target,O_WRONLY|O_CREAT|O_TRUNC,0644)) < 0)
	{
		perror(target);
		close(fd1);
		return;
	}
	
	offset = lseek(fd1,(off_t)-2,SEEK_END);
	do
	{	
		read(fd1,&c,1);
		write(fd2,&c,1);
		offset = lseek(fd1,(off_t)-2,SEEK_CUR);
	}while(offset != 0);

	read(fd1,&c,1);
	write(fd2,&c,1);

	close(fd1);
	close(fd2);

}
int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("give me argv");
		exit(-1);
	}

	copy_reverse(argv[1],argv[2]);

	exit(0);
}
		
