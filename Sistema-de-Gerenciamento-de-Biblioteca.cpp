#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Livro {
private:
    static int contadorLivros;
    int id;
    string titulo;
    string autor;
    int numCopias;

public:
    Livro(string t, string a, int n) : id(contadorLivros++), titulo(t), autor(a), numCopias(n) {}

    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getNumCopias() const { return numCopias; }
    int getId() const { return id; }

    void emprestarLivro() {
        if (numCopias > 0) {
            numCopias--;
            cout << "Livro emprestado com sucesso!\n";
        } else {
            cout << "Não há cópias disponíveis para empréstimo.\n";
        }
    }

    void devolverLivro() {
        numCopias++;
        cout << "Livro devolvido com sucesso!\n";
    }
};

int Livro::contadorLivros = 0;

class Usuario {
private:
    static int contadorUsuarios;
    int id;
    string nome;
    vector<Livro*> livrosEmprestados;

public:
    Usuario(string n) : id(contadorUsuarios++), nome(n) {}

    string getNome() const { return nome; }
    int getId() const { return id; }

    void emprestarLivro(Livro* livro) {
        if (livro->getNumCopias() > 0) {
            livrosEmprestados.push_back(livro);
            livro->emprestarLivro();
        } else {
            cout << "Não foi possível emprestar o livro. Não há cópias disponíveis.\n";
        }
    }

    void devolverLivro(Livro* livro) {
        auto it = find(livrosEmprestados.begin(), livrosEmprestados.end(), livro);
        if (it != livrosEmprestados.end()) {
            livrosEmprestados.erase(it);
            livro->devolverLivro();
        } else {
            cout << "Este livro não está emprestado para você.\n";
        }
    }

    void listarLivrosEmprestados() {
        cout << "Livros emprestados para " << nome << ":\n";
        for (Livro* livro : livrosEmprestados) {
            cout << " - " << livro->getTitulo() << " por " << livro->getAutor() << "\n";
        }
    }
};

int Usuario::contadorUsuarios = 0;

class Biblioteca {
private:
    static vector<Livro> listaLivros;
    static vector<Usuario> listaUsuarios;

public:
    static void adicionarLivro(const Livro& livro) {
        listaLivros.push_back(livro);
    }

    static void adicionarUsuario(const Usuario& usuario) {
        listaUsuarios.push_back(usuario);
    }

    static void registrarEmprestimo(int idUsuario, int idLivro) {
        if (idUsuario >= 0 && idUsuario < listaUsuarios.size() && idLivro >= 0 && idLivro < listaLivros.size()) {
            Usuario& usuario = listaUsuarios[idUsuario];
            Livro& livro = listaLivros[idLivro];

            time_t now = time(0);
            tm* localTime = localtime(&now);
            cout << "Empréstimo registrado em: " << localTime->tm_mday << "/" << localTime->tm_mon + 1 << "/" << localTime->tm_year + 1900 << "\n";

            usuario.emprestarLivro(&livro);
        } else {
            cout << "Usuário ou livro inválido.\n";
        }
    }

    static void verificarDisponibilidade(int idLivro) {
        if (idLivro >= 0 && idLivro < listaLivros.size()) {
            Livro& livro = listaLivros[idLivro];
            cout << "Livro: " << livro.getTitulo() << "\n";
            if (livro.getNumCopias() > 0) {
                cout << "Disponível. Número de cópias disponíveis: " << livro.getNumCopias() << "\n";
            } else {
                cout << "Não disponível.\n";
            }
        } else {
            cout << "Livro inválido.\n";
        }
    }

    static void listarLivrosEmprestadosPorUsuario(int idUsuario) {
        if (idUsuario >= 0 && idUsuario < listaUsuarios.size()) {
            Usuario& usuario = listaUsuarios[idUsuario];
            usuario.listarLivrosEmprestados();
        } else {
            cout << "Usuário inválido.\n";
        }
    }

    static void devolverLivro(int idUsuario, int idLivro) {
        if (idUsuario >= 0 && idUsuario < listaUsuarios.size() && idLivro >= 0 && idLivro < listaLivros.size()) {
            Usuario& usuario = listaUsuarios[idUsuario];
            Livro& livro = listaLivros[idLivro];

            usuario.devolverLivro(&livro);
        } else {
            cout << "Usuário ou livro inválido.\n";
        }
    }
};

vector<Livro> Biblioteca::listaLivros;
vector<Usuario> Biblioteca::listaUsuarios;

void exibirMenu() {
    cout << "\n==== Sistema de Gerenciamento de Biblioteca ====\n";
    cout << "1. Adicionar Livro\n";
    cout << "2. Adicionar Usuário\n";
    cout << "3. Emprestar Livro\n";
    cout << "4. Devolver Livro\n";
    cout << "5. Verificar Disponibilidade de Livro\n";
    cout << "6. Listar Livros Emprestados por Usuário\n";
    cout << "7. Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    int escolha;

    do {
        exibirMenu();
        cin >> escolha;
        cin.ignore(); // Limpa o buffer do teclado

        switch (escolha) {
            case 1: {
                string titulo, autor;
                int numCopias;

                cout << "Informe o título do livro: ";
                getline(cin, titulo);

                cout << "Informe o autor do livro: ";
                getline(cin, autor);

                cout << "Informe o número de cópias disponíveis: ";
                cin >> numCopias;
                cin.ignore(); // Limpa o buffer do teclado

                Livro novoLivro(titulo, autor, numCopias);
                Biblioteca::adicionarLivro(novoLivro);
                cout << "Livro adicionado com sucesso! ID: " << novoLivro.getId() << "\n";
                break;
            }
            case 2: {
                string nome;

                cout << "Informe o nome do usuário: ";
                getline(cin, nome);

                Usuario novoUsuario(nome);
                Biblioteca::adicionarUsuario(novoUsuario);
                cout << "Usuário adicionado com sucesso! ID: " << novoUsuario.getId() << "\n";
                break;
            }
            case 3: {
                int idUsuario, idLivro;

                cout << "Informe o ID do usuário: ";
                cin >> idUsuario;
                cout << "Informe o ID do livro: ";
                cin >> idLivro;

                Biblioteca::registrarEmprestimo(idUsuario, idLivro);
                break;
            }
            case 4: {
                int idUsuario, idLivro;

                cout << "Informe o ID do usuário: ";
                cin >> idUsuario;
                cout << "Informe o ID do livro: ";
                cin >> idLivro;

                Biblioteca::devolverLivro(idUsuario, idLivro);
                break;
            }
            case 5: {
                int idLivro;

                cout << "Informe o ID do livro: ";
                cin >> idLivro;

                Biblioteca::verificarDisponibilidade(idLivro);
                break;
            }
            case 6: {
                int idUsuario;

                cout << "Informe o ID do usuário: ";
                cin >> idUsuario;

                Biblioteca::listarLivrosEmprestadosPorUsuario(idUsuario);
                break;
            }
            case 7:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida. Tente novamente.\n";
                break;
        }
    } while (escolha != 7);

    return 0;
}
