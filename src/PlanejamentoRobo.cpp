#include "PlanejamentoRobo.h"


PlanejamentoRobo::PlanejamentoRobo(StatusRobo *robo) {
    this->melhorFitness = -INFINITY;
    
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAACAO; i++) {
        this->sequenciasPacotes.at(i) = *(new SequenciaAcao(robo));
        this->sequenciasPacotes.at(i).sequenciaAcoes = this->geraSequenciaAleatoria();
    }
}


int* PlanejamentoRobo::geraSequenciaAleatoria() {
    int quantidadeDeColetas = 0;
    int acoes[QUANTIDADE_ACOES];

    for(int j = 0; j < QUANTIDADE_ACOES; j++) {

        //Armazenamento do robô está cheio
        if(quantidadeDeColetas > ARMAZENAMENTO_ROBO) { acoes[j] = 0; } 
        else { acoes[j] = rand() % 2; }

        if(acoes[j]) { quantidadeDeColetas++; }
        else         { quantidadeDeColetas--; }
    
    }

    return acoes;
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

    return this->melhorFitness;
}


void PlanejamentoRobo::evoluiNGeracoes(int n) {
    for(int i = 0; i < n; i++) {
        
        this->atualizaPopulacao();
        this->calculaFitness();
    
    }
}


void PlanejamentoRobo::atualizaPopulacao() {
    //Atualiza a sequencia de ações
    this->mutacao();


    bool condicaoParaGenocidio = false; //Pensar em quando os genocídios precisam ocorrer

    if(condicaoParaGenocidio) { this->genocidio(); }
}

void PlanejamentoRobo::mutacao() {
    //Necessidade de verificar se a sequencia de pacotes gerada é valida
}

void PlanejamentoRobo::genocidio() {
    //A cada xx iterações, mata todos e cria uma nova população com base nos yy melhores
}