#ifndef PLANEJAMENTOROBO_H
#define PLANEJAMENTOROBO_H

#include "SequenciaAcao.h"

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

    public:

    int indiceMelhorCombinacao;
    
    array<SequenciaAcao, TAMANHO_VETOR_SEQUENCIAACAO> sequenciaPacotes;


    PlanejamentoRobo(StatusRobo *robo);

    void inicializaPlanejamento(StatusRobo *robo);

    void calculaFitness();

    void evoluiNGeracoes(int n);
    
};

#endif