# 📡 Projeto RPC em C - Somatória e Subtração

Este projeto foi desenvolvido como atividade da disciplina de Sistemas Distribuídos. Ele implementa um sistema de chamada de procedimento remoto (**RPC**) em linguagem C, com duas operações básicas: **soma** e **subtração**.

## ✅ Funcionalidades

- Soma de dois números inteiros via RPC.
- Subtração de dois números inteiros via RPC.
- Comunicação entre cliente e servidor usando a ferramenta `rpcgen`.

## 📁 Estrutura dos Arquivos

- `calculadora.x`: define as operações remotas (soma e subtração).
- `cliente.c`: código do cliente que chama as funções remotas.
- `servidor.c`: implementa as funções chamadas remotamente.
- `calculadora_clnt.c`, `calculadora_svc.c`, `calculadora.h`: arquivos gerados automaticamente com `rpcgen`.

## 🛠️ Como Compilar e Executar

1. Gere os arquivos base com o `rpcgen`:
   ```bash
   rpcgen calculadora.x

compile o servidor:
gcc -o servidor calculadora_svc.c servidor.c -lnsl

compile o cliente:
gcc -o cliente calculadora_clnt.c cliente.c -lnsl

execute o servidor:
./servidor

execute o cliente:
./cliente
