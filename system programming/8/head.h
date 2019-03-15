#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
typedef struct {
	char filename[128];
	char status[16];
	char data[1024];
}Memory;

#define SHM_PATH "./tmp"
#define SHM_KEY 'A'
#define SEM_KEY 'B'

