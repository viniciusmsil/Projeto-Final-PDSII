#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "tabuleiro.hpp"
#include "jogador.hpp"
#include <vector>
#include <utility>

class Othello {
private:
    Tabuleiro tabuleiro;
    Jogador* jogadorPreto;
    Jogador* jogadorBranco;
    char jogadorAtual;
    const std::vector<std::pair<int, int>> direcoes = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
public:
    // Construtor
    Othello(Jogador* preto, Jogador* branco);
    bool jogadaValida(int linha, int coluna) const;
    void capturarPecas(int linha, int coluna);
    std::pair<int, int> calcularPontuacao() const;
    bool verificarFimDeJogo() const;
    bool verificarDisponibilidade(int linha, int coluna) const;
    char getJogadorAtual() const;
    void exibirJogadorAtual() const;
    void verificarVencedor() const;
};

#endif
