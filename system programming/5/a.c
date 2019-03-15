#include <stdio.h>
#include <string.h>

int main()
{
	char a[100] = "a";
	char b[100] = "bcd";

	strcpy(a,b);

	printf("%s\n",a);

	return 0;
}
