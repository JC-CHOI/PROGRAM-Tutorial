#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define LENGTH 200
int my_access(char *path2,char **instruction,char *tmp)
{
	memset(tmp,0,LENGTH);
	
	strcpy(tmp,path2); 
	 strcat(tmp,instruction[0]);
	
	return access(tmp,F_OK);
}

void tokenize(char **basket,char *commend)
{
	int seek=0,i_basket=0;
	char tok,pre;
	
	while((tok=commend[seek]) != '\0')
	{
		if(seek == 0)
		{
			if(tok != ' ')
				basket[i_basket++] = &commend[seek];
		}
		else
		{
			pre = commend[seek-1];
			if( tok != ' ') 
			{
				if( (pre == ' ') || (pre  == '\0') )
					basket[i_basket++] = &commend[seek];
			}
			else if( tok == ' ') 
			{
				if( (pre != ' ') && (pre != '\0') )
					commend[seek] = '\0';
			}
		}
		seek++;
	}
}
int main(int argc, char **argv)
{
	int i,j=0,index,pid,access_check=1;
	char tok,buf[100];
	char *basket[LENGTH];
	char *path[10];
	char tmp[LENGTH];
	char *tmp2;
	struct sigaction act;
	
	memset(path,0,10);

	act.sa_handler = SIG_IGN;
	sigfillset(&act.sa_mask);
	sigaction(SIGINT,&act,(struct sigaction *)NULL);
	sigaction(SIGQUIT,&act,(struct sigaction *)NULL);
	while(1)
	{
		fprintf(stderr, "@@@ ");
		fgets(buf,LENGTH,stdin);
		buf[strlen(buf)-1]='\0';

		memset(basket,0,LENGTH);
		tokenize(basket,buf);

		if(!basket[0])// situation only enter
			continue;
		else if(!strcmp(basket[0],"exit"))
		{
			exit(0);
		}
		else if(!strcmp(basket[0],"setpath"))
		{
			strcat(basket[1],"/");
			tmp2 = malloc(sizeof(basket[1]));
			strcpy(tmp2,basket[1]);
			path[j++] = tmp2;				
		}
		else
		{
			access_check = 1;
			
			for(i=0;i<j;i++)
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

			if(access_check==1)
			{
				printf("command not found\n");
				continue;
			}		
 			wait((int *)0);
		}
	}
	return 0;
}
