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

int Count_word_all(char s[MAXLINE])
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ' ' && s[i + 1] != ' ')
            count++;
    }
    return count + 1;
}

// Driver code
int main()
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // actual part

    int len;
    int word[5];
    char input[5][MAXLINE];

    len = sizeof(cliaddr);

    recvfrom(sockfd, &input, sizeof(input),
             0, (struct sockaddr *)&cliaddr,
             &len);
    for (int i = 0; i < 5; i++)
    {
        word[i] = Count_word_all(input[i]);
    }

    printf("\nSentence 1 --> %s ", input[0]);

    printf("\nSentence 2 --> %s ", input[1]);

    printf("\nSentence 3 --> %s ", input[2]);

    printf("\nSentence 4 --> %s ", input[3]);

    printf("\nSentence 5 --> %s ", input[4]);

    int max = word[0];
    for (int i = 0; i < 5; i++)
    {
        if (word[i] > max)
            max = word[i];
    }

    sendto(sockfd, &max, sizeof(max),0, (const struct sockaddr *)&cliaddr,len);
    printf("\nWord count sent\n");

    return 0;
}
