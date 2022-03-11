#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    char protocol_choice[4];
    short port;

    printf("Enter the server protocol (udp/tcp):\n");
    scanf("%s", protocol_choice);

    printf("Enter the server port:\n");
    scanf("%hd", &port);

    if (strcmp(protocol_choice, "udp") == 0)
    {
        int sockfd;
        char buffer[100];
        char *request = "qotd";
        struct sockaddr_in servaddr;

        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = INADDR_ANY;

        int n, len;

        sendto(sockfd, (const char *)request, strlen(request),
               0, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));

        len = sizeof(servaddr);

        n = recvfrom(sockfd, (char *)buffer, 100,
                     0, (struct sockaddr *)&servaddr,
                     (socklen_t *)&len);
        buffer[n] = '\0';

        printf("%s\n", buffer);
        close(sockfd);
    }
    else if (strcmp(protocol_choice, "tcp") == 0)
    {
        int sockfd;
        char buffer[100];
        char *request = "qotd";
        struct sockaddr_in servaddr;

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = INADDR_ANY;

        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            printf("Connection Failed\n");
            exit(EXIT_FAILURE);
        }

        int n;
        send(sockfd, request, strlen(request), 0);
        n = read(sockfd, buffer, 100);
        buffer[n] = '\0';
        printf("%s\n", buffer);
        close(sockfd);
    }
    else
    {
        printf("The protocol is not supported. Exiting.");
        exit(EXIT_FAILURE);
    }
}