#ifndef JOGO_DA_VELHA_HPP
#define JOGO_DA_VELHA_HPP

#include "tabuleiro.hpp"
#include "jogador.hpp"
#include <iostream>
#include <vector>

class JogoDaVelha : public Tabuleiro {
public:
    JogoDaVelha();

    bool fazerJogada (int linha, int coluna, char jogador);

    void exibirTabuleiro() const override; 

    bool verificarVitoria(char jogador) const;

    bool verificarEmpate() const;
};

#endif 

