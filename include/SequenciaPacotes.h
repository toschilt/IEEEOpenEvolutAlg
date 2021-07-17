#ifndef SEQUENCIAPACOTES_H
#define SEQUENCIAPACOTES_H

#include "Pacote.h"
#include "Constantes.h"

typedef float retornoCalcFitness;

class SequenciaPacotes {
    private:

    public:

    vector<Pacote*> *sequenciaPacotes;

    retornoCalcFitness calculaFitness(int *sequenciaAcoes);

    SequenciaPacotes(vector<Pacote*> *sequencia);
    
};


#endif>begin(), novaSequencia->end(), std::default_random_engine(semente));
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
