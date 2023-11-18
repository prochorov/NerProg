#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket, nBytes;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);

    // Создание сокета
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Заполнение структуры адреса сервера
    memset((char *)&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Привязка сокета к адресу сервера
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind");
        exit(1);
    }

    // Прослушивание сокета
    if (listen(serverSocket, 5) == -1) {
        perror("listen");
        exit(1);
    }

    std::cout << "Server waiting for connections on port " << SERVER_PORT << "..." << std::endl;

    // Принятие подключения от клиента
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addr_len)) == -1) {
        perror("accept");
        exit(1);
    }

    // Получение данных от клиента
    if ((nBytes = recv(clientSocket, buffer, BUFFER_SIZE, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buffer[nBytes] = '\0';
    std::cout << "Received from client: " << buffer << std::endl;

    // Отправка данных обратно клиенту
    send(clientSocket, buffer, strlen(buffer), 0);

    // Закрытие сокетов
    close(clientSocket);
    close(serverSocket);

    return 0;
}
