#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#define TRUE 1
#define FALSE 0
#define PORT 8889

int isPrimeFn(int number)
{
    int i;
    for (i=2; i<number; i++) {
        if (number % i == 0 && i != number) return FALSE;
    }
    return TRUE;
}
int isArmstrongFn(int n)
{
    int r, sum = 0, temp;
    temp = n;
    while (n > 0)
    {
        r = n % 10;
        sum = sum + (r * r * r);
        n = n / 10;
    }
    return temp == sum ? TRUE : FALSE;
}
int isOddFn(int number)
{
    return number % 2 == 0 ? FALSE : TRUE;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        printf("bind failed\n");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        printf("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Server started on PORT %d\n", PORT);
    int a, b;
    int number = read(new_socket, &a, sizeof(int));
    int isOdd, isArmstrong, isPrime;
    isOdd = isOddFn(a);
    isPrime = isPrimeFn(a);
    isArmstrong = isArmstrongFn(a);

    printf("The number %d is prime: %d, is Arms: %d, isOdd: %d\n", a, isPrime, isOdd);
    send(new_socket, &isOdd, sizeof(int), 0);
    send(new_socket, &isPrime, sizeof(int), 0);
    send(new_socket, &isArmstrong, sizeof(int), 0);
    printf("Sent\n");

    close(server_fd);

    return 0;
}
