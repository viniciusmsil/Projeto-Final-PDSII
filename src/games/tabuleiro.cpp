#include "tabuleiro.hpp"


Tabuleiro::Tabuleiro() : tamanho(3) {
    tabuleiro = std::vector<std::vector<char>>(tamanho, std::vector<char>(tamanho, ' '));
}

Tabuleiro::Tabuleiro(int tamanho) : tamanho(tamanho) {
    tabuleiro = std::vector<std::vector<char>>(tamanho, std::vector<char>(tamanho, ' '));
}

void Tabuleiro::exibirTabuleiro() const {
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            std::cout << tabuleiro[i][j];
            if (j < tamanho - 1) std::cout << " | ";
        }
        std::cout << std::endl;
        if (i < tamanho - 1) {
            for (int k = 0; k < tamanho; ++k) {
                std::cout << "---";
                if (k < tamanho - 1) std::cout << "+";
            }
            std::cout << std::endl;
        }
    }
}

void Tabuleiro::limparTabuleiro() {
    for (auto& linha : tabuleiro) {
        for (char& celula : linha) {
            celula = ' ';
        }
    }
}

int Tabuleiro::getTamanho() const {
    return tamanho;
}