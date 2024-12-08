#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 80      // Porta para comunicação
#define BUFFER_SIZE 1024       // Tamanho do buffer para mensagens

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    // Criação do socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar o socket do servidor");
        return 1;
    }

    // Configuração do endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Aceitar qualquer IP
    server_addr.sin_port = htons(SERVER_PORT);

    // Associa o socket ao endereço e porta
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erro ao associar o socket ao endereço");
        return 1;
    }

    // Coloca o servidor para ouvir conexões
    if (listen(server_socket, 5) < 0) {
        perror("Erro ao colocar o servidor para escutar");
        return 1;
    }

    printf("\nServidor está ouvindo na porta %d...\n", SERVER_PORT);

    // Loop para aceitar múltiplas conexões
    while (1) {
        client_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

        if (client_socket < 0) {
            perror("Erro ao aceitar conexão");
            continue;
        }

        printf("\nConexão recebida de %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Processa as mensagens do cliente
        while (1) {
            memset(buffer, 0, BUFFER_SIZE); // Limpa o buffer
            int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
            if (bytes_received < 0) {
                perror("Erro ao receber mensagem do cliente");
                break;
            } else if (bytes_received == 0) {
                printf("Cliente desconectado.\n");
                break;
            }

            // Exibe a mensagem recebida do cliente
            printf("Mensagem recebida do cliente: %s\n", buffer);

            // Envia uma resposta para o cliente
            char response[] = "Mensagem recebida com sucesso!";
            send(client_socket, response, strlen(response), 0);
        }

        // Fecha o socket do cliente
        close(client_socket);
        printf("Conexão encerrada com o cliente.\n");
    }

    // Fecha o socket do servidor
    close(server_socket);
    return 0;
}
