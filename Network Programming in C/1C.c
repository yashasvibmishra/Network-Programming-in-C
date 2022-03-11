#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8889
#define TRUE 1
#define FALSE 0

char *getval(int a)
{
    return a == FALSE ? "FALSE" : "TRUE";
}

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    int a;

    printf("Enter the number:");
    scanf("%d", &a);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {

        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, &a, sizeof(int), 0);
    printf("Number sent\n");

    int isOdd, isArmstrong, isPrime;
    valread = read(sock, &isOdd, sizeof(int));
    valread = read(sock, &isPrime, sizeof(int));
    valread = read(sock, &isArmstrong, sizeof(int));
    printf("The number is prime: %s\n", getval(isPrime));
    printf("The number is Armstrong: %s\n", getval(isArmstrong));
    printf("The number is Odd: %s\n", getval(isOdd));

    return 0;
}
