#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_address;
    char buffer[1024];

    // Создание сокета
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        return -1;
    }

    // Настройка адреса сервера
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(13); // Порт daytime

    // IP-адрес сервера daytime (здесь укажите IP-адрес сервера)
    const char* server_ip = "127.0.0.1";
    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
        std::cerr << "Ошибка при настройке адреса сервера" << std::endl;
        return -1;
    }

    // Отправка запроса к серверу
    sendto(sockfd, "Запрос", sizeof("Запрос"), 0,
           (struct sockaddr*)&server_address, sizeof(server_address));

    // Получение ответа от сервера
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);

    // Вывод ответа
    std::cout << "Ответ от сервера: " << buffer << std::endl;

    // Закрытие сокета
    close(sockfd);

    return 0;
}
