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
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Заполнение структуры адреса сервера
    memset((char *)&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Подключение к серверу
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("connect");
        exit(1);
    }

    // Отправка данных на сервер
    std::cout << "Enter message to send to server: ";
    std::cin.getline(buffer, BUFFER_SIZE);
    send(clientSocket, buffer, strlen(buffer), 0);

    // Получение данных от сервера
    if ((nBytes = recv(clientSocket, buffer, BUFFER_SIZE, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buffer[nBytes] = '\0';
    std::cout << "Received from server: " << buffer << std::endl;

    // Закрытие сокета
    close(clientSocket);

    return 0;
}
