//
// Created by Vicenzo D’Arezzo on 01/07/24.
//

#ifndef CHAT_REDES_SERVER_H
#define CHAT_REDES_SERVER_H

#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>

class Server {
private:
    int server_fd, conversation_sckt;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    const int PORT = 3000;
    const int ip_add = htonl(INADDR_LOOPBACK);

public:
    /**
     * MÉTODO CONSTRUTOR:
     *
     * @brief:
     *  Inicializa o objeto abrindo e configurando um socket
     *  no endereço de loopback + porta definida na classe.\;
     *  esse socket é configurado para uma comunicação
     *  duplex com, no máximo, um cliente conectado.
     *
     * Em caso de erro, imprime mensagem na saída de erro
     * e encerra o programa
     */
    Server();
    ~Server();

    /**
     * INICIALIZADOR:
     *
     * @brief:
     *  Realiza espera ocupada por uma tentativa de conexão
     *  no endereço especificado, realizando o handshake e
     *  iniciando a conversa em caso de sucesso.
     *
     * Em caso de erro, imprime mensagem na saída de erro
     * e encerra o programa
     */
    void start();
    void stop();

    /**
     * LOOP DE CONVERSAÇÃO:
     *
     * @brief:
     *  Loop infinito em que ocorre a conversa entre ambas as partes.
     *  A conversação é encerrada quando ...
     *
     */
    void conversation();

    void handle_signal(int signal);
};



#endif //CHAT_REDES_SERVER_H
