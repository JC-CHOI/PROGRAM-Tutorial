#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#define LENGTH 200
int j;
void avoid_slash_overlap(char *array)
{
	char tok;
	char shift[LENGTH];
	int i=0,j=0;

	while( (tok = array[i]) != '\0')
	{
		if( i == 0)
		{
			shift[j++] = tok;
		}
		if( tok == '/')
		{
			if( shift[j-1] != '/')
			{
				shift[j++] = tok;
			}
		}
		else
			shift[j++] = tok;
		
		i++;
	}
	strcpy(array,shift);
}	

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
void set_path(char **basket,char **path)
{
	char *tmp2;
	int i=0;
	
	while(basket[1][i++] != '\0');

	if( basket[1][i] != '/')
		strcat(basket[1],"/");
	tmp2 = malloc(sizeof(basket[1]));
	strcpy(tmp2,basket[1]);
	
	if(j == 0)
		path[j++] = tmp2;
	else
	{
		for(i=0; i<j; i++)
		{
			if( !strcmp(path[i],tmp2) )
			{
				printf("path already exist \n");
				return;
			}
		}	
		path[j++] = tmp2;	
	}
}
void load_path(int fd,char **path)
{
	char buf;
	char bufs[BUFSIZ];
	char *baguni[10];
	int i=0;
	memset(bufs,0,BUFSIZ);

	if( (fd = open(".myShellRc", O_RDONLY)) <0 )
	{
		perror("open : ");
		exit(0) ;
	}	
	while( (read(fd,&buf,1)) > 0 )
	{
		if( buf == '\n')
		{
			tokenize(baguni,bufs);
			set_path(baguni,path);
			i = 0;
		}
		else 
			bufs[i++] = buf;
	}
}
			
int main(int argc, char **argv)
{
	int i,index,pid,access_check=1;
	char tok,buf[100];
	char *basket[LENGTH];
	char *path[20];
	char tmp[LENGTH];
	char *tmp2;
	int fd,n;
	struct sigaction act;

	memset(path,0,10);
	load_path(fd,path);

	act.sa_handler = SIG_IGN;
	sigfillset(&act.sa_mask);
	sigaction(SIGINT,&act,(struct sigaction *)NULL);

	while(1)
	{
		fprintf(stderr, "@@@ ");
		fgets(buf,LENGTH,stdin);
		buf[strlen(buf)-1]='\0';

		memset(basket,0,LENGTH);
		tokenize(basket,buf);

		if(!basket[0])// situation only enter
			continue;
		else if(!strcmp(basket[0],"setpath"))
		{
			avoid_slash_overlap(basket[1]);
			
			printf("input path = [%s]\n",basket[1]);
			set_path(basket,path);
		}
		else if(!strcmp(basket[0],"logout"))
		{
			printf("input logout byebye \n");
			exit(0);
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
	close(fd);
	return 0;
}
