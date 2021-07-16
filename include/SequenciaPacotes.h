#ifndef SEQUENCIAPACOTES_H
#define SEQUENCIAPACOTES_H

#define QUANTIDADE_PACOTES 32

#include "Pacote.h"


typedef float retornoCalcFitness;

class SequenciaPacotes {
    private:

    public:

    array<Pacote*, QUANTIDADE_PACOTES> sequenciaPacotes;

    retornoCalcFitness calculaFitness(int *sequenciaAcoes);
    
};

#endif