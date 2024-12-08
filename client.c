#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDRESS "34.171.19.125" // Substitua pelo IP do servidor
#define SERVER_PORT 80           // Porta usada pelo servidor
#define BUFFER_SIZE 1024           // Tamanho do buffer

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    // Criação do socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar o socket");
        return 1;
    }

    // Configuração do endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // Converte o endereço IP para o formato correto
    if (inet_pton(AF_INET, SERVER_ADDRESS, &server_addr.sin_addr) <= 0) {
        perror("Endereço inválido ou não suportado");
        close(sock);
        return 1;
    }

    // Conexão ao servidor
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erro ao conectar ao servidor");
        close(sock);
        return 1;
    }

    printf("Conectado ao servidor %s:%d\n", SERVER_ADDRESS, SERVER_PORT);

    // Comunicação com o servidor
    while (1) {
        printf("Digite uma mensagem (ou 'exit' para sair): ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove o '\n' do final

        // Envia a mensagem para o servidor
        if (send(sock, message, strlen(message), 0) < 0) {
            perror("Erro ao enviar mensagem");
            break;
        }

        // Encerra a conexão se o usuário digitar 'exit'
        if (strcmp(message, "exit") == 0) {
            printf("Encerrando a conexão...\n");
            break;
        }

        // Recebe a resposta do servidor
        memset(buffer, 0, BUFFER_SIZE); // Limpa o buffer
        int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            perror("Erro ao receber resposta do servidor");
            break;
        } else if (bytes_received == 0) {
            printf("Servidor desconectou.\n");
            break;
        }

        printf("Resposta do servidor: %s\n", buffer);
    }

    // Fecha o socket
    close(sock);
    return 0;
}
