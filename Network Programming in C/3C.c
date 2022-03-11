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
int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in serveraddr, clientaddr;
    char buffer[MAXLINE];
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("An error creating the socket");
        exit(EXIT_FAILURE);
    }
    // using memset to fill socket and client addr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    memset(&clientaddr, 0, sizeof(clientaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("An error binding the socket");
        exit(EXIT_FAILURE);
    }

    

    int len = sizeof(clientaddr);
    int n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     0, (struct sockaddr *)&clientaddr,
                     &len);
    	printf("String recieved.\n");

buffer[n] = '\0';
int words = 1;
    for(int i = 0; buffer[i] != '\0'; i++) {
        if(buffer[i] == ' ') words++;
    }
     	

    sendto(sockfd, (float *)&words, sizeof(words), 0, (struct sockaddr *)&clientaddr,len);
    printf("Ans sent.\n");
    return 0;
}
