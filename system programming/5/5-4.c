#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define LENGTH 200
int my_access(char *path,char **instruction,char *tmp)
{
	memset(tmp,0,LENGTH);
	
	strcpy(tmp,path);
	strcat(tmp,instruction[0]);
	
	return access(tmp,F_OK);
}

void tokenize(char **basket,char *commend)
{
	int seek=0,i_basket=0;
	char tok;
	
	while((tok=commend[seek]) != '\0')
	{
		if((seek == 0) && (tok != ' '))
			basket[i_basket++] = &commend[seek];

		else if((tok != ' ') && (commend[seek-1] ==' '))
			basket[i_basket++] = &commend[seek];
		
		seek++;
	}
	seek = 0;
	while((tok = commend[seek]) != '\0')
	{
		if(tok == ' ')
			commend[seek] = '\0';

		seek++;
	}
}
		
int main(int argc, char **argv)
{
	int i,index,pid,access_check=1;
	char tok,buf[LENGTH];
	char tmp[LENGTH];
	char *basket[LENGTH];
	char *path[LENGTH];

	
	while(1)
	{	
		fprintf(stderr, "@@@ ");
		fgets(buf,LENGTH,stdin);
		buf[strlen(buf)-1]='\0';

		memset(basket,0,LENGTH);
		tokenize(basket,buf);
		access_check=1;
		if(!basket[0])// situation only enter
			continue;
		else if(!strcmp(basket[0],"setpath"))
		{	
			for(i=0;i<3;i++)
			{
				if(!my_access(path[i],basket,tmp))
				{
					access_check++;
					if((pid = fork()) == -1)
					{	
						perror("fork() :");
						exit(0);
					}
					if(pid == 0)
					{
						execv(tmp,basket);
						exit(0);
					}
					break;
				}			
			}	
		}
		
		if(access_check==1)
		{
			printf("command not found\n");
			continue;
		}		
 		wait((int *)0);
	}
	return 0;
}
