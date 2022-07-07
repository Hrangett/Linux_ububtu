#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <fcntl.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100
#define IMG_BUF 10000000;

void request_handler(int *arg);
void send_data(FILE*fp, char*ct, char* file_name);
void error_handling(char *msg);

char wp[] = "HTTP/1.1 200 OK\r\n"
		"Server:Linux Web Server\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n\r\n"
		"<!DOCTYPE html>\r\n"	
		"<html><head><title> My Web Page </title>\r\n"
		"<style>body {background-color: #FFFF0F }</style></head>\r\n"
		"<body><center><h1>Hello world!!</h1><br>\r\n"
		 "<img src=\"cap.jpg\"></center></body></html>\r\n";

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_size;
	

	if(argc!=2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if((serv_sock = socket(PF_INET, SOCK_STREAM, 0))==-1)
		error_handling("socket() error");		
		
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
		if((clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size)) == -1)
			error_handling("accept err");

		request_handler(&clnt_sock);

		close(clnt_sock);

	}
	close(serv_sock);
	return 0;
}

void request_handler(int *arg)
{
	int clnt_sock = *arg;
	char req_line[SMALL_BUF];	
	int img_fd = 0;
	char img_buf[68852];
	char buf[BUF_SIZE];
	char wp[] = "HTTP/1.1 200 OK\r\n"
        "Server:Linux Web Server\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<!DOCTYPE html>\r\n"
        "<html><head><title> My Web Page </title>\r\n"
        "<style>body {background-color: #FFFF0F }</style></head>\r\n"
        "<body><center><h1>Hello world!!</h1><br>\r\n"
			"<img src=\"mon.png\"></center></body></html>\r\n";

	if(read(clnt_sock,buf,sizeof(buf)) == -1)
		error_handling("read err");

	printf("\n\n%s\n\n",buf);


	if(strstr(buf, "GET / HTTP/1.1")!=NULL)
	{
		if(write(clnt_sock, wp,sizeof(wp)) == -1)
			error_handling("write err");
		
	}
	else if(strstr(buf, "GET /mon.png HTTP")!=NULL)
	{

		if((img_fd=open("mon.png",O_RDONLY)) == -1)
			error_handling("img open err");

		if(read(img_fd,img_buf,sizeof(img_buf))==-1)
			error_handling("img read err");

		if(write(clnt_sock, img_buf, sizeof(img_buf)) == -1)
			error_handling("img write err");
	}
	

}

void error_handling(char *msg)
{
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}
