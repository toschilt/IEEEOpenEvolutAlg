#ifndef CONSTANTES_H
#define CONSTANTES_H

using namespace std;

#define ARMAZENAMENTO_ROBO                          3

#define QUANTIDADE_PACOTES                          10 //TODO atualizar para que seja automático
#define QUANTIDADE_ACOES                            10

#define TAMANHO_VETOR_SEQUENCIAPACOTES              10
#define TAMANHO_VETOR_SEQUENCIAACAO                 10

#define GERACOES                                    50
#define GERACOES_EVOLUTIVO_INTERNO                  10

#define TAXA_MUTACAO_SEQUENCIACAO                   5
#define TAXA_MUTACAO_ADICIONAL                      0.1
#define TAXA_CROSSOVER_SEQUENCIAPACOTES             80
#define TAXA_MUTACAO_SEQUENCIAPACOTES               15
#define QUANTIDADE_CONDICAO_GENOCIDIO               7

#define PENALIDADE_QUADRANTE_DESLOCADO              100
#define GANHO_COLETA_PACOTE_COLORIDO                20
#define GANHO_COLETA_PACOTE_PRETO                   100
#define GANHO_COLETA_PACOTE_BRANCO                  200
#define GANHO_ENTREGA_PACOTE_COLORIDO               100
#define GANHO_ENTREGA_PACOTE_PRETO                  500
#define GANHO_ENTREGA_PACOTE_BRANCO                 1000

#define SEMENTE                                     1298279

enum kcores_pacotes 
{
    COR_INDEF = -1,
    COR_VERDE,
    COR_AZUL,
    COR_AMARELO,
    COR_VERMELHO,
    COR_PRETO,
    COR_BRANCO
};

/* 
 * Definição das constantes que definem a orientação do robô.
 * ORIENTACAO_PRATILEIRA - garra voltada para as pratileiras
 * ORIENTACAO_ENTREGA_COLORIDOS - garra voltada para as regiões coloridas
 * ORIENTACAO_DIREITA - garra voltada para a direita, olhando para as pratileiras
 * ORIENTACAO_ESQUERDA - garra voltada para a esquerda, olhando para as pratileiras
*/
enum korientacaoRobo {
    ORIENTACAO_PRATILEIRA,
    ORIENTACAO_ENTREGA_COLORIDOS,
    ORIENTACAO_DIREITA,
    ORIENTACAO_ESQUERDA
};

#endif