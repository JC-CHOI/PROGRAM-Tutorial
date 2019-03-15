#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	char buf[128];
	int size =0;

	while((size = read(0,buf,128)) > 0)
	{
		write(1,buf,size);
	}

	exit(0);
}
