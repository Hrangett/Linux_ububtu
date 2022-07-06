#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define SAMLL_BUF 100

void request_handler(void*arg);
void send_data(FILE*fp, char*ct, char* file_name);
void error_handling(char *msg);

char webpage[] = "HTTP/1.1 200 OK\r\n"
		"Server:Linux Web Server\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n\r\n"
		"<!DOCTYPE html>\r\n"	
		"<html><head><title> My Web Page </title>\r\n"
		"<style>body {background-color: #FFFF00 }</style></head>\r\n"
		"<body><center><h1>Hello world!!</h1><br>\r\n"
		 "<img src=\"cap.jpg\"></center></body></html>\r\n";

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;

	int clnt_adr_size;
	char buf[BUF_SIZE];
	

	
	if(argc!=2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind error");
	else
		puts("binding sucess");
		
	if(listen(serv_sock,20) == -1)
		error_handling("listen err");
	else
		puts("listen sucess");

	while(1)
	{
		clnt_adr_size = sizeof(clnt_adr);
		if(clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size) == -1)
			error_handling("accept err");

		printf("Connection Request : %s : %d \n", inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));

		request_handler(&clnt_sock);
		
	}
	close(serv_sock);
	return 0;
}

void request_handler(int *arg)
{
	int clnt_sock =*arg;
	char req_line[SMALL_BUF];
	FILE* clnt_read;
	FILE* clnt_write;

	char method[10];
	
}

 void error_handling(char *msg)
 {
 	fputs(msg,stderr);
 	fputc('\n',stderr);
 	exit(1);
}
