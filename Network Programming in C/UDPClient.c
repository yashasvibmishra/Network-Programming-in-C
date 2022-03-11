// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	int result;
	int a,b;
	char buffer[MAXLINE];
	char *hello = "Hello from client";
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;
	scanf("%d%d",&a,&b);
	sendto(sockfd, &a, sizeof(int),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	sendto(sockfd, &b, sizeof(int),
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("The Numbers have been sent for computation to the server.\n");
		
	n = recvfrom(sockfd, &result, sizeof(int),
				0, (struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';
	printf("Result returned from the server is: %d\n", result);

	close(sockfd);
	return 0;
}

