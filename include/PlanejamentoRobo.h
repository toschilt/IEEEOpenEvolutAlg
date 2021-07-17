#ifndef PLANEJAMENTOROBO_H
#define PLANEJAMENTOROBO_H

#include "SequenciaAcao.h"
#include "StatusRobo.h"
#include <vector>

/*
PlanejamentoRobo.h
    - int indiceMelhorCombinacao                   (índice com a melhor combinação de ações/pacotes)
    - SequenciaAcao[]                              (populações)

    - PlanejamentoRobo(StatusRobo)
    - inicializaSequenciaAcao(StatusRobo)          (inicializa sequências válidas de ações)
    - inicializaPlanejamento()                     (encapsula toda inicializacao)
    - calculaFitness()                             (já atualiza indiceMelhorCombinacao)
    - evoluiAteScore(int score)                    (chama o criaNovaPopulacao() para cada SequenciaAcao até obter o score desejado)
    - evoluiNGeracoes(int n)                       (chama o criaNovaPopulacao() para cada SequenciaAcao até passar todas as gerações)
*/
class PlanejamentoRobo {
    private:

        SequenciaAcao geraSequenciaAleatoria();

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