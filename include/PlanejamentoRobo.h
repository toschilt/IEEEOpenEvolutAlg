#ifndef PLANEJAMENTOROBO_H
#define PLANEJAMENTOROBO_H

#include "SequenciaAcao.h"
#include "StatusRobo.h"
#include "SequenciaPacotes.h"
#include "ProduzGrafico.h"
#include <vector>
#include <string>

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
         * O melhor fitness do AG externo anterior.
        */
        float melhorFitnessAnterior;

        /*
         * Índice que aumenta a mutação conforme o fitness
         * fica preso em determinado valor.
        */
        float indiceDestravamentoMutacao;

        /*
         * Vetor com valores de fitness das sequências de ações.
        */
        float fitness[TAMANHO_VETOR_SEQUENCIAACAO];

        /*
         * Vetor com valores dos fitness antigos.
        */
        vector<double> pastFitness;

        /*
         * Vetor com valores para o eixo X.
        */
        vector<double> xAxis;

        /*
         * Variável para inserir no vetor de valores para o eixo X.
        */
        int indexForXAxis = 0;
        
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

        /*
         * Imprime os resultados finais da evolução.
        */
        void printResults();
};

#endif