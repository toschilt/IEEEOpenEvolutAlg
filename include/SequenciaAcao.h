#ifndef SEQUENCIAACAO_H
#define SEQUENCIAACAO_H

#include "SequenciaPacotes.h"
#include "StatusRobo.h"
#include "Pacote.h"

#define TAMANHOSEQUENCIAACAO 10
#define QUANTIDADESEQUENCIAPACOTES 10

/*
SequenciaAcao.h                                                         (populacão de SequenciaPacotes e indivíduo do PlanejamentoRobo)
    - int indiceMelhorSequenciaPacotes                                  (índice com o melhor conjunto de pacotes)
    - char[]                                                            (ações)
    - SequenciaPacotes[]
    - CoordR2 posicaoAtual
    
    - SequenciaAcao(StatusRobo)                                         (chama inicializaPacotes e atualiza posicaoAtual)
    - inicializaPacotes(Pacote[] pacotesDisponiveis)                    (inicializa sequências randômicas de pacotes)
    - calculaFitness()                                                  (já atualiza indiceMelhorSequenciaPacotes)
    - criaNovaPopulacao()                                               (chama crossover() e mutacao() e atualiza SequenciaPacotes)
    - crossover()                                                       (age sobre o SequenciaPacotes[])
    - mutacao()                                                         (age sobre o SequenciaPacotes[])
*/


class SequenciaAcao 
{
    private:

    public:
    
    int melhorSequenciaPacotes;
    int sequencia[TAMANHOSEQUENCIAACAO];
    CoordR2 posicaoAtual;

    SequenciaPacotes sequenciaPacotes[QUANTIDADESEQUENCIAPACOTES];

    SequenciaAcao(StatusRobo *robo);
    void inicializaPacotes(Pacote* pacotesDisponiveis);
    void calculaFitness();
    void crossover();
    void mutacao();

};

#endif