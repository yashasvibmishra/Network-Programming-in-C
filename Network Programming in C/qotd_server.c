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

    char qotds[5][100] = {
        "You are good.",
        "You are the best.",
        "You are a great programmer.",
        "CN Lab is OK if you work hard.",
        "KIIT is the best."};

    printf("Enter the protocol (udp/tcp):\n");
    scanf(" %s", protocol_choice);

    printf("Enter the port to bind to:\n");
    scanf("%hd", &port);

    if (strcmp(protocol_choice, "udp") == 0)
    {
        int sockfd;
        struct sockaddr_in servaddr, cliaddr;

        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(port);

        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        if (bind(sockfd, (const struct sockaddr *)&servaddr,
                 sizeof(servaddr)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            int random_number = rand() % 5;
            char buffer[8];
            int len, n;
            len = sizeof(cliaddr);
            char *invalid_request_message = "Invalid request.";
            n = recvfrom(sockfd, (char *)buffer, 8,
                         0, (struct sockaddr *)&cliaddr,
                         (socklen_t *)&len);
            buffer[n] = '\0';

            if (strcmp(buffer, "qotd") == 0)
            {
                sendto(sockfd, (const char *)qotds[random_number], strlen(qotds[random_number]),
                       0, (const struct sockaddr *)&cliaddr,
                       len);
            }
            else
            {
                sendto(sockfd, (const char *)invalid_request_message, strlen(invalid_request_message),
                       0, (const struct sockaddr *)&cliaddr,
                       len);
            }
        }
    }
    else if (strcmp(protocol_choice, "tcp") == 0)
    {
        int sockfd;
        struct sockaddr_in servaddr, cliaddr;

        memset(&servaddr, 0, sizeof(servaddr));
        memset(&cliaddr, 0, sizeof(cliaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(port);

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        if (bind(sockfd, (const struct sockaddr *)&servaddr,
                 sizeof(servaddr)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(sockfd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            int new_sock;
            int addrlen = sizeof(cliaddr);

            if ((new_sock = accept(sockfd, (struct sockaddr *)&cliaddr,
                                   (socklen_t *)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            int random_number = rand() % 5;
            char buffer[8];
            int len, n;
            len = sizeof(cliaddr);
            char *invalid_request_message = "Invalid request.";

            n = read(new_sock, buffer, 8);
            buffer[n] = '\0';

            if (strcmp(buffer, "qotd") == 0)
            {
                send(new_sock, qotds[random_number], strlen(qotds[random_number]), 0);
            }
            else
            {
                send(new_sock, invalid_request_message, strlen(invalid_request_message), 0);
            }
            close(new_sock);
        }
    }
    else
    {
        printf("The protocol is not supported. Exiting.");
        exit(EXIT_FAILURE);
    }
}
