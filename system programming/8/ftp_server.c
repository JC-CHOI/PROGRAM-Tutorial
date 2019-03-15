#include "head.h"

int sem_id =0, shm_id =0;
Memory *memory;

void remove_ipcs(int, int, Memory*);
int init_sem();
int init_shm();
void handler(int sig);
int main(int argc, char **argv)
{
	int fd,size;
	key_t shm_key;
	key_t sem_key;
	char file[128];
	struct sembuf lock = {0,-1,SEM_UNDO};
	struct sembuf unlock = {0,1,SEM_UNDO};
	
	if( (shm_id = init_shm(shm_ptr)) < 0)
	{
		perror(argv[0]);
		remove_ipcs(shm_id,sem_id,memory);
		exit(3);
	}
	if( (sem_id = init_sem()) < 0 )
	{
		perror(argv[0]);
		remove_ipcs(shm_id,sem_id,memory);
		exit(4);
	}
	strcpy(memory->status,"invalid");
	while(1)
	{
		if(semop(sem_id,&lock,1) < 0)
		{
			perror("semop : ");
			exit(1);
		}
		if( (!strcmp(memory->status,"invalid") || (!strcmp(memory->status,"processed"))))
		{
			if(semop(sem_id,&unlock,1) < 0)
			{
				perror("semop : ");
				exit(2);
			}
			continue;
		}
		else if(!strcmp(memory->status,"requested"))
		{
			strcpy(file,memory->filename);
			if(	(fd = open(file,O_RDONLY)) < 0)
			{
				perror(file);
				exit(3);
			}
			while( (size = read(fd,memory->data,1024)) > 0)
					;
			strcpy(memory->status,"processed");
			if(semop(sem_id,&unlock,1) < 0)
			{
				perror("semop : ");
				exit(2);
			}
		}
	}
	remove_ipcs(shm_id, sem_id, memory);
	printf("complished \n");
	exit(0);
}


int init_shm()
{
	key_t shm_key = ftok(SHM_PATH,SHM_KEY);
	
	if( (shm_id = shmget(shm_key, sizeof(Memory),IPC_CREAT|IPC_EXCL|0666) ) == -1)
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
	if( (sem_id = semget(sem_key, 1, IPC_CREAT|IPC_EXCL|0666)) == -1)
	{
		printf("semaphore already exist\n");
		if( (sem_id = semget(sem_key,1,0)) == -1)
		{
			perror("semget : ");
			return -1;
		}
	}
	if( semctl(sem_id, 0, SETVAL, 1) == -1)
	{
		perror("semctl : ");
		return -1;
	}
	return sem_id;
}

void remove_ipcs(int shmid,int semid, Memory* shmptr)
{
	if( shmid > 0 && (shmptr != NULL))
	{
		shmdt(shmptr);
		shmctl(shmid,IPC_RMID,NULL);
	}
	if( semid >0)
		semctl(semid, 0, IPC_RMID, 0);
}
void handler(int sig)
{
	if( sig == SIGINT)
	{
		remove_ipcs(shm_id,sem_id,memory);
		printf("remove complished \n");
		exit(1);
	}
}
