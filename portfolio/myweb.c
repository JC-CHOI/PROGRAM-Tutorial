#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void* request_handler(void *arg);
void send_data(FILE *,char *file_name,FILE *);// have to repair
void error_handler(char *msg);
void status_error(int status,FILE *fp);

char virsion[8];

int main(int argc, char **argv)
{
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_size;
	pthread_t t_id;
	char message[BUFSIZ];

	if(argc < 2)
		error_handler("input ip & port number \n");

	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(server_sock == -1)
		error_handler("server_sock socket() error \n");

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));
	if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
		error_handler("bind error \n");
	if(listen(server_sock, 20))
		error_handler("listen error \n");

	while(1)
	{
		client_addr_size = sizeof(client_addr);
		client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&client_addr_size);
		printf("connection request : %s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		pthread_create(&t_id, NULL , request_handler,(void *)&client_sock);
		pthread_detach(t_id);
	}

}
void* request_handler(void *arg)
{
	int clnt_sock = *((int*)arg);
	FILE *in_client;
	FILE *out_client;
	char req_line[BUFSIZ] = {0};

	char command[10];
	char file_name[128];
	FILE *fp;

	memset(command,0,10);
	memset(file_name,0,128);

	in_client = fdopen(clnt_sock,"r");
	out_client = fdopen(clnt_sock,"w");
	
	printf("input request line : ");
	fgets(req_line,BUFSIZ,in_client);                            
	req_line[strlen(req_line)-1] = '\0';

	if(!strcmp(strtok(req_line," /"),"GET"))
	{
		strcpy(file_name,strtok(NULL," "));
		
		fp = fopen(file_name,"r");
		if( fp == NULL)
		{
			status_error(404,out_client);
		}
		
		if(!strcmp(strtok(NULL," /"),"HTTP"))
		{
			strcpy(virsion,strtok(NULL," /"));

			send_data(out_client,file_name,fp);
		}
		else
			status_error(400,out_client);

	}
	else
		status_error(400,out_client);
	return NULL;
}
void send_data(FILE *out_client,char *file_name,FILE *fp)
{
	//char status_line[] = "HTTP/1.1 200 OK";
	char status_line[BUFSIZ];
	char header_server[] = "Server : mySimpleWebServer ";
	char header_type[100] = "Content-type : text/";
	char header_length[100] = "Content-length : ";
	char BUF[BUFSIZ];
	char copy_filename[100];
	char tok[100];

	int c,length = 0;

	while( (c = fgetc(fp)) != 0)
		length++;
	fseek(fp,0,SEEK_SET); // return offset

	memset(BUF,0L,BUFSIZ);
	memset(status_line,0,BUFSIZ);

	strcpy(status_line,"HTTP/"); //MAKE STATUS LINE
	strcat(status_line,virsion);
	strcat(status_line," 200 OK");

	strcpy(copy_filename,file_name); // copy file_name for strtok
	strtok(copy_filename," .");
	strcpy(tok,strtok(NULL," ."));

	if( !strcmp(tok,"html"))
		strcat(header_type,tok); // make header_type
	else
		strcat(header_type,"plain");

//	strcat(header_length, itoa(length));
	sprintf(header_length + strlen(header_length), "%d", length);

	fputs(status_line,out_client);
	fputs(header_server,out_client);
	fputs(header_type,out_client);
	fputs(header_length,out_client);

	while( fgets(BUF,BUFSIZ,fp) != NULL)
	{
		fputs(BUF,out_client);
		fflush(fp);
	}
	fflush(fp);
	fclose(fp);
}

void error_handler(char *msg)
{
	fputs(msg,stderr);
//	fputc('\n',stderr);
	return ;
}
void status_error(int status,FILE *fp)
{
	char msg[100]  ;
	sprintf(msg, "HTTP/%s %d Bad Request \n",virsion,status);

	fputs(msg,fp);
	fflush(fp);

}
