#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define LENGTH 200
int my_access(char *path,char **instruction,char *tmp)
{
	char *stop;
	memset(tmp,'\0',LENGTH);
	
	strcpy(tmp,instruction[0]);

	strcpy(stop,path);
	strcat(stop,tmp);

	return access(stop,F_OK);
}

void tokenize(char **basket,char *commend)
{
	int seek=0,i_basket=0;
	char tok;
	while((tok=commend[seek]) != '\0')
	{
		printf("1\n");
		if(seek == 0 && tok != ' ')
		{
			basket[i_basket++] = &commend[seek];
			printf("basket2 : %s\n",basket[i_basket-1]);
		}
			
		else 
		 {
		printf("2\n");
			if(tok != ' ')
			{	
				printf("command : %c\n",commend[seek-1]);
				if(commend[seek-1] == ' ')
				{		
					printf("111\n");
					basket[i_basket++] = &commend[seek];
					printf("basket : %s\n",basket[i_basket-1]);
				}
			}
			else 
			{
		printf("3\n");
				if(commend[seek-1] != ' ')
					commend[seek] = '\0';
			}
		}
		
		seek++;
	}
}
		
int main(int argc, char **argv)
{
	int i,pid;
	char tok,buf[LENGTH];
	char *basket[LENGTH];
	char tmp[LENGTH];
	char *path[3]={"/bin/","/usr/bin/","/usr/local/bin/"};

	
	while(1)
	{	
		printf("@@@ \n");
		read(0,buf,LENGTH);
		buf[strlen(buf)-1]='\0';

		memset(basket,0,LENGTH);
		tokenize(basket,buf);
		fprintf(stdout,"%s\n", basket[0]);

		fprintf(stdout,"%s\n", basket[1]);
/*		for(i=0;i<3;i++)
		{
			if(!my_access(path[i],basket,tmp))
			{*/
				if(pid =fork() == -1)
				{
					perror("fork() :");
					exit(0);
				}
				if(pid == 0)
					execv(path[i],basket);
		//	}
		}			
	

	return 0;
}

