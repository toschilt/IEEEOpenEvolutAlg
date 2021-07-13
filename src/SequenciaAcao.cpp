#include "SequenciaAcao.h"
#include <cmath>

SequenciaAcao::SequenciaAcao(StatusRobo *robo) {
    this->inicializaPacotes(robo->pacotesDisponiveis);
    this->indiceMelhorSequenciaPacotes = -1;
    this->melhorFitness = -INFINITY;
}


void SequenciaAcao::inicializaPacotes(Pacote* pacotesDisponiveis) {
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++) {
        for(int j = 0; j < QUANTIDADE_PACOTES; j++) {
            //Gerar uma sequência de cores aleatória sem repetição
        }
    }
}


void SequenciaAcao::calculaFitness() {
    //Passa por toda a sequência, calcula os fitness individuais, e salva o melhor
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++) {
        this->fitness[i] = this->sequenciaPacotes[i].calculaFitness(this->sequenciaAcoes);
        if(this->fitness[i] > this->melhorFitness) {
            this->melhorFitness = this->fitness[i];
            this->indiceMelhorSequenciaPacotes = i;
        }
    }
}


void SequenciaAcao::crossover() {
    //Crossover na sequencia de blocos pra deixar o bagulho quente sei la
    //Maior fitness -> maior chance de estar no próximo
}


void SequenciaAcao::mutacao() {
    //Mutar a sequencia de blocos
    //Fazer modificações aleatórias

    //Sequencias com menor fitness tem mais chance de mutação?
}