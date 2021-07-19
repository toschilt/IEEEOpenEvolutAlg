#ifndef PLANEJAMENTOROBO_H
#define PLANEJAMENTOROBO_H

#include "SequenciaAcao.h"
#include "StatusRobo.h"
#include "SequenciaPacotes.h"
#include <vector>

class PlanejamentoRobo {
    private:
        
        /*
         * Gera sequência aleatória de ações para inicializar a sequenciaAcoes
        */
        void geraSequenciaAleatoria(vector<int> *sequenciaAcoes);

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
         * Vetor com falores de fitness das sequências de ações.
        */
        float fitness[TAMANHO_VETOR_SEQUENCIAACAO];
        
        /*
         * Vetor de SequenciaAcao.
        */
        vector<SequenciaAcao*> *sequenciasAcao;


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
        float calculaFitness();

        /*
         * Atualiza todas as sequências de pacotes para
         * cada sequência de ação.
        */
        void atualizaPopulacaoPacotes();

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

        /*
         * Atualiza todas as sequências de ações.
        */
        void atualizaPopulacaoAcoes();
        
        /*
         * Realiza a evolução do sistema por n gerações.
        */
        void evoluiNGeracoes(int n);
};

#endif