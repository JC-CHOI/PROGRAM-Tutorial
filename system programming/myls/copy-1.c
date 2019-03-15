#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
void ls_(char *);
void stat_(char *);
void sorting_ls(char *);

int main(int argc, char **argv)
{
	if( argc < 2)
	{
		exit(1);
	}

	ls_(argv[1]);
	stat_(argv[1]);
	sorting_ls(argv[1]);
}

void ls_(char *dirname)
{
	DIR *dir_ptr;
	struct dirent *direntp;

	printf("-----------filename --------------\n");
	if( (dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr,"ls : cannot open %s\n",dirname);
	else
	{
		while( (direntp = readdir(dir_ptr)) != NULL)
			printf("%s\t",direntp->d_name);
		printf("\n");
	closedir(dir_ptr);
	}
	printf("-----------filename --------------\n\n");

}
void stat_(char *dirname)
{
	DIR *dir_ptr;
	struct dirent *direntp;
	struct stat statbuf;

	printf("-----------file stat -------------\n");
	dir_ptr = opendir(dirname);

	while( (direntp = readdir(dir_ptr)) != NULL)
	{
		stat(direntp->d_name, &statbuf);
		printf("%d\t%d\t%d\t%d\t%s\n",statbuf.st_nlink,statbuf.st_uid,statbuf.st_gid,statbuf.st_size,direntp->d_name);
	}
	closedir(dir_ptr);
	printf("-----------file stat -------------\n\n");
}
void sorting_ls(char *dirname)
{
	struct dirent **direntp;
	int n,i;
	struct stat statbuf;

	printf("-----------sorting----------------\n");
	n = scandir(dirname,&direntp,0,alphasort);

	for(i=0; i<n; i++)
	{
		stat(direntp[i]->d_name, &statbuf);
		printf("%o\t%d\t%d\t%d\t%d\t%d\t%s\n",statbuf.st_mode,statbuf.st_nlink,statbuf.st_uid,statbuf.st_gid,statbuf.st_size,statbuf.st_mtime,direntp[i]->d_name);
	}
	printf("-----------sorting----------------\n");
}
