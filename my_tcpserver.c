// NAME : B.UDAY KIRAN
// ROLL NUMBER : 19CS10017
// MY_TCPSERVER PROGRAM

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in client_addr, server_addr;
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
    	server_addr.sin_port = htons(4321);
    	
    	int bindflag = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    	
    	while(1) {
	    	int listenflag = listen(sockfd, 3);
		int len = sizeof(struct sockaddr_in);	
		int newsockfd = accept(sockfd, (struct sockaddr *)&client_addr,  &len);

		char buffer[100];
		int readbytes = read(newsockfd, buffer, sizeof(buffer));
		buffer[readbytes] = '\0';
		
		int words = 0, sentences = 0, chars = 0;
		while(readbytes) {
			for(int i=0; i<readbytes; i++) {
				if(buffer[i] == ' ')
					words++;
				if(buffer[i] == '.')
					sentences++;
			}
			chars += readbytes;
			memset(&buffer, 0, sizeof(buffer));
			readbytes = read(newsockfd, buffer, sizeof(buffer));
			buffer[readbytes] = '\0';
		}
		
		printf("Characters: %d, Words: %d, Sentences: %d\n", chars, words, sentences);
		send(newsockfd, &chars, sizeof(int), 0);
		send(newsockfd, &words, sizeof(int), 0);
		send(newsockfd, &sentences, sizeof(int), 0);
		
		close(newsockfd);

	}
}
