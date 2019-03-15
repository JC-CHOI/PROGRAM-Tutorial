#include "head.h"
#define wait 1 
#define sended 2
int sem_id =0, shm_id =0;
Memory *memory;

void remove_ipcs();
int init_sem();
int init_shm();
void handler(int sig);
int main(int argc, char **argv)
{
	int fd,size;
	int flag;
	char file[128];
	struct sembuf lock = {0,-1,SEM_UNDO};
	struct sembuf unlock = {0,1,SEM_UNDO};

	if( (shm_id = init_shm()) < 0)
	{
		perror(argv[0]);
		remove_ipcs();
		exit(3);
	}
	if( (sem_id = init_sem()) < 0 )
	{
		perror(argv[0]);
		remove_ipcs();
		exit(4);
	}
	signal(SIGINT,handler);
	flag = wait;
	while(1)
	{
		if(semop(sem_id,&lock,1) < 0) // sema lock
		{
			perror("semop : ");
			exit(1);
		}
		if( !strcmp(memory->status,"invalid"))
		{
			if( flag == wait)
			{
				printf("write file name \n");
				read(0,file,128);
				file[strlen(file)-1]='\0';
	
				strcpy(memory->filename,file);
				memset(file,0,128);
				strcpy(memory->status,"requested");	
				flag = sended;	
			}
		}
		else if( !strcmp(memory->status,"processed"))
		{
			if( flag == sended)
			{
				write(1,memory->data,1024);
				memset(memory->status,0,128);
				strcpy(memory->status,"invalid");
				flag = wait;
			}
		}

		if(semop(sem_id,&unlock,1) < 0)
		{
			perror("semop : ");
			exit(2);
		}
	}
	remove_ipcs();
	printf("complished \n");
	exit(0);
}
int init_shm()
{
	
	key_t shm_key = ftok(SHM_PATH,SHM_KEY);
	
	if( (shm_id = shmget(shm_key, sizeof(Memory),IPC_CREAT|0666) ) == -1)
	{
		printf("shared memory already exist\n");
		if( (shm_id = shmget(shm_key,sizeof(Memory),0)) == -1)
		{
			perror("shmget : ");
			return -1;
		}
	}
	if( (memory= (Memory *)shmat(shm_id,0,0)) == NULL)
	{
		perror("shmat : ");
		return -1;
	}
	
	return shm_id;
}
int init_sem()
{
	key_t sem_key = ftok(SHM_PATH,SEM_KEY);
	if( (sem_id = semget(sem_key, 1, IPC_CREAT|0666)) == -1)
	{
		printf("semaphore already exist\n");
		if( sem_id = semget(sem_key,1,0) == -1)
		{
			perror("semget : ");
			return -1;
		}
	}
	return sem_id;
}
void handler(int sig)
{
	if( sig == SIGINT)
	{
		remove_ipcs(shm_id,sem_id,memory);
		printf("semaphore & shared memory deleted \n");
		exit(1);
	}
}

void remove_ipcs()
{
	if( shm_id > 0 && (memory != NULL))
	{
		shmdt(memory);
		shmctl(shm_id,IPC_RMID,NULL);
	}
	if( sem_id >0)
		semctl(sem_id, 0, IPC_RMID, 0);
}
