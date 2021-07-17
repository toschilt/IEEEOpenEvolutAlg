#ifndef SEQUENCIAPACOTES_H
#define SEQUENCIAPACOTES_H

#include "Pacote.h"
<<<<<<< Updated upstream
#include "Constantes.h"
=======
#include "SequenciaAcao.h"
#include <list>

/*
SequenciaPacotes.h                                                      (indivíduo)
    - int fitness
    - Pacote[]

    - SequenciaPacotes(Pacote[] pacotesDisponiveis)
    - calculaCustoDeslocamento(CoordR2)                                 (calcula o custo para realizar o deslocamento para uma determinada acao)
    - calculaCustoColeta()                                              (calula o custo para realizar a coleta de um pacote)
    - calculaCustoEntrega()                                             (calcula o custo para realizar a entrega de um pacote)
    - calculaFitness(char[])                                            (recebe as ações como argumento)
*/

enum{
    coleta,
    entrega
};
>>>>>>> Stashed changes

typedef float retornoCalcFitness;

class SequenciaPacotes {
    private:

    float fitness;
    Grafo grafoCenario; 

    public:

<<<<<<< Updated upstream
    vector<Pacote*> *sequenciaPacotes;

    retornoCalcFitness calculaFitness(int *sequenciaAcoes);

    SequenciaPacotes(vector<Pacote*> *sequencia);
    
=======
    array<Pacote*, QUANTIDADE_PACOTES> sequenciaPacotes;
    int pacoteAtual;

    CoordR2 posAtualRobo;

    // Construtor da classe
    SequenciaPacotes::SequenciaPacotes(vector<Pacote*> pacotes, Grafo grafoCenario);

    // Calcula pontuacao referente ao deslocamento do robo até a posicao alvo
    int SequenciaPacotes::calculaCustoDeslocamento(CoordR2 coordenadaAtual, CoordR2 coordenadaAlvo);

    // Calcula pontuacao referente a uma coleta dde um pacote
    float SequenciaPacotes::calculaPontosColeta(Pacote* pacote, int distancia);

    // Escolhe a melhor posicao disponivele coleta o pacote, retornando a pontuacao referente a coleta
    CoordR2 SequenciaPacotes::coletaPacote(CoordR2 coordenadaAtual, Pacote* pacote);

    // Calcula pontuacao referente a uma entrega de pacote
    float SequenciaPacotes::calculaPontosEntrega(Pacote* pacote, int distancia);

    // Escolhe dentre as posições de entrega possíveis a mais vantajosa
    CoordR2 SequenciaPacotes::encontraMelhorPosicaoEntrega(CoordR2 coordenadaAtual, Pacote* pacote, int* menorDistancia);

    // Escolhe o pacote mais vantajoso a ser entregue na posicao mais vantajosa e retorna a pontuacao da entrega
    float SequenciaPacotes::entregaPacote(CoordR2 *posicaoAtualRobo, set<Pacote*> pacotesColetados);

    // Calcula fitness total iterando por todas as acoes do robô e pelos pacotes a serem coletados e entregues
    float SequenciaPacotes::calculaFitness(int *sequenciaAcoes, CoordR2 posicaoInicialRobo);
>>>>>>> Stashed changes
};


#endif