#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

#include <vector>
#include <iostream>
#include <string>

class Tabuleiro {
protected:
    std::vector<std::vector<char>> tabuleiro; 
    int tamanho; 

public:
    
    Tabuleiro();

    Tabuleiro(int tamanho);

    void exibirTabuleiro() const;

    void limparTabuleiro();

    int getTamanho() const;
};

#endif