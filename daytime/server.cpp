#include <iostream>
#include <ctime>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_address, client_address;
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
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Привязка сокета к адресу сервера
    if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Ошибка при привязке сокета к адресу сервера" << std::endl;
        return -1;
    }

    while (true) {
        socklen_t client_len = sizeof(client_address);
        memset(buffer, 0, sizeof(buffer));

        // Получение запроса от клиента
        ssize_t bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                          (struct sockaddr*)&client_address, &client_len);
        if (bytes_received == -1) {
            std::cerr << "Ошибка при получении запроса от клиента" << std::endl;
            continue;
        }

        // Получение текущего времени
        time_t current_time;
        time(&current_time);
        char* time_str = ctime(&current_time);

        // Отправка времени клиенту
        sendto(sockfd, time_str, strlen(time_str), 0,
               (struct sockaddr*)&client_address, client_len);
    }

    // Закрытие сокета (не будет достигнуто в данной программе)
    close(sockfd);

    return 0;
}
