#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char * message);
int calculate(int opnum, int op[], char oprator);

int main(int argc, char* argv[])
{
	int serv_sock;
	int clnt_sock;

	//서버,,,,,

	//,,,,,,,

	//잠와,,,,,크루아상..??
	socket
	bind
	listen
	accept
	read
	write
	
	
	return 0;
}
int calculate(int opnum, int op[], char oprator)
{
	int result;
	
	switch(oprator)
	{
		case '+':
			result = 0;
			break;
		case '-':
			result = 0;
			break;

		case'*';
			result = 1;
			break;
		case '/'
			
			break;
		
	}
	
	
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
	
}
