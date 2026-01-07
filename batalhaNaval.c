#include <stdio.h>

#define TAM 10    // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3  // Todos os navios têm tamanho 3

// Tabuleiro do jogador (0 = água, 3 = parte do navio)
int tabuleiro[TAM][TAM];

// Protótipos de funções
void inicializarTabuleiro();
int posicionarNavio(int linha_inicio, int coluna_inicio, char orientacao);
void exibirTabuleiro();

int main() {
    // Inicializa o tabuleiro com água (0)
    inicializarTabuleiro();

    printf("=== BATALHA NAVAL - Posicionamento dos Navios ===\n\n");

    // === Posicionamento do Navio 1: Horizontal ===
    // Exemplo: linha 2, coluna 3 → ocupa posições (2,3), (2,4), (2,5)
    int sucesso1 = posicionarNavio(2, 3, 'H');  // 'H' = horizontal

    if (sucesso1) {
        printf("Navio 1 (horizontal) posicionado com sucesso na linha 2, coluna 3.\n");
    } else {
        printf("ERRO: Não foi possível posicionar o Navio 1 (posição inválida ou sobreposição).\n");
        return 1; // Encerra se houver erro grave
    }

    // === Posicionamento do Navio 2: Vertical ===
    // Exemplo: linha 5, coluna 7 → ocupa posições (5,7), (6,7), (7,7)
    int sucesso2 = posicionarNavio(5, 7, 'V');  // 'V' = vertical

    if (sucesso2) {
        printf("Navio 2 (vertical) posicionado com sucesso na linha 5, coluna 7.\n\n");
    } else {
        printf("ERRO: Não foi possível posicionar o Navio 2 (posição inválida ou sobreposição).\n");
        return 1;
    }

    // Exibe o tabuleiro final com os navios posicionados
    printf("Tabuleiro final:\n");
    exibirTabuleiro();

    return 0;
}

// Função: Preenche todo o tabuleiro com 0 (água)
void inicializarTabuleiro() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função: Posiciona um navio de tamanho 3 no tabuleiro
// Retorna 1 se sucesso, 0 se falhou (fora dos limites ou sobreposição)
int posicionarNavio(int linha_inicio, int coluna_inicio, char orientacao) {
    // Validação inicial: coordenadas de início devem estar dentro do tabuleiro
    if (linha_inicio < 0 || linha_inicio >= TAM || coluna_inicio < 0 || coluna_inicio >= TAM) {
        return 0;
    }

    // Verifica se o navio cabe no tabuleiro de acordo com a orientação
    if (orientacao == 'H') { // Horizontal
        if (coluna_inicio + TAM_NAVIO > TAM) { // Não cabe à direita
            return 0;
        }
        // Verifica sobreposição: nenhuma posição já deve ter navio (3)
        for (int j = 0; j < TAM_NAVIO; j++) {
            if (tabuleiro[linha_inicio][coluna_inicio + j] == 3) {
                return 0; // Já tem navio nessa posição
            }
        }
        // Posiciona o navio
        for (int j = 0; j < TAM_NAVIO; j++) {
            tabuleiro[linha_inicio][coluna_inicio + j] = 3;
        }
    }
    else if (orientacao == 'V') { // Vertical
        if (linha_inicio + TAM_NAVIO > TAM) { // Não cabe para baixo
            return 0;
        }
        // Verifica sobreposição
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha_inicio + i][coluna_inicio] == 3) {
                return 0;
            }
        }
        // Posiciona o navio
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha_inicio + i][coluna_inicio] = 3;
        }
    }
    else {
        return 0; // Orientação inválida
    }

    return 1; // Sucesso
}

// Função: Exibe o tabuleiro de forma organizada
void exibirTabuleiro() {
    // Cabeçalho com letras das colunas
    printf("   ");
    for (int j = 0; j < TAM; j++) {
        printf(" %c ", 'A' + j);
    }
    printf("\n");

    // Linhas do tabuleiro
    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i); // Número da linha alinhado
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" ~ "); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf(" N "); // Navio
            }
        }
        printf(" %d\n", i); // Repete o número da linha no final (opcional, para clareza)
    }

    printf("   ");
    for (int j = 0; j < TAM; j++) {
        printf(" %c ", 'A' + j);
    }
    printf("\n");

    printf("\nLegenda: ~ = água, N = parte do navio\n");
}
