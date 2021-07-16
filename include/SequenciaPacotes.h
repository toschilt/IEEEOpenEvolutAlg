#ifndef SEQUENCIAPACOTES_H
#define SEQUENCIAPACOTES_H

#include "Pacote.h"
#include "Constantes.h"


typedef float retornoCalcFitness;

class SequenciaPacotes {
    private:

    public:

    array<Pacote*, QUANTIDADE_PACOTES> sequenciaPacotes;

    retornoCalcFitness calculaFitness(int *sequenciaAcoes);
    
};

#endif