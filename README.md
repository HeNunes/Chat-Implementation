# Chat-Implementation

## Chat TCP em C++

Este é um projeto simples de chat em C++ que permite a comunicação entre dois terminais em um mesmo computador usando sockets TCP. O projeto usa a programação orientada a objetos e as bibliotecas padrão de comunicação TCP do C++.

## Equipe

- Enzo Nunes Sedenho - 13671810
- Vicenzo D’Arezzo Zilio - 13671790
- Lucas de Souza Brandão - 13695021
- Miller Matheus Lima Anacleto Rocha - 13727954

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- `server.h` e s`server.cpp`: Implementam a classe `Server` que gerencia a conexão TCP do lado do servidor.
- `client.h` e `client.cpp`: Implementam a classe `Client` que gerencia a conexão TCP do lado do cliente.
- `main.cpp`: Contém a função `main` que inicia o servidor ou o cliente em threads separadas.

## Funcionalidades

- **Servidor**: Aceita conexões de clientes, envia e recebe mensagens do cliente.
- **Cliente**: Conecta-se ao servidor, envia e recebe mensagens do servidor.

## Requisitos

- Compilador C++ (por exemplo, `g++`)
- Sistema operacional Linux
- CMake 3.28+

## Como Compilar

Para compilar o código **pela primeira vez**, use o seguinte comando:

```bash
mkdir build
cd build
cmake ..
```

Em seguida e nas demais vezes apenas use o comando:

```bash
make
```

## Como Executar

Para executar o programa, basta abrir dois terminais e em ambos rodar o executável `chat_redes`:

```bash
./chat_redes
```

Em seguida escolha o primeiro para ser o Servidor e o segundo para ser o Cliente.

## Funcionamento

1. **Servidor**: O servidor escuta na porta 3000 e espera conexões de clientes. Quando um cliente se conecta, o servidor pode enviar e receber mensagens.
2. **Cliente**: O cliente se conecta ao servidor na porta 3000. Após a conexão, o cliente pode enviar e receber mensagens.

### Exemplo de Uso

1. Abra dois terminais.
2. No primeiro terminal, execute o comando para iniciar o chat e escolha a opção 1 para executar o servidor:
    
    ```bash
    ./chat_redes
    1
    ```
    
3. No segundo terminal, execute o comando para iniciar o chat e escolha a opção 2 para executar o cliente:
    
    ```bash
    ./chat_redes
    2
    ```
    
4. Nesse momento o cliente pode enviar a primeira mensagem.
5. O servidor recebe a mensagem e pode responder o cliente.
6. A comunicação continua alternadamente.
7. Para finalizar o chat digite `![exit]` em qualquer dos dois terminais.

### Notas

- O servidor deve ser iniciado antes do cliente para que a conexão possa ser estabelecida.
- As mensagens enviadas pelo servidor e pelo cliente aparecerão nos respectivos terminais.
- Ambos os terminais mostram uma indicação de quais mensagens foram enviadas e quais foram recebidas.
