#include "JogoDaVelha.hpp"
#include <iostream>

JogoDaVelha::JogoDaVelha() : Tabuleiro(3, 3) {}

bool JogoDaVelha::fazerJogada(int linha, int coluna, char jogador) {
    if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && tabuleiro[linha][coluna] == ' ') {
        tabuleiro[linha][coluna] = jogador;
        return true;
    }
    return false;
}

bool JodoDaVelha::verificarVitoria(string jogador) const {
    for (int i = 0; i < 3; ++i) {
        //linhas
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador)
            return true;
        //Colunas
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)
            return true;
    }
        //Diagonais
        if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) ||
           (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador); {
            return true;
}  
return false;
}  

bool JogoDaVelha::verificarEmpate() const {
    // Verifica se todas as células estão preenchidas
    for (const auto& linha : tabuleiro) {
        for (char celula : linha) {
            if (celula == ' ') {
                return false; 
            }
        }
    }
    if (verificarVitoria('X') || verificarVitoria('O')) {
        return false; 
    }
    return true; 
}

void JogoDaVelha::verificarVencedor() const {
    if (verificarVitoria('X')) {
    std::cout << "O jogador X venceu!\n";
  } else if (verificarVitoria('O')) {
    std::cout << "O jogador O venceu!\n";
  } else if (verificarEmpate()) {
    std::cout << "O jogo terminou empatado!\n";
  } else {
    std::cout << "O jogo ainda não acabou.\n";
  }
}

void JogoDaVelha::exibirTabuleiro() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
            std::cout << tabuleiro[i][j];
                if (j < 2) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "---------\n";
    }
}
