#include <stdio.h>
#include <unistd.h>

int main()
{
	execl("/bin/date","wow",(char*)0);
	printf("Something wrong.\n");
}
