#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd1,fd2,fd;
	int size1,size2;
	char buf,buf2;
	if(argc < 3)
	{
		printf("give me argv");
		exit(-1);
	}
	if((fd = open(argv[1],O_RDONLY)) < 0)
	{
		perror(argv[1]);
		return -1;
	}
	if((fd1 = open(argv[2],O_RDONLY)) < 0)
	{
		perror(argv[2]);
		close(fd);
		return -1;
	}
	if((fd2 = open(argv[3],O_WRONLY|O_CREAT|O_EXCL,0644)) < 0)
	{
		perror(argv[3]);
		close(fd1);
		close(fd);	
		return -1;
	}
	
	while(read(fd,&buf,1) > 0 && read(fd1,&buf2,1) >0)
	{
		write(fd2,&buf,1);
		write(fd2,&buf2,1);
	}
	return 0;
}
		
