#include <stdio.h>
#include <unistd.h>

int main()
{
	if(fork() == 0)
		printf("child\n");
	else
		printf("parent\n");

	printf("both\n");
}
