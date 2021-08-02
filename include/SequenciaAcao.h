#ifndef SEQUENCIAACAO_H
#define SEQUENCIAACAO_H

using namespace std;

#include "SequenciaPacotes.h"
#include "StatusRobo.h"
#include "Pacote.h"
#include "Constantes.h"
#include "CoordR2.h"
#include "Grafo.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <vector>
#include <chrono>
#include <set>

class SequenciaAcao {
    private:

    /*
     * Função responsável por retornar um booleano de acordo
     * com uma certa probabilidade de sucesso.
    */
    bool coinflip(float probabilidadeSucesso);

    /*
     * Função responsável por verificar se uma sequencia de pacotes
     * deve sofrer genocídio
    */
    bool calculoCondicaoGenocidio();

    public:

    /*
    * ============
    * ATRIBUTOS
    * ============
    */

    /*
     * Variável que armazena o índice da melhor sequencia de pacotes
     * para a sequência de ações em específico.
    */
    int indiceMelhorFitness;

    /*
     * Vetor que armazena a sequência de ações específica.
    */
    vector<int> *sequenciaAcoes;
    
    /*
     * Vetor que armazena as sequências de pacotes para evoluir.
    */
    vector<SequenciaPacotes*> *sequenciasPacotes;

    /*
     * Função responsável por retornar o melhor valor de fitness de
     * cada sequência de ações.
    */
    float melhorFitness;

    /*
     * Vetor com os valores de fitness individuais para cada sequência.
     * É utilizado para definição de pesos no crossover.
    */
    float fitness[TAMANHO_VETOR_SEQUENCIAPACOTES];

    /*
     * Posição inicial do robô no cenário
    */
    CoordR2 *posInicial;

    /*
     * Grafo do cenário.
    */
    Grafo *grafoCenario;


    /*
     * ==============
     * CONSTRUTORES
     * ==============
    */

    /*
     * Construtor padrão.
     * O StatusRobo é passado como parâmetro.
    */
    SequenciaAcao(StatusRobo* robo);

    /*
     * ======================
     * ALGORITMO EVOLUTIVO
     * ======================
    */

    /*
     * Inicializa sequências aleatórias de pacotes a partir
     * dos pacotes disponíveis no cenário.
    */
    void inicializaPacotes(vector<Pacote*> *pacotesDisponiveis);

    /*
     * Calcula o fitness da sequência de ações. Calcula o fitness
     * de cada uma da sequência de pacotes para cada sequência de 
     * ações.
    */
    float calculaFitness();
    
    /*
     * Atualiza os indivíduos das sequências de pacotes para cada
     * sequência de ações.
     * Executa as funções crossover() e mutacao().
    */
    void atualizaPopulacao(int indiceDestravamentoMutacao);

    /*
     * Realiza o crossover entre as sequências de pacotes, cruzando
     * informações.
    */
    void crossover();

    /*
     * Realiza o genocídio da população, caso esta tenha convergido
    */
    bool genocidio();

    /*
     * Realiza a mutação nas sequências de pacotes, aumentando a
     * diversidade do sistema.
    */
    void mutacao(int indiceDestravamentoMutacao);

    /*
     * Sobrecarga do operador <<.
    */
    friend ostream& operator<<(ostream& os, const SequenciaAcao& acoes);

};

#endif