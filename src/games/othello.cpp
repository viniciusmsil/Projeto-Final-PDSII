#include "othello.hpp"

// Direções possíveis para capturar peças (8 direções ao redor da célula).
const std::vector<std::pair<int, int>> Othello::direcoes = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

// Construtor que inicializa o tabuleiro e os jogadores.
Othello::Othello(std::shared_ptr<Jogador> jogador1, std::shared_ptr<Jogador> jogador2)
    : Tabuleiro(8), jogadorAtual('B'), jogadorPreto(jogador1), jogadorBranco(jogador2) {
    // Configura as peças iniciais no centro do tabuleiro.
    tabuleiro[3][3] = 'P'; // Branco
    tabuleiro[3][4] = 'B'; // Preto
    tabuleiro[4][3] = 'B'; // Preto
    tabuleiro[4][4] = 'P'; // Branco
}

// Alterna o jogador atual.
void Othello::alternarJogador() {
    jogadorAtual = (jogadorAtual == 'B') ? 'P' : 'B';
}

// Exibe o tabuleiro atual.
void Othello::exibirTabuleiro() const {
    std::cout << "\nTabuleiro Atual:\n";
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            std::cout << tabuleiro[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Exibe pontuação.
    auto [pontuacaoPreto, pontuacaoBranco] = calcularPontuacao();
    std::cout << "Pontuação:\n";
    std::cout << jogadorPreto->getApelido() << " (Preto): " << pontuacaoPreto << "\n";
    std::cout << jogadorBranco->getApelido() << " (Branco): " << pontuacaoBranco << "\n";
}

// Realiza uma jogada no tabuleiro.
bool Othello::fazerJogada(int linha, int coluna) {
    if (!jogadaValida(linha, coluna)) {
        std::cout << "Jogada inválida! Tente novamente.\n";
        return false;
    }

    // Realiza a jogada.
    tabuleiro[linha][coluna] = jogadorAtual;

    // Captura peças do oponente.
    capturarPecas(linha, coluna);

    // Alterna para o próximo jogador.
    alternarJogador();
    return true;
}

// Verifica se uma jogada é válida.
bool Othello::jogadaValida(int linha, int coluna) const {
    if (linha < 0 || linha >= tamanho || coluna < 0 || coluna >= tamanho || tabuleiro[linha][coluna] != ' ') {
        return false;
    }

    for (const auto& [dx, dy] : direcoes) {
        int x = linha + dx, y = coluna + dy;
        bool encontrouOponente = false;

        while (x >= 0 && x < tamanho && y >= 0 && y < tamanho) {
            if (tabuleiro[x][y] == ' ') break;
            if (tabuleiro[x][y] == jogadorAtual) {
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

// Captura peças do oponente.
void Othello::capturarPecas(int linha, int coluna) {
    for (const auto& [dx, dy] : direcoes) {
        std::vector<std::pair<int, int>> capturar;
        int x = linha + dx, y = coluna + dy;

        while (x >= 0 && x < tamanho && y >= 0 && y < tamanho) {
            if (tabuleiro[x][y] == ' ') break;
            if (tabuleiro[x][y] == jogadorAtual) {
                for (const auto& pos : capturar) {
                    tabuleiro[pos.first][pos.second] = jogadorAtual;
                }
                break;
            }
            capturar.push_back({x, y});
            x += dx;
            y += dy;
        }
    }
}

// Calcula a pontuação dos jogadores.
std::pair<int, int> Othello::calcularPontuacao() const {
    int pontuacaoPreto = 0, pontuacaoBranco = 0;
    for (const auto& linha : tabuleiro) {
        for (char celula : linha) {
            if (celula == 'B') ++pontuacaoPreto;
            else if (celula == 'P') ++pontuacaoBranco;
        }
    }
    return {pontuacaoPreto, pontuacaoBranco};
}

// Verifica se o jogo terminou.
bool Othello::verificarFimDeJogo() const {
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            if (verificarDisponibilidade(i, j)) return false;
        }
    }

    // Verifica o vencedor ao fim do jogo.
    verificarVencedor();
    return true;
}

// Verifica se há jogada disponível para o jogador atual.
bool Othello::verificarDisponibilidade(int linha, int coluna) const {
    return jogadaValida(linha, coluna);
}

// Retorna o jogador atual.
char Othello::getJogadorAtual() const {
    return jogadorAtual;
}

// Exibe o jogador atual.
void Othello::exibirJogadorAtual() const {
    std::cout << "Jogador atual: " 
              << (jogadorAtual == 'B' ? jogadorPreto->getApelido() : jogadorBranco->getApelido())
              << " (" << jogadorAtual << ")\n";
}

// Verifica e exibe o vencedor.
void Othello::verificarVencedor() const {
    auto [pontuacaoPreto, pontuacaoBranco] = calcularPontuacao();
    if (pontuacaoPreto > pontuacaoBranco) {
        std::cout << jogadorPreto->getApelido() << " (Preto) é o vencedor!\n";
    } else if (pontuacaoBranco > pontuacaoPreto) {
        std::cout << jogadorBranco->getApelido() << " (Branco) é o vencedor!\n";
    } else {
        std::cout << "O jogo terminou empatado!\n";
    }
}