#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
	int sockfd;
	char buffer[MAXLINE];
	int *a = (int *)malloc(5 * sizeof(int));
	float result;
	printf("Enter 5 Numbers:-\n");
	for (int i = 0; i < 5; i++)
		scanf("%d", &a[i]);

	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, len;

	for (int i = 0; i < 5; i++)
		sendto(sockfd, &a[i], sizeof(a[i]), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

	printf("Numbers sent.\n");

	n = recvfrom(sockfd, &result, sizeof(int), 0, (struct sockaddr *)&servaddr, &len);

	printf("Sum(from Server) = %f\n", result/5);

	close(sockfd);
	return 0;
}
