#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main()
{
    struct sockaddr_in {
        short sin_family;
        unsigned short sin_port;
        struct in_addr sin_addr;
        char sin_zero[8];
    };
    struct in_addr {
        unsigned long s_addr;
    };

    int s = socket(AF_INET, SOCK_STREAM, 0);


    sockaddr_in * self_addr = new (sockaddr_in);
    self_addr->sin_family = AF_INET;
    self_addr->sin_port = htons(7777);
    self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(s,(const sockaddr*) self_addr,sizeof(sockaddr_in));
    if(b == -1) {
        cout << "Binding error\n";
        return 1;
    }
    int rl = listen(s, 5);
    if(rl == -1) {
        cout << "Listening error\n";
        return 1;
    }
    while(true) {
        sockaddr_in * client_addr = new sockaddr_in;
        socklen_t len = sizeof (sockaddr_in);
        int work_sock = accept(s, (sockaddr*)(client_addr), &len);
        if(work_sock == -1) {
            cout << "Error #2\n";
        } else {
            cout << "Successfull client connection!\n";
            char *msg = new char [2560000];
            recv(work_sock, msg, 2560000, 0);
            cout << "Message from client: " << msg;
            send(work_sock, msg, 10000, 0);
            cout << "Message was returned to client!\n";
            delete [] msg;
            close(work_sock);
        }
    }
    close(s);
    return 0;
}
