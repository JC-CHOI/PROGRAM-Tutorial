#include "echo.h"

int main()
{
	int size =0,fd[2];
	int msg_id =0,n,pid;
	key_t key;
	MSG_BUF msg_buf;

	if( (key = ftok(".",'a')) == -1)
	{
		perror("[server] ftok() : ");
		exit(1);
	}
	if( (msg_id = msgget(key, IPC_CREAT | 0666)) == -1)
	{
		perror("[server] msgget() : ");
		exit(2);
	}
	while(1)
	{
		if(pipe(fd) == -1)
		{
			perror("pipe : ");
			exit(1);
		}
			
		if( (size = msgrcv(msg_id,&msg_buf,MAXSIZE+1,SERVER_TYPE,0)) == -1)
		{
			perror("[server] msgrcv : ");
			break;
		}
		else if(size == 0)
				break;

		if( (pid = fork()) > 0)
		{
			memset(&msg_buf,0x00,sizeof(MSG_BUF));
			if( (read(fd[0],msg_buf.mdata,MAXSIZE)) < 0)
			{
				perror("read : ");
				break;
			}
		}
		else if( pid == 0)
		{
			close(1);
			dup(fd[1]);
			msg_buf.mdata[strlen(msg_buf.mdata)-1] = '\0';
			execl(msg_buf.mdata,msg_buf.mdata,NULL);
		}

		msg_buf.mtype = CLIENT_TYPE;
		if(msgsnd(msg_id,&msg_buf,strlen(msg_buf.mdata)+1,0) == -1)
		{
			perror("[server] : msgsnd : ");
			break;
		}
	}

	msgctl(msg_id, IPC_RMID,0);
	exit(0);
}
