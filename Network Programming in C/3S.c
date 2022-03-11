#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	struct sockaddr_in	 servaddr;
                    char buffer[MAXLINE];
                    char *a = "Hello this is a sentence";
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
                   len = sizeof(servaddr);
	sendto(sockfd, (const char *)a, MAXLINE,
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("String sent.\n");
	int ans;
	n = recvfrom(sockfd, &ans, sizeof(int),
				0, (struct sockaddr *) &servaddr,
		                                                                                                      &len);
                   buffer[n] = '\0';
	printf("Server : %d\n", ans);

	close(sockfd);
	return 0;
}
