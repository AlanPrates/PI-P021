# Sistema de Gerenciamento de Biblioteca

Este é um projeto de um Sistema de Gerenciamento de Biblioteca implementado em C++.

## Equipe

- Alan Prates
- Daniel Monteiro
- Danilo Silveira
- Paulo Pereira

## Descrição

O sistema permite aos usuários realizar as seguintes operações:

- Adicionar livros à biblioteca, incluindo informações como título, autor e número de cópias disponíveis.
- Registrar empréstimos de livros para os usuários, controlando quem pegou emprestado e quando.
- Verificar a disponibilidade de um livro.
- Listar os livros emprestados por um usuário específico.

## Estrutura do Projeto

O projeto é dividido em classes `Livro` e `Usuario`, com métodos estáticos para gerenciar a lista de livros e empréstimos.

## Como Compilar e Executar

Para compilar o projeto, utilize um compilador C++ compatível com C++11 ou superior.

```bash
g++ -std=c++11 main.cpp Livro.cpp Usuario.cpp -o biblioteca
