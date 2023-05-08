#include <iostream>
#include <cstring>
#include <ctime>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 7

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;

    // Создание сокета
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Ошибка при создании сокета." << std::endl;
        return 1;
    }

    // Настройка адреса сервера
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr("172.16.40.1");

    // Запрос времени у сервера
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead = sendto(sockfd, nullptr, 0, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bytesRead < 0) {
        std::cerr << "Ошибка при отправке запроса." << std::endl;
        close(sockfd);
        return 1;
    }

    // Получение ответа от сервера
    bytesRead = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE, 0, nullptr, nullptr);
    if (bytesRead < 0) {
        std::cerr << "Ошибка при получении ответа." << std::endl;
        close(sockfd);
        return 1;
    }
    // Вывод полученного ответа
    std::cout << "Полученный ответ: " << buffer << std::endl;

    // Завершение строки ответа
    buffer[bytesRead] = '\0';

    // Вывод полученного времени
    std::cout << "Текущее время: " << buffer << std::endl;

    // Закрытие сокета
    close(sockfd);

    return 0;
}

