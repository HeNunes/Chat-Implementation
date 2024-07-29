#include "server.h"
#include <csignal>


const int BUFFER_SIZE = 1024;


Server::Server() {


    // Tenta abrir um socket genérico duplex usando IPv4 ;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Falha ao abrir o socket no servidor;\n");
        exit(EXIT_FAILURE);
    }

    // Configurando o socket aberto para permitir a utilização do mesmo IP e porta,
    // de modo que o cliente possa abrir sua conexão sobre o mesmo endereço ;
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
        perror("Falha ao configurar SO_REUSEADDR no socket do servidor\n");
        exit(EXIT_FAILURE);
    }
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))){
        perror("Falha ao configurar SO_REUSEPORT no socket do servidor\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; // IPv4 ;
    address.sin_addr.s_addr = ip_add; // endereço de LoopBack ;
    address.sin_port = htons(PORT);

    // Ativando o socket no endereço configurado: Loopback porta 3000 - 127.0.0.1 - 3000 ;
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Falha ao associar o socket aberto ao endereço de loopback na porta 3000\n");
        exit(EXIT_FAILURE);
    }

    // Verificando a escuta no canal ;
    // O parâmetro 1 limita o número máximo de conexões suportadas;

    if(listen(server_fd, 1) < 0){
        perror("Falha na escuta teste no socket\n");
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    std::cout << "ENCERRANDO CONEXÃO SERVIDOR\n";
    close(conversation_sckt);
    conversation_sckt = -1;

    close(server_fd);
    server_fd = -1;
}

void Server::start() {

    std::cout << "Iniciando Comunicação no endereço: esperando conexão na porta [" << PORT << "]" << std::endl;

    // [ESPERA OCUPADA POR CONEXÃO] - Handshake ;
    // Ao encontrar uma conexão, transfere o canal para conversation_sckt ;
    if ((conversation_sckt = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Erro ao aceitar conexão no socket\n");
        exit(EXIT_FAILURE);
    }
    std::cout << "CONEXÃO ESTABELECIDA - Iniciando Chat :D !\n\n";
    conversation();
}

void Server::conversation() {

    char buffer[BUFFER_SIZE] = {0};
    std::string message;

    while (true) {

        // A comunicação utiliza um buffer de tamanho constante;

        // O pipeline do método de conversação é:
        //      -> ler mensagem do socket;
        //      -> se houver mensagem, imprimi-la;
        //      -> ler mensagem da entrada padrão;
        //      -> se houver mensagem, enviá-la;
        memset(buffer, 0, sizeof(buffer));
        size_t read_data = read(conversation_sckt, buffer, 1024);
        if (read_data == 0) break;
        std::cout << "[Correspondente]: " << buffer << std::endl;

        if(strcmp(buffer, "![exit]") == 0){
            std::cout << "Conexão encerrada pelo cliente.\n";
            break;
        }

        std::cout << "[Eu]: ";
        std::getline(std::cin, message);

        while(message.empty()){
            std::getline(std::cin, message);
        }

        if(message == "![exit]") {
            send(conversation_sckt, message.c_str(), message.length(), 0);
            break;
        }

        send(conversation_sckt, message.c_str(), message.length(), 0);
    }
}
