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
    char buffer[5][MAXLINE];
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

    //actual

    int len;
    int words = 0;

    for (int i = 0; i < 5; i++)
    {
        printf("Enter sentence %d: --- ", i + 1);
        scanf("%[^\n]%*c", buffer[i]);
    }

    sendto(sockfd, &buffer, sizeof(buffer),
           0, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));
    printf("Sentences sent: \n");

    recvfrom(sockfd, &words, sizeof(int),
             0, (struct sockaddr *)&servaddr,
             &len);
    printf("Sentence with max words is  : %d\n", words);

    close(sockfd);
    return 0;
}
