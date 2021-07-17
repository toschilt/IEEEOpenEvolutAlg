#ifndef PLANEJAMENTOROBO_H
#define PLANEJAMENTOROBO_H

#include "SequenciaAcao.h"
#include "StatusRobo.h"
#include <vector>

class PlanejamentoRobo {
    private:
        
        /*
         * 
        */
        int* geraSequenciaAleatoria();

    public:

        /*
        * ============
        * ATRIBUTOS
        * ============
        */

        /*
         * Indice do vetor que contém a sequência de ação 
         * com melhor fitness.
        */
        int indiceMelhorCombinacao;
        
        /*
         * O melhor fitness em relação a todas as sequências
         * de ações.
        */
        float melhorFitness;

        /*
         * Vetor com falores de fitness.
        */
        float fitness[TAMANHO_VETOR_SEQUENCIAACAO];
        
        /*
         * Vetor de SequenciaAcao.
        */
        vector<SequenciaAcao> sequenciasPacotes;


        /*
        * ==============
        * CONSTRUTORES
        * ==============
        */

        /*
         * Construtor padrão.
         * Recebe o StatusRobo para inicialização.
        */
        PlanejamentoRobo(StatusRobo *robo);

        /*
         * Inicia a inicialização das sequências de ação.
        */
        void inicializaPlanejamento(StatusRobo *robo);


        /*
        * ======================
        * ALGORITMO GENÉTICO
        * ======================
        */

        /*
         * Calcula o fitness de todas as sequências de ação,
         * bem como de todas as sequências de pacotes.
        */
        retornoCalcFitness calculaFitness();

        /*
         * Realiza a evolução do sistema por n gerações.
        */
        void evoluiNGeracoes(int n);
        
        /*
         * Atualiza todas as sequências de ação.
        */
        void atualizaPopulacao();

        /*
         * Realiza o crossover de todas as sequências de pacote
         * encapsuladas nas sequências de ações.
        */
        void crossover();

        /*
         * Realiza a mutação de todas as sequências de pacote
         * encapsuladas nas sequências de ações.
        */
        void mutacao();

        /*
         * Realiza o genocídio nas sequências de pacote
         * encapsuladas nas sequências de ações.
        */
        void genocidio();

};

#endif