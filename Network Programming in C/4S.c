#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
struct student
{
    int id;
    char name[20];
};

int main(int argc, char const *argv[])
{

    struct student st;
    int sockfd;
    struct sockaddr_in serveraddr, clientaddr;
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
    int n = recvfrom(sockfd, ( struct student *)&st, sizeof(struct student ),
                     0, (struct sockaddr *)&clientaddr,
                     &len);
    printf("Struct recieved.\n");
    printf("Id sent by client: %d\n Name:%s", st.id, st.name);
    int num = st.id;
     st.id = 0;
    while (num > 0) {
        st.id = st.id * 10 + num % 10;
        num = num / 10;
    }
   
    sendto(sockfd, (const struct student *)&st, sizeof(struct student),
           0, (const struct sockaddr *)&clientaddr,
           sizeof(clientaddr));
    return 0;
}
