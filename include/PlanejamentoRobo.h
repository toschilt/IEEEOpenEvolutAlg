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
        
        int indiceMelhorCombinacao;
        
        float melhorFitness;

        float fitness[TAMANHO_VETOR_SEQUENCIAACAO];
        
        vector<SequenciaAcao> sequenciasPacotes;


        PlanejamentoRobo(StatusRobo *robo);

        void inicializaPlanejamento(StatusRobo *robo);

        retornoCalcFitness calculaFitness();

        void evoluiNGeracoes(int n);
        

        void atualizaPopulacao();
        void crossover();
        void mutacao();
        void genocidio();

};

#endif