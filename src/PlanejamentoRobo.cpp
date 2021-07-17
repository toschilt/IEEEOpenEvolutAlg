#include "PlanejamentoRobo.h"


PlanejamentoRobo::PlanejamentoRobo(StatusRobo *robo) {
    this->melhorFitness = -INFINITY;
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) {
        int acoes[QUANTIDADE_ACOES];
        int quantidadeDeColetas = 0;

        for(int j = 0; j < QUANTIDADE_ACOES; j++) {
            
            if(quantidadeDeColetas > ARMAZENAMENTO_ROBO) {
                //Armazenamento do robô está cheio
                acoes[j] = 0;
            } else {
                acoes[j] = rand() % 2;
            }

            if(acoes[j]) { quantidadeDeColetas++; }
            else         { quantidadeDeColetas--; }
        }

        this->sequenciasPacotes.at(i).sequenciaAcoes = acoes;
    }
}


SequenciaAcao PlanejamentoRobo::geraSequenciaAleatoria() {

}


void PlanejamentoRobo::inicializaPlanejamento(StatusRobo *robo) {
    
}

retornoCalcFitness PlanejamentoRobo::calculaFitness() {
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) {
        
        this->fitness[i] = this->sequenciasPacotes.at(i).calculaFitness();
        
        if(this->fitness[i] > this->melhorFitness) {
            this->melhorFitness = this->fitness[i];
            this->indiceMelhorCombinacao = i;
        }
    }
}

void PlanejamentoRobo::evoluiNGeracoes(int n) {
    for(int i = 0; i < n; i++) {
        this->calculaFitness();
        
    }
}
