#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

std::string getCurrentDateTime() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    return std::string(buffer);
}

int main() {
    int serverSocket, nBytes;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);

    // Создание сокета
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
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

    std::cout << "Server waiting for data on port " << SERVER_PORT << "..." << std::endl;

    // Получение данных от клиента
    if ((nBytes = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }

    buffer[nBytes] = '\0';

    // Получение текущей даты и времени
    std::string dateTime = getCurrentDateTime();

    // Отправка данных обратно клиенту
    if (sendto(serverSocket, dateTime.c_str(), dateTime.length(), 0, (struct sockaddr *)&clientAddr, addr_len) == -1) {
        perror("sendto");
        exit(1);
    }

    // Закрытие сокета
    close(serverSocket);

    return 0;
}
