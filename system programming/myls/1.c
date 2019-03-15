#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void sorting_ls(char *);
void mode_change(int mode, char *str);
void sort_argv(char **argv,char **, char**);
void select_option(int argc,char **argv,int flag);
void select_dir(int argc,char **argv,
int main(int argc, char **argv)
{
	if( argc < 2)
	{
		exit(1);
	}


	sorting_ls(argv[1]);
}

void sorting_ls(char *dirname)
{
	struct dirent **direntp;
	int n,i;
	struct stat statbuf;
	char str[11];

	printf("-----------sorting----------------\n");
	n = scandir(dirname,&direntp,0,alphasort);

	mode_change(statbuf.st_mode, str);

	for(i=0; i<n; i++)
	{
		stat(direntp[i]->d_name, &statbuf);
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%s\n",str,statbuf.st_nlink,statbuf.st_uid,statbuf.st_gid,statbuf.st_size,statbuf.st_mtime,direntp[i]->d_name);
	}
	printf("-----------sorting----------------\n");
}

void mode_change(int mode, char *str)
{
	strcpy(str,"----------");

	if( S_ISDIR(mode))
		str[0] = 'd';
	if( S_ISCHR(mode))
		str[0] = 'c';
	if( S_ISBLK(mode))
		str[0] = 'b';
	if( mode & S_IRUSR)
		str[1] = 'r';
	if( mode & S_IWUSR)
		str[2] = 'w';
	if( mode & S_IXUSR)
		str[3] = 'x';
	if( mode & S_IRGRP)
		str[4] = 'r';
	if( mode & S_IWGRP)
		str[5] = 'w';
	if( mode & S_IXGRP)
		str[6] = 'x';
	if( mode & S_IROTH)
		str[7] = 'r';
	if( mode & S_IWOTH)
		str[8] = 'w';
	if( mode & S_IXOTH)
		str[9] = 'x';
}

void sort_argv(char **argv)
{}
void select_option(int argc,char **argv,int flag)
{
	int i;

	for(i=1; i<argc ; i++)
	{
		if(!strcmp(argv[i],"-a"))
			flag = flag | 0;
		if(!strcmp(argv[i],"-l"))
			flag = flag | 1;
	}
}

	
