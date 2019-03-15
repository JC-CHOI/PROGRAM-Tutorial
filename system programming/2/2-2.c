#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd_even,fd_odd,fd;
	char buf;
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
	if((fd_even = open(argv[2],O_WRONLY|O_CREAT|O_EXCL,0644)) < 0)
	{
		perror(argv[2]);
		close(fd);
		return -1;
	}
	if((fd_odd = open(argv[3],O_WRONLY|O_CREAT|O_EXCL,0644)) < 0)
	{
		perror(argv[3]);
		close(fd);
		close(fd_even);	
		return -1;
	}
	
	lseek(fd,0L,SEEK_SET);
	while(read(fd,&buf,1) > 0)
	{
		write(fd_odd,&buf,1);
		lseek(fd,1L,SEEK_CUR);
	}
	lseek(fd,1L,SEEK_SET);
	while(read(fd,&buf,1) > 0)
	{
		write(fd_even,&buf,1);
		lseek(fd,1L,SEEK_CUR);
	}
	return 0;
}
		
