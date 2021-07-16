#include "SequenciaAcao.h"


SequenciaAcao::SequenciaAcao(StatusRobo *robo) {
    this->inicializaPacotes(robo->pacotesDisponiveis);
    this->indiceMelhorFitness = -1;
    this->melhorFitness = -INFINITY;
}


void SequenciaAcao::inicializaPacotes(array<Pacote*, QUANTIDADE_PACOTES> pacotesDisponiveis) {
    
    unsigned semente = std::chrono::system_clock::now().time_since_epoch().count();

    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++) {

        //! Vi na net que essa atribuição cria uma cópia do vetor, mas pode ser fake news
        array<Pacote*, QUANTIDADE_PACOTES> novaSequencia = pacotesDisponiveis;

        shuffle(novaSequencia.begin(), novaSequencia.end(), std::default_random_engine(semente));
        sequenciaPacotes[i].sequenciaPacotes = novaSequencia;
    }
}


void SequenciaAcao::calculaFitness() {
    //Passa por toda a sequência, calcula os fitness individuais, e salva o melhor
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++) {
        this->fitness[i] = this->sequenciaPacotes[i].calculaFitness(this->sequenciaAcoes);
        if(this->fitness[i] > this->melhorFitness) {
            this->melhorFitness = this->fitness[i];
            this->indiceMelhorFitness = i;
        }
    }
}


void SequenciaAcao::crossover() {
    //Crossover na sequencia de blocos pra deixar o bagulho quente sei la
    //Maior fitness -> maior chance de estar no próximo
    
    //fitness * 100
    //vetor com a porra toda vai ter que ser mt grande puta que pariou
}


//Realiza trocas aleatórias com base na taxa de mutação e o fitness
//Sequencias de pacotes com menor fitness possuem mais chance de sofrer mutação
void SequenciaAcao::mutacao() {

    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++) {
        
        if(i == this->indiceMelhorFitness) { continue; }

        for(int j = 0; j < QUANTIDADE_PACOTES; j++) {
            if(coinflip(TAXA_MUTACAO * (1 - this->fitness[j]))) {
                int indiceTroca = rand() % QUANTIDADE_PACOTES;
                
                Pacote *pacote1 = this->sequenciaPacotes.at(i).sequenciaPacotes[indiceTroca];
                Pacote *pacote2 = this->sequenciaPacotes.at(i).sequenciaPacotes[j];
                Pacote *aux = pacote1;
                pacote1 = pacote2;
                pacote2 = aux;
            }
        }
    }
}



bool SequenciaAcao::coinflip(float probabilidadeSucesso) {
    int flip = rand() % 100;
    if(flip > probabilidadeSucesso) { return false; }
    return true;
}