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
#include <vector>


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
    vector<SequenciaPacotes*> *sequenciasPacotes;


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
     * Inicializa sequências aleatórias de pacotes
    */
    void inicializaPacotes(vector<Pacote*> *pacotesDisponiveis);
    void calculaFitness();
    void atualizaPopulacao();
    void crossover();
    void mutacao();

    void normalizaFitness(); //Necessária caso o fit do seq pacotes não retorne algo entre 0 e 1

};

#endif