#include "tabuleiro.hpp"
#include "jogador.hpp"
#include <vector>
#include <iostream>

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
    Othello(Jogador* preto, Jogador* branco) 
        : jogadorPreto(preto), jogadorBranco(branco), jogadorAtual('B') {}

    bool jogadaValida(int linha, int coluna) const {
        if (!tabuleiro.posicaoValida(linha, coluna) || tabuleiro.getCelula(linha, coluna) != ' ')
            return false;

        for (const auto& [dx, dy] : direcoes) {
            int x = linha + dx, y = coluna + dy;
            bool encontrouOponente = false;

            while (tabuleiro.posicaoValida(x, y)) {
                char celula = tabuleiro.getCelula(x, y);
                if (celula == ' ') break;
                if (celula == jogadorAtual) {
                    if (encontrouOponente) return true;
                    break;
                }
                encontrouOponente = true;
                x += dx;
                y += dy;
            }
        }
        return false;
    }

    void capturarPecas(int linha, int coluna) {
        for (const auto& [dx, dy] : direcoes) {
            std::vector<std::pair<int, int>> capturar;
            int x = linha + dx, y = coluna + dy;

            while (tabuleiro.posicaoValida(x, y)) {
                char celula = tabuleiro.getCelula(x, y);
                if (celula == ' ') break;
                if (celula == jogadorAtual) {
                    for (const auto& pos : capturar) {
                        tabuleiro.setCelula(pos.first, pos.second, jogadorAtual);
                    }
                    break;
                }
                capturar.emplace_back(x, y);
                x += dx;
                y += dy;
            }
        }
    }

    std::pair<int, int> calcularPontuacao() const {
        return tabuleiro.calcularPontuacao();
    }

    bool verificarFimDeJogo() const {
        for (int i = 0; i < tabuleiro.getTamanho(); ++i) {
            for (int j = 0; j < tabuleiro.getTamanho(); ++j) {
                if (verificarDisponibilidade(i, j)) return false;
            }
        }

        verificarVencedor();
        return true;
    }

    bool verificarDisponibilidade(int linha, int coluna) const {
        return jogadaValida(linha, coluna);
    }

    char getJogadorAtual() const {
        return jogadorAtual;
    }

    void exibirJogadorAtual() const {
        std::cout << "Jogador atual: " 
                  << (jogadorAtual == 'B' ? jogadorPreto->getApelido() : jogadorBranco->getApelido())
                  << " (" << jogadorAtual << ")\n";
    }

    void verificarVencedor() const {
        auto [pontuacaoPreto, pontuacaoBranco] = calcularPontuacao();
        if (pontuacaoPreto > pontuacaoBranco) {
            std::cout << jogadorPreto->getApelido() << " (Preto) é o vencedor!\n";
        } else if (pontuacaoBranco > pontuacaoPreto) {
            std::cout << jogadorBranco->getApelido() << " (Branco) é o vencedor!\n";
        } else {
            std::cout << "O jogo terminou empatado!\n";
        }
    }
};
