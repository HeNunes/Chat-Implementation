//
// Created by Vicenzo D’Arezzo on 01/07/24.
//

#ifndef CHAT_REDES_CLIENT_H
#define CHAT_REDES_CLIENT_H

#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>

class Client {

private:
    int sock = 0;
    struct sockaddr_in serv_addr;
    const int PORT = 3000;
    const int ip_add = htonl(INADDR_LOOPBACK);

public:
    Client();
    ~Client();
    void start();
    void conversation();
};


#endif //CHAT_REDES_CLIENT_H
