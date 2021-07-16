#include "SequenciaAcao.h"


SequenciaAcao::SequenciaAcao(StatusRobo *robo) 
{
    sequenciasPacotes = new vector<SequenciaPacotes*>;
    this->inicializaPacotes(robo->pacotesDisponiveis);
    this->indiceMelhorFitness = -1;
    this->melhorFitness = -INFINITY;
}


void SequenciaAcao::inicializaPacotes(vector<Pacote*> *pacotesDisponiveis)
{
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++)
    {
        vector<Pacote*> *novaSequencia = pacotesDisponiveis;

        shuffle(novaSequencia->begin(), novaSequencia->end(), std::default_random_engine(semente));
        sequenciasPacotes->at(i) = new SequenciaPacotes(novaSequencia);
    }
}


void SequenciaAcao::calculaFitness()
{
    //Passa por toda a sequência, calcula os fitness individuais, e salva o melhor
    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++)
    {
        this->fitness[i] = sequenciasPacotes[i]->calculaFitness(this->sequenciaAcoes);
        if(this->fitness[i] > this->melhorFitness)
        {
            this->melhorFitness = this->fitness[i];
            this->indiceMelhorFitness = i;
        }
    }
}


void SequenciaAcao::crossover()
{
    //Crossover na sequencia de blocos pra deixar o bagulho quente sei la
    //Maior fitness -> maior chance de estar no próximo
    
    //fitness * 100
    //vetor com a porra toda vai ter que ser mt grande puta que pariou
}


//Realiza trocas aleatórias com base na taxa de mutação e o fitness
//Sequencias de pacotes com menor fitness possuem mais chance de sofrer mutação
void SequenciaAcao::mutacao()
{

    for(int i = 0; i < TAMANHO_VETOR_SEQUENCIAPACOTES; i++)
    {
        
        if(i == this->indiceMelhorFitness)
        { 
            continue;
        }

        for(int j = 0; j < QUANTIDADE_PACOTES; j++) 
        {

            float taxaMutacao = TAXA_MUTACAO_SEQUENCIAPACOTES * (1 - this->fitness[j]);

            if(coinflip(taxaMutacao)) 
            {
                int indiceTroca = rand() % QUANTIDADE_PACOTES;
                
                Pacote *pacote1 = this->sequenciasPacotes.at(i).sequenciaPacotes[indiceTroca];
                Pacote *pacote2 = this->sequenciasPacotes.at(i).sequenciaPacotes[j];
                Pacote *aux = pacote1;
                pacote1 = pacote2;
                pacote2 = aux;
            }
        }
    }
}



bool SequenciaAcao::coinflip(float probabilidadeSucesso) 
{
    int flip = rand() % 100;
    if(flip > probabilidadeSucesso)
    { 
        return false; 
    }
    
    return true;
}