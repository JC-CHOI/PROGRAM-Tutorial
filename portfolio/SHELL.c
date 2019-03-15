#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>

#define MAX_LENGTH 100

int File_read(char **argv,char **path);
int Path_Insert(char **argv,char **buffer);
int Access_possibility(char **path,char **argv);
void Command_handler(char *command,char **argv);

void main()
{
	int pid,status;
	char command[MAX_LENGTH],PATH[MAX_LENGTH];
	char *argv[MAX_LENGTH]={};
	char *path[MAX_LENGTH]={};
	
	if(File_read(argv,path) == -1)
	{
		printf("Confirm .myShellRc file\n");	
		exit(-1);
	}
	
	while(1)
	{
		printf("%% ");
		fgets(command,MAX_LENGTH,stdin);
        command[strlen(command)-1]='\0';
		Command_handler(command,argv);
		
		if(!argv[0])
		{
			printf("Input command\n");	
			continue;
		}

		if(!strcmp(argv[0],"setpath"))
		{
			Path_Insert(argv,path);
			continue;
		}

		if(Access_possibility(path,argv) == -1)
		{
			printf("Command not found\n");	
			continue;
		}
		
		if((pid = fork()) == -1)
		{
			perror("fork() : ");
			exit(-1);
		}
		else if(!pid)
		{
			execv(argv[0],argv);
			perror("execv : ");
			exit(-1);
		}
		else	
			wait(&status);
	}
}
int File_read(char **argv,char **path)
{
	int fd=0,index=0;
	char tmp,path_tmp[MAX_LENGTH];

	if((fd=open("/home/yesblue/.myShellRc",O_RDONLY)) < 0)
	{
		perror("/home/yesblue/.myShellRc : ");
		return -1;
	}
	
	strcat(path_tmp,"setpath ");
	index=strlen(path_tmp);
	
	while(read(fd,&tmp,1) > 0)
	{
		if(tmp == '\n')
			tmp= ' ';
		path_tmp[index++]=tmp;
	}
	Command_handler(path_tmp,argv);
	Path_Insert(argv,path);
	return 0;	
}
int Path_Insert(char **argv,char **path)
{
	char tmp[MAX_LENGTH]={};
	int i,j;
	
	if(!argv[1]) //if argv[1] is NULL, you quit.
	{
		printf("usage : setpath /path/\n");
		return -1;
	}
	for(i=0 ; *(path+i) ; i++) ; //find space for inserting path road.
	for(j=1 ; *(argv+j) ; j++,i++) //if you have many path roades, insert many times.
	{
		strcpy(tmp,argv[j]);
		if(tmp[strlen(tmp)-1] !=  '/')
			tmp[strlen(tmp)]='/';
		
		*(path+i)=malloc(strlen(tmp));
		strcpy(*(path+i),tmp);
	}
	return 0;
}
int Access_possibility(char **path,char **argv)
{
	char tmp[MAX_LENGTH];
	int i=0;

	for( ; *(path+i) ; i++)
	{
		memset(tmp,'\0',MAX_LENGTH);

		strcpy(tmp,*(path+i));
		strcat(tmp,argv[0]);

		if(!access(tmp,F_OK))
		{
			free(argv[0]);
			argv[0]=malloc(strlen(tmp));
			strcpy(argv[0],tmp);

			return 0;	
		}
	}
	return -1;
}
void Command_handler(char *command,char **argv)
{
	int index=-1,tmp_index=-1;
	char tmp[MAX_LENGTH]={};
	
	memset(tmp,'\0',MAX_LENGTH);
	
	for( ; *command ; command++)
	{
		if((*command == ' ') && (tmp_index != -1))
		{	
			argv[++index]=malloc(strlen(tmp));
			strcpy(argv[index],tmp);
			memset(tmp,'\0',MAX_LENGTH);
			tmp_index=-1;
		}
		else if(*command != ' ')
			tmp[++tmp_index]=*command;		
	}
	if(tmp_index != -1)
	{
		argv[++index]=malloc(strlen(tmp));
		strcpy(argv[index],tmp);
		argv[++index]=NULL;
	}
}
