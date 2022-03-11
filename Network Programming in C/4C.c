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

struct student
{
    int id;
    char name[20];
};

// Driver code
int main()
{
    struct student st;
    strcpy(st.name, "lekha");
    st.id = 561;
    int sockfd;
    struct sockaddr_in servaddr;

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

    int n, len = sizeof(servaddr);

    sendto(sockfd, (const struct student*)&st, sizeof(struct student),
           0, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));
    printf("Struct sent.\n");
    float ans;
    n = recvfrom(sockfd, ( struct student*)&st, sizeof( struct student ),
                 0, (struct sockaddr *)&servaddr,
                 &len);

    printf("Id sent by server: %d\n Name :%s\n", st.id, st.name);

    return 0;
