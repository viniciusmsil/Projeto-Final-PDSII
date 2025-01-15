#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <utility>

class Jogador {
public:
    virtual std::string getApelido() const = 0;
    virtual ~Jogador() = default;
};

class Tabuleiro {
protected:
    int tamanho;
    std::vector<std::vector<char>> tabuleiro;

public:
    Tabuleiro(int tamanho);
    virtual void exibirTabuleiro() const = 0;
};

class Othello : public Tabuleiro {
private:
    static const std::vector<std::pair<int, int>> direcoes;  // Direções para captura
    char jogadorAtual; // 'B' para preto e 'P' para branco
    std::shared_ptr<Jogador> jogadorPreto;
    std::shared_ptr<Jogador> jogadorBranco;

    void alternarJogador();
    bool jogadaValida(int linha, int coluna) const;
    void capturarPecas(int linha, int coluna);
    std::pair<int, int> calcularPontuacao() const;
    bool verificarDisponibilidade(int linha, int coluna) const;
    void verificarVencedor() const;

public:
    Othello(std::shared_ptr<Jogador> jogador1, std::shared_ptr<Jogador> jogador2);
    void exibirTabuleiro() const override;
    bool fazerJogada(int linha, int coluna);
    bool verificarFimDeJogo() const;
    char getJogadorAtual() const;
    void exibirJogadorAtual() const;
};

#endif // OTHELLO_HPP