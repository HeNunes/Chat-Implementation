//
// Created by Vicenzo D’Arezzo on 01/07/24.
//

#include "client.h"
#include <chrono> 
#include <thread>

const int BUFFER_SIZE = 1024;
const int RETRY_COUNT = 5;
const int RETRY_DELAY = 5;

Client::Client() {
    for (int i = 0; i < RETRY_COUNT; ++i) {
        // Cria um objeto de socket para lidar com a conexão ;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("Falha ao abrir o socket no cliente;\n");
            exit(EXIT_FAILURE);
        }
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = ip_add;
        serv_addr.sin_port = htons(PORT);

        // Configura a conexão usando o endereço de loopback em IPv4;
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            perror("Falha ao endereçar o objeto de socket no cliente\n");
            exit(EXIT_FAILURE);
        }

        // [Estabelecimento de Conexão] - handshake
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cout << "Tentativa de conexão falhou. Tentativa " << (i + 1) << " de " << RETRY_COUNT << ". Retentando em " << RETRY_DELAY << " segundos...\n";
            close(sock);
            std::this_thread::sleep_for(std::chrono::seconds(RETRY_DELAY));
        }else{
            // Connection successful
            std::cout << "Conexão estabelecida com sucesso!\n";
            return;
        }
    }

    perror("Falha ao estabelecer a conexão do cliente ao servidor\n");
    exit(EXIT_FAILURE);
}

Client::~Client() {
    std::cout << "ENCERRANDO CONEXÃO CLIENTE\n";
    close(sock);
    sock = -1;
}

void Client::start() {
    conversation();
}

void Client::conversation() {

    char buffer[BUFFER_SIZE] = {0};
    std::string message;

    // A comunicação utiliza um buffer de tamanho constante;

    // O pipeline do método de conversação é:
    //
    //      -> ler mensagem da entrada padrão;
    //      -> se houver mensagem, enviá-la;
    //      -> ler mensagem do socket;
    //      -> se houver mensagem, imprimi-la;
    while (true) {

        std::cout << "[Eu]: ";
        std::getline(std::cin, message);


        while(message.empty()){
            std::getline(std::cin, message);
        }

        if (message == "![exit]") {
            send(sock, message.c_str(), message.length(), 0);
            break;
        }

        // if(message == "\0" || message == "\n"){
        send(sock, message.c_str(), message.length(), 0);
        memset(buffer, 0, sizeof(buffer));
        size_t read_data = read(sock, buffer, 1024);
        if (read_data == 0) break;
        std::cout << "[Correspondente]: " << buffer << std::endl;

        if (strcmp(buffer, "![exit]") == 0) {
            std::cout << "Conexão encerrada pelo servidor.\n";
            break;
        }
    }
}

