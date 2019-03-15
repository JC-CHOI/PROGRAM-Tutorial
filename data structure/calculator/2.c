#include <stdio.h>
#include <string.h>
int main()
{
	int a[100] = {12,3};
	char x[100] ;
	char s[100];

	memset(x,0,100);
	memset(s,0,100);
	printf("gogo : \n");
	fgets(x,100,stdin);
	x[strlen(x)-1] = '\0';

	strcat(s,x);
	

	printf("%s\n",s);

	printf("%d %d \n",a[0],a[1]);
	return 0;
}
