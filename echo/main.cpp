#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int BUFFER_SIZE = 1024;

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    // Создание сокета
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Настройка адреса сервера
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(7); // Порт сервера
    serverAddress.sin_addr.s_addr = inet_addr("172.16.40.1"); // IP-адрес сервера

    // Установка соединения с сервером
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Ошибка соединения с сервером" << std::endl;
        return 1;
    }

    // Ввод сообщения для отправки серверу
    std::string message;
    std::cout << "Введите сообщение для отправки серверу: ";
    std::getline(std::cin, message);

    // Отправка сообщения серверу
    if (send(clientSocket, message.c_str(), message.length(), 0) == -1) {
        std::cerr << "Ошибка отправки сообщения" << std::endl;
        return 1;
    }

    // Получение ответа от сервера
    memset(buffer, 0, sizeof(buffer)); // Очистка буфера
    if (recv(clientSocket, buffer, BUFFER_SIZE, 0) == -1) {
        std::cerr << "Ошибка получения ответа" << std::endl;
        return 1;
    }

    std::cout << "Полученный ответ: " << buffer << std::endl;

    // Закрытие соединения
    close(clientSocket);

    return 0;
}

