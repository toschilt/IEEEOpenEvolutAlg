#ifndef SEQUENCIAPACOTES_H
#define SEQUENCIAPACOTES_H

#include "Pacote.h"
#include "Constantes.h"
#include "CoordR2.h"
#include "Grafo.h"
#include <list>
#include <set>

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

class SequenciaPacotes {
    private:

    float fitness;
    Grafo *grafoCenario; 

    public:

    vector<Pacote*> *sequenciaPacotes;
    int pacoteAtual;

    CoordR2 posAtualRobo;

    // Construtor da classe
    SequenciaPacotes(vector<Pacote*> *pacotes, Grafo *grafoCenario);

    // Calcula pontuacao referente ao deslocamento do robo até a posicao alvo
    int calculaCustoDeslocamento(CoordR2 coordenadaAtual, CoordR2 coordenadaAlvo);

    // Calcula pontuacao referente a uma coleta dde um pacote
    float calculaPontosColeta(Pacote* pacote, int distancia);

    // Escolhe a melhor posicao disponivele coleta o pacote, retornando a pontuacao referente a coleta
    float coletaPacote(CoordR2 *coordenadaAtual, Pacote* pacote);

    // Calcula pontuacao referente a uma entrega de pacote
    float calculaPontosEntrega(Pacote* pacote, int distancia);

    // Escolhe dentre as posições de entrega possíveis a mais vantajosa
    CoordR2 encontraMelhorPosicaoEntrega(CoordR2 coordenadaAtual, Pacote* pacote, int* menorDistancia);

    // Escolhe o pacote mais vantajoso a ser entregue na posicao mais vantajosa e retorna a pontuacao da entrega
    float entregaPacote(CoordR2 *posicaoAtualRobo, set<Pacote*> pacotesColetados);

    // Calcula fitness total iterando por todas as acoes do robô e pelos pacotes a serem coletados e entregues
    float calculaFitness(vector <int> *sequenciaAcoes, CoordR2 *posicaoInicialRobo);
};

#endif