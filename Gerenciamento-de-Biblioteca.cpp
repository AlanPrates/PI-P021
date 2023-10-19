#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

class Livro {
private:
    std::string titulo;
    std::string autor;
    int copias_disponiveis;

public:
    Livro(std::string t, std::string a, int c) : titulo(t), autor(a), copias_disponiveis(c) {}

    std::string getTitulo() const { return titulo; }
    std::string getAutor() const { return autor; }
    int getCopiasDisponiveis() const { return copias_disponiveis; }

    void emprestarLivro() {
        if (copias_disponiveis > 0) {
            copias_disponiveis--;
            std::cout << "Livro emprestado com sucesso!" << std::endl;
        } else {
            std::cout << "Desculpe, não há cópias disponíveis no momento." << std::endl;
        }
    }

    void devolverLivro() {
        copias_disponiveis++;
        std::cout << "Livro devolvido com sucesso!" << std::endl;
    }

    void editarLivro(std::string novo_titulo, std::string novo_autor, int novas_copias) {
        titulo = novo_titulo;
        autor = novo_autor;
        copias_disponiveis = novas_copias;
    }
};

class Usuario {
private:
    std::string nome;

public:
    Usuario(std::string n) : nome(n) {}

    std::string getNome() const { return nome; }

    static void emprestarLivro(Usuario& usuario, Livro& livro) {
        livro.emprestarLivro();
        std::cout << usuario.getNome() << " pegou emprestado o livro: " << livro.getTitulo() << std::endl;
    }

    static void devolverLivro(Usuario& usuario, Livro& livro) {
        livro.devolverLivro();
        std::cout << usuario.getNome() << " devolveu o livro: " << livro.getTitulo() << std::endl;
    }
};

class Biblioteca {
private:
    static std::vector<Livro> livros;

public:
    static void adicionarLivro(const Livro& livro) {
        livros.push_back(livro);
    }

    static void editarLivro(const std::string& titulo, const std::string& novo_titulo, const std::string& novo_autor, int novas_copias) {
        auto it = std::find_if(livros.begin(), livros.end(), [&titulo](const Livro& livro) {
            return livro.getTitulo() == titulo;
        });

        if (it != livros.end()) {
            it->editarLivro(novo_titulo, novo_autor, novas_copias);
        } else {
            std::cout << "Livro não encontrado." << std::endl;
        }
    }

    static void removerLivro(const std::string& titulo) {
        auto it = std::remove_if(livros.begin(), livros.end(), [&titulo](const Livro& livro) {
            return livro.getTitulo() == titulo;
        });

        if (it != livros.end()) {
            livros.erase(it, livros.end());
            std::cout << "Livro removido com sucesso." << std::endl;
        } else {
            std::cout << "Livro não encontrado." << std::endl;
        }
    }

    static void listarLivros() {
        for (const Livro& livro : livros) {
            std::cout << "Título: " << livro.getTitulo() << ", Autor: " << livro.getAutor() 
                      << ", Cópias Disponíveis: " << livro.getCopiasDisponiveis() << std::endl;
        }
    }

    static Livro* encontrarLivroPorTitulo(const std::string& titulo) {
        for (Livro& livro : livros) {
            if (livro.getTitulo() == titulo) {
                return &livro;
            }
        }
        return nullptr;
    }

    static void salvarDados() {
        std::ofstream arquivo("dados_biblioteca.txt");

        if (arquivo.is_open()) {
            for (const Livro& livro : livros) {
                arquivo << livro.getTitulo() << "," << livro.getAutor() << "," << livro.getCopiasDisponiveis() << "\n";
            }
            arquivo.close();
            std::cout << "Dados salvos com sucesso." << std::endl;
        } else {
            std::cout << "Erro ao abrir o arquivo para salvar os dados." << std::endl;
        }
    }

    static void carregarDados() {
        std::ifstream arquivo("dados_biblioteca.txt");

        if (arquivo.is_open()) {
            std::string linha;
            while (std::getline(arquivo, linha)) {
                std::string titulo, autor;
                int copias;

                std::istringstream ss(linha);
                std::getline(ss, titulo, ',');
                std::getline(ss, autor, ',');
                ss >> copias;

                adicionarLivro(Livro(titulo, autor, copias));
            }
            arquivo.close();
           
            std::cout << "Dados carregados com sucesso." << std::endl;
        } else {
            std::cout << "Não foi possível abrir o arquivo para carregar os dados." << std::endl;
        }
    }
};

std::vector<Livro> Biblioteca::livros;

int main() {
    Biblioteca::carregarDados();

    int escolha;
    do {
        std::cout << "Menu de Opções:" << std::endl;
        std::cout << "1. Adicionar Livro" << std::endl;
        std::cout << "2. Editar Livro" << std::endl;
        std::cout << "3. Remover Livro" << std::endl;
        std::cout << "4. Listar Livros" << std::endl;
        std::cout << "5. Salvar Dados" << std::endl;
        std::cout << "6. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
            case 1: {
                std::string titulo, autor;
                int copias;

                std::cout << "Informe o título: ";
                std::cin.ignore();
                std::getline(std::cin, titulo);

                std::cout << "Informe o autor: ";
                std::getline(std::cin, autor);

                std::cout << "Informe o número de cópias disponíveis: ";
                std::cin >> copias;

                Biblioteca::adicionarLivro(Livro(titulo, autor, copias));
                break;
            }
            case 2: {
                std::string titulo, novo_titulo, novo_autor;
                int novas_copias;

                std::cout << "Informe o título do livro a ser editado: ";
                std::cin.ignore();
                std::getline(std::cin, titulo);

                std::cout << "Novo Título: ";
                std::getline(std::cin, novo_titulo);

                std::cout << "Novo Autor: ";
                std::getline(std::cin, novo_autor);

                std::cout << "Novo Número de Cópias: ";
                std::cin >> novas_copias;

                Biblioteca::editarLivro(titulo, novo_titulo, novo_autor, novas_copias);
                break;
            }
            case 3: {
                std::string titulo;
                std::cout << "Informe o título do livro a ser removido: ";
                std::cin.ignore();
                std::getline(std::cin, titulo);
                Biblioteca::removerLivro(titulo);
                break;
            }
            case 4:
                Biblioteca::listarLivros();
                break;
            case 5:
                Biblioteca::salvarDados();
                break;
            case 6:
                break;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
                break;
        }

    } while (escolha != 6);

    return 0;
}
