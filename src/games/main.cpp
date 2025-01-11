#include <iostream>
#include <unordered_map>
#include <regex>
#include "jogador.hpp"
#include "utils.hpp"

bool validarEmail(const std::string& email) {
    const std::regex padraoEmail(R"(^[\w.%+-]+@[\w.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, padraoEmail);
}

int main() {
    std::unordered_map<std::string, Jogador> jogadores;
    std::string entrada;

    while (true) {
        std::cout << "\nBem-vindo ao Jogo! Escolha uma opção:\n";
        std::cout << "  0 - Entrar.\n";
        std::cout << "  1 - Cadastrar um novo jogador.\n";
        std::cout << "  2 - Remover um jogador.\n";
        std::cout << "  3 - Sair do sistema.\n";

        std::cout << "Digite a opção desejada: ";
        std::getline(std::cin, entrada);

        if (entrada == "3") {
            std::cout << "Jogo encerrado.\n";
            break;
        }

        if (entrada == "1") { // Cadastrar Jogador
            std::cout << "Digite o apelido do jogador: ";
            std::string apelido;
            std::getline(std::cin, apelido);

            if (apelido.empty()) {
                std::cout << "ERRO: O apelido não pode estar vazio.\n";
                continue;
            }

            std::cout << "Digite o nome do jogador: ";
            std::string nome;
            std::getline(std::cin, nome);

            if (nome.empty()) {
                std::cout << "ERRO: O nome não pode estar vazio.\n";
                continue;
            }

            std::cout << "Digite o email do jogador: ";
            std::string email;
            std::getline(std::cin, email);

            if (!validarEmail(email)) {
                std::cout << "ERRO: Email inválido.\n";
                continue;
            }

            std::cout << "Digite a senha do jogador: ";
            std::string senha;
            std::getline(std::cin, senha);

            if (senha.empty()) {
                std::cout << "ERRO: A senha não pode estar vazia.\n";
                continue;
            }

            if (jogadores.find(apelido) != jogadores.end()) {
                std::cout << "ERRO: jogador já existente\n";
            } else {
                jogadores[apelido] = {apelido, nome, email, senha};
                std::cout << "Jogador " << apelido << " cadastrado com sucesso\n";
            }
        } else if (entrada == "2") { // Remover Jogador
            std::cout << "Digite o apelido do jogador a ser removido: ";
            std::string apelido;
            std::getline(std::cin, apelido);

            if (apelido.empty()) {
                std::cout << "ERRO: O apelido não pode estar vazio.\n";
                continue;
            }

            if (jogadores.find(apelido) == jogadores.end()) {
                std::cout << "ERRO: jogador inexistente\n";
            } else {
                jogadores.erase(apelido);
                std::cout << "Jogador " << apelido << " removido com sucesso\n";
            }
        } else if (entrada == "0") { // Entrar no sistema
            std::cout << "Digite o apelido: ";
            std::string apelido;
            std::getline(std::cin, apelido);

            if (apelido.empty()) {
                std::cout << "ERRO: O apelido não pode estar vazio.\n";
                continue;
            }

            std::cout << "Digite a senha: ";
            std::string senha;
            std::getline(std::cin, senha);

            if (senha.empty()) {
                std::cout << "ERRO: A senha não pode estar vazia.\n";
                continue;
            }

            if (jogadores.find(apelido) != jogadores.end() && jogadores[apelido].getSenha() == senha) {
                std::cout << "Bem-vindo, " << jogadores[apelido].getNome() << "!\n";
                std::cout << "Seja bem vindo! \n";
            } else {
                std::cout << "ERRO: apelido ou senha incorretos\n";
            }
        } else {
            std::cout << "ERRO: opção desconhecida\n";
        }
    }

    return 0;
}