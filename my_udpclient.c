// NAME : B.UDAY KIRAN
// ROLL NUMBER : 19CS10017
// MY_UDPCLIENT PROGRAM

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char filename[100];
	//filename = (char *)argv[1];
	int fd = open(argv[1], O_RDONLY, 0);
	if(fd == -1)
	{
		printf("File Not Found\n");
		exit(1);
	}
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server_addr, client_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    	server_addr.sin_port = htons(4321);
    	
    	char buffer[100] ;
    	int readbytes ;
    	//chunk size is 50
    	while(1) {
    		readbytes = read(fd, buffer, 50);
    		if(readbytes == 0)
    			break;	
    		buffer[readbytes] = '\0';
    		send(sockfd, buffer, strlen(buffer), 0);
    		memset(&buffer, 0, 100);
    	}
    	int chars, words, sentences;
    	readbytes = recv(sockfd, &chars, sizeof(int), 0);
    	readbytes = recv(sockfd, &words, sizeof(int), 0);
    	readbytes = recv(sockfd, &sentences, sizeof(int), 0);
    	
    	printf("Characters: %d, Words: %d, Sentences: %d\n", chars, words, sentences);
    	
	close(fd);
    	close(sockfd);    	
}
