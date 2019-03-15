#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>

#define MAXLENGTH 100

int f_index;
int d_index;
char option[5];

void Option(int argc,char *argv[],char *opt);
void Sort(char *argv[],char *new[]);
void Seperate_Mode(char *argv[],char *dir[],char *file[]);
int Opt_Execute(char *pathname,char flag);
void print_status(struct stat *);
void print_mode(struct stat *);
int filter(const struct dirent *dirent);

void main(int argc, char *argv[])
{
	char *dir[MAXLENGTH]={},*file[MAXLENGTH]={};
	char *new[MAXLENGTH]={};
	struct dirent *dir_entry;
	struct dirent **dir_entp;
	int i,total,n,k;
	char path[MAXLENGTH]={};

	Option(argc,argv,option);

	//Sort(argv,new);
	
	Seperate_Mode(argv,dir,file);
	
	for(i=0 ; i<f_index ; i++)
	{
		Opt_Execute(file[i],'f');
		printf("%s  ",file[i]);
		
		if(i == (f_index-1))
			printf("\n");
	}	
	
		
	if(!d_index)
	{
		dir[0]=malloc(sizeof(*argv));
		strcpy(dir[d_index++],"./");
	}	
	
	for(k=0 ; k<d_index ; k++)
	{
		memset(path,'\0',sizeof(path));
		strcpy(path,dir[k]);
		
		if(d_index >1)
			fprintf(stderr,"%s:\n",dir[k]);

		if((n=scandir(path,&dir_entp,*filter,alphasort)) == -1)
		{
			perror("scandir : ");
			exit(2);
		}
		
		if(option[1] || option[2])
		{
			for(i=0 ; i<n ; i++)
			{
				memset(path,'\0',sizeof(path));
				strcpy(path,dir[k]);
				strcat(path,dir_entp[i]->d_name);
				total += Opt_Execute(path,'t');
			}
			printf("합계 %d\n",total/2);
		}

		for(i=0 ; i<n ; i++)
		{
			memset(path,'\0',sizeof(path));
			strcpy(path,dir[k]);
			strcat(path,dir_entp[i]->d_name);
			Opt_Execute(path,'d');

			printf("%s\n",dir_entp[i]->d_name);
		}
	}
}	

int Opt_Execute(char *pathname,char flag)
{
	struct stat s_buf;
	
	if(lstat(pathname,&s_buf) == -1)
	{
		perror("lstat: ");
		exit(1);
	}
		
	if((flag == 'd') || (flag =='f')) //directory or total	
	{	
		if(option[1] == 's')
				printf("%2ld ",s_buf.st_blocks/2);
	
		if(option[2] == 'l')
				print_status(&s_buf);
	}

	if(flag == 't') //total
		return s_buf.st_blocks;
	
	return 0;
}

void Option(int argc,char *argv[],char *option)
{
	int param_opt;

	while((param_opt=getopt(argc,argv,"als")) != -1)
	{
			switch(param_opt)
			{
					case 'a':
							*option='a';		
							break;
					case 's':
							*(option+1)='s';
							break;
					case 'l':
							*(option+2)='l';
							break;
					case '?':
							printf("Invalid Option : %c\n",optopt);
							exit(1);
			}
	}

}

void Sort(char *argv[],char *new[])
{
/*
	char tmp[MAXLENGTH]={};
	char **now;
	char **next;

	while(*now && *next)
	{
		
		if(**now == '-')
			continue;
		if(strcmp(**now,**next))

	}
*/
}
void Seperate_Mode(char *argv[],char *dir[],char *file[])
{
	struct stat s_buf;
	char tmp[MAXLENGTH]={};
	
	for(*argv++ ; *argv ; argv++)
	{
		if(*argv[0] == '-')
			continue;
		
		if(lstat(*argv,&s_buf) == -1)
		{
			fprintf(stderr,"ls: '%s'에 접근할 수 없습니다: 그런 파일이나 디렉터리가 없습니다\n",*argv);
			continue;
		}
		else
		{
			if((s_buf.st_mode & S_IFMT) == S_IFDIR)
			{
				memset(tmp,'\0',MAXLENGTH);
				strcpy(tmp,*argv);
				if(tmp[strlen(tmp)-1] != '/')
				{
					tmp[strlen(tmp)] = '/';
				}
				dir[d_index]=malloc(sizeof(tmp));
				strcpy(dir[d_index++],tmp);
			}
			else
			{
				file[f_index]=malloc(sizeof(*argv));
				strcpy(file[f_index++],*argv);
			}
		}
	}	
}

int filter(const struct dirent *dirent)
{
	if(!option[0]  && dirent->d_name[0] == '.')
		return 0;
}

void print_status(struct stat *f_buf)
{
		print_mode(f_buf);
		printf("%2ld ",f_buf->st_nlink); //links
		printf("%s ",getpwuid(f_buf->st_uid)->pw_name);
		printf("%s ",getgrgid(f_buf->st_gid)->gr_name);
		printf("%5ld  ",f_buf->st_size);//total size
		printf("%d월 ",localtime(&f_buf->st_mtime)->tm_mon); //file size
		printf("%2d ",localtime(&f_buf->st_mtime)->tm_mday); //file size
		printf("%2d:%02d ",localtime(&f_buf->st_mtime)->tm_hour,localtime(&f_buf->st_mtime)->tm_min); //file size
}

void print_mode(struct stat *f_buf)
{
		switch(f_buf->st_mode & S_IFMT)
		{
				case S_IFDIR:
						printf("d");
						break;
				case S_IFCHR:
						printf("c");
						break;
				case S_IFBLK:
						printf("b");
						break;
				case S_IFREG:
						printf("-");
						break;
				case S_IFIFO:
						printf("Named Pipes!!\n");
						break;
		}
		printf("%s",(f_buf->st_mode& S_IRUSR)?"r":"-");
		printf("%s",(f_buf->st_mode& S_IWUSR)?"w":"-");
		printf("%s",(f_buf->st_mode& S_IXUSR)?"x":"-");
		printf("%s",(f_buf->st_mode& S_IRGRP)?"r":"-");
		printf("%s",(f_buf->st_mode& S_IWGRP)?"w":"-");
		printf("%s",(f_buf->st_mode& S_IXGRP)?"x":"-");
		printf("%s",(f_buf->st_mode& S_IROTH)?"r":"-");
		printf("%s",(f_buf->st_mode& S_IWOTH)?"w":"-");
		printf("%s",(f_buf->st_mode& S_IXOTH)?"x":"-");
}
