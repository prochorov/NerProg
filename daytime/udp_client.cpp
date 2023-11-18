#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int clientSocket, nBytes;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr;

    // Создание сокета
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Заполнение структуры адреса сервера
    memset((char *)&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Отправка запроса на сервер
    if (sendto(clientSocket, "Request", strlen("Request"), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("sendto");
        exit(1);
    }

    // Получение ответа от сервера
    socklen_t addr_len = sizeof(serverAddr);
    if ((nBytes = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverAddr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }

    buffer[nBytes] = '\0';
    std::cout << "Received from server: " << buffer << std::endl;

    // Закрытие сокета
    close(clientSocket);

    return 0;
}
