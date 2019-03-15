#include <stdio.h>

int main()
{
		FILE *fpin, *fpout;
		char line[BUFSIZ];

		fpin = popen("who","r");
		fpout = popen("sort","w");

		while(fgets(line,BUFSIZ,fpin) != (char *)NULL)
		{
			fputs(line,fpout);
		}

		pclose(fpin);
		pclose(fpout);
}
