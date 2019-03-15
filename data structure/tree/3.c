#include <stdio.h>

int main()
{
	int x;

	char a='0';

	x = &a;

	printf("%d, %c \n",x,x);
	return 0;
}
