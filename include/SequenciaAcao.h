#ifndef SEQUENCIAACAO_H
#define SEQUENCIAACAO_H

using namespace std;

#include "SequenciaPacotes.h"
#include "StatusRobo.h"
#include "Pacote.h"
#include "Constantes.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <array>
#include <random>


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


class SequenciaAcao {
    private:

    bool coinflip(float probabilidadeSucesso);


    public:
    
    /*
     * Variável que armazena o índice da melhor sequencia de pacotes
    */
    int indiceMelhorFitness;
    
    /*
     * Melhor fitness
    */
    retornoCalcFitness melhorFitness;

    /*
     * Vetor com sequências de pacotes para evoluir
    */
    array<SequenciaPacotes, TAMANHO_VETOR_SEQUENCIAPACOTES> sequenciaPacotes;


    /*
     * Vetor com os fitness individuais para cada sequência
     * utilizado para definição de pesos no crossover
    */
    retornoCalcFitness fitness[TAMANHO_VETOR_SEQUENCIAPACOTES];

    /*
     * Vetor que armazena a sequência de ações específica
    */
    int *sequenciaAcoes;
    
    /*
     * Construtor da classe
    */
    SequenciaAcao(StatusRobo *robo);

    /*
     * Inicializa sequências aleatóirias de pacotes
    */
    void inicializaPacotes(array<Pacote*, QUANTIDADE_PACOTES> pacotesDisponiveis);
    void calculaFitness();
    void atualizaPopulacao();
    void crossover();
    void mutacao();

    void normalizaFitness(); //Necessária caso o fit do seq pacotes não retorne algo entre 0 e 1

};

#endif