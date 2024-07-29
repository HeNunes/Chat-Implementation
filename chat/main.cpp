#include <thread>
#include "server.h"
#include "client.h"

void runServer() {
    Server server = Server();
    server.start();
}

void runClient() {
    Client client = Client();
    client.start();
}

int main() {


    std::cout << "Escolha o modo de operação:" << std::endl;
    std::cout << "1. Servidor" << std::endl;
    std::cout << "2. Cliente" << std::endl;

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // Inicia o servidor em uma nova thread
        std::thread serverThread(runServer);
        serverThread.join(); // Espera a thread do servidor terminar
    } else if (choice == 2) {
        // Inicia o cliente em uma nova thread
        std::thread clientThread(runClient);
        clientThread.join(); // Espera a thread do cliente terminar
    } else {
        std::cout << "Escolha inválida. Encerrando programa." << std::endl;
    }

    return 0;
}